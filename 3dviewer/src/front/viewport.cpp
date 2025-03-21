#include "viewport.h"

#include <iostream>

namespace s21 {
Viewport::Viewport(Control *ctr, Ui::MainWindow *ptrui, QWidget *parent)
    : QOpenGLWidget(parent),
      vertixesBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
      indexBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)),
      ptrControl(ctr),
      timer(new QTimer(this)),
      uiWin(ptrui) {
  setMinimumSize(400, 400);
  connect(timer, &QTimer::timeout, this, &Viewport::recordGif);
  std::filesystem::path exePath = std::filesystem::current_path();
  std::ifstream settings(exePath / "settings.txt");
  if (settings.is_open()) {
    std::string line;
    std::getline(settings, line);
    std::istringstream iss(line);
    std::string substr;
    iss >> substr;
    isDotted = toBool(substr);
    iss >> rVertex >> gVertex >> bVertex >> alphaVertex;
    iss >> lineWidth >> pointSize;
    iss >> rPoint >> gPoint >> bPoint >> alphaPoint;
    iss >> rBackground >> gBackground >> bBackground >> alphaBackground;
    iss >> substr;
    isPerspective = toBool(substr);
    iss >> substr;
    drawPoints = toBool(substr);
    iss >> substr;
    roundedPoints = toBool(substr);
    settings.close();
  }
  setRadioButtons();
  setSliders();
}

Viewport::~Viewport() {
  std::filesystem::path exePath = std::filesystem::current_path();
  std::ofstream settings(exePath / "settings.txt",
                         std::ios::out | std::ios::trunc);
  if (settings.is_open()) {
    settings << std::boolalpha << isDotted << " " << rVertex << " " << gVertex
             << " " << bVertex << " " << alphaVertex << " " << lineWidth << " "
             << pointSize << " " << rPoint << " " << gPoint << " " << bPoint
             << " " << alphaPoint << " " << rBackground << " " << gBackground
             << " " << bBackground << " " << alphaBackground << " "
             << std::boolalpha << isPerspective << " " << std::boolalpha
             << drawPoints << " " << std::boolalpha << roundedPoints;
    settings.close();
  } else {
    std::cout << "Failed to write settings.txt" << std::endl;
  }
  destroyBuffers();
  delete vertixesBuffer;
  delete indexBuffer;
}

void Viewport::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  initShaders();
  initShadersPoint();
}
void Viewport::resizeGL(int w, int h) {
  if (vertixesBuffer->isCreated()) updateBufferVertixes();
  glViewport(0, 0, w, h);
  update();
}

void Viewport::paintGL() {
  glClearColor(rBackground, gBackground, bBackground, alphaBackground);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    shaderProgram.bind();
    vertixesBuffer->bind();
    indexBuffer->bind();
    int posLoc = shaderProgram.attributeLocation("position");
    shaderProgram.setAttributeBuffer(posLoc, GL_FLOAT, 0, 4, sizeof(Point3D));
    shaderProgram.enableAttributeArray(posLoc);
    shaderProgram.setUniformValue(
        "u_lineColor", QVector4D(rVertex, gVertex, bVertex, alphaVertex));
    shaderProgram.setUniformValue("u_resolution",
                                  QVector2D((float)width(), (float)height()));
    shaderProgram.setUniformValue("u_isDotted", isDotted);
    shaderProgram.setUniformValue("u_lineWidth", lineWidth);
    glDrawElements(GL_LINES, indexBuffer->size(), GL_UNSIGNED_INT, 0);
    shaderProgram.release();
    if (drawPoints == true) {
      glPointSize(pointSize);
      shaderProgramPoints.bind();
      shaderProgramPoints.setUniformValue("circles", roundedPoints);
      shaderProgramPoints.setUniformValue("u_pointSize", pointSize);
      shaderProgramPoints.setAttributeValue(
          "inColor", QVector4D(rPoint, gPoint, bPoint, alphaPoint));
      shaderProgramPoints.setUniformValue(
          "u_resolution", QVector2D((float)width(), (float)height()));
      glDrawElements(GL_POINTS, indexBuffer->size(), GL_UNSIGNED_INT, 0);
      shaderProgramPoints.release();
    }
    vertixesBuffer->release();
    indexBuffer->release();
  }
}
void Viewport::initShaders() {
  if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                             ":/shaders/vertexShader.glsl")) {
    close();
  }
  if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,
                                             ":/shaders/geometryShader.glsl")) {
    close();
  }
  if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                             ":/shaders/fragmentShader.glsl")) {
    close();
  }
  shaderProgram.link();
}
void Viewport::initShadersPoint() {
  if (!shaderProgramPoints.addShaderFromSourceFile(
          QOpenGLShader::Vertex, ":/shaders/vertexShader.glsl")) {
    close();
  }
  if (!shaderProgramPoints.addShaderFromSourceFile(
          QOpenGLShader::Fragment, ":/shaders/fragmentShaderPoints.glsl")) {
    close();
  }
  shaderProgramPoints.link();
}
void Viewport::destroyBuffers() {
  vertixesBuffer->destroy();
  indexBuffer->destroy();
}
void Viewport::updateBufferVertixes() {
  auto vertices = ptrControl->mode(width(), height(), isPerspective);
  vertixesBuffer->bind();
  vertixesBuffer->write(0, vertices.data(), vertices.size() * sizeof(Point3D));
  vertixesBuffer->release();
}
void Viewport::updateBuffers() {
  auto vertices = ptrControl->mode(width(), height(), isPerspective);
  auto indices = ptrControl->getIndices();
  if (!vertixesBuffer->isCreated() && !indexBuffer->isCreated()) {
    vertixesBuffer->create();
    indexBuffer->create();
  }
  vertixesBuffer->bind();
  vertixesBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vertixesBuffer->allocate(vertices.data(), vertices.size() * sizeof(Point3D));
  vertixesBuffer->release();
  indexBuffer->bind();
  indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  indexBuffer->allocate(indices.data(), indices.size() * sizeof(GLuint));
  indexBuffer->release();
}

void Viewport::loadObj(const std::string &path) {
  ptrControl->load(path);
  updateBuffers();
  update();
}
void Viewport::doScale(int size) {
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    ptrControl->scale(size);
    updateBufferVertixes();
    update();
  }
}
void Viewport::doMove(float x, float y, float z) {
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    ptrControl->move(x, y, z);
    updateBufferVertixes();
    update();
  }
}
void Viewport::doRotate(int horizontal, int vertical) {
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    ptrControl->rotate(-float(vertical), float(horizontal));
    // std::cout << "angle: " << horizontal << " " << vertical << std::endl;

    updateBufferVertixes();
    update();
  }
}

void Viewport::doSetPerspectiveMode() {
  isPerspective = true;
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    updateBufferVertixes();
    update();
  }
  std::cout << "Perspective" << std::endl;
}
void Viewport::doSetOrthoMode() {
  isPerspective = false;
  if (vertixesBuffer->isCreated() && indexBuffer->isCreated()) {
    updateBufferVertixes();
    update();
  }
  std::cout << "Ortho" << std::endl;
}
void Viewport::doSolid() {
  isDotted = false;
  update();
}
void Viewport::doDotted() {
  isDotted = true;
  update();
}
void Viewport::changeColorLines(const QColor &var) {
  rVertex = var.redF();
  gVertex = var.greenF();
  bVertex = var.blueF();
  alphaVertex = var.alphaF();
  update();
}
void Viewport::changeColorPoints(const QColor &var) {
  rPoint = var.redF();
  gPoint = var.greenF();
  bPoint = var.blueF();
  alphaPoint = var.alphaF();
  update();
}
void Viewport::changePointSize(int value) {
  pointSize = value;
  update();
}
void Viewport::setQuads() {
  if (drawPoints == false) {
    drawPoints = true;
  }
  roundedPoints = false;
  update();
}
void Viewport::setCircles() {
  if (drawPoints == false) {
    drawPoints = true;
  }
  roundedPoints = true;
  update();
}
void Viewport::setAbsent() {
  drawPoints = false;
  update();
}
void Viewport::changeColorBackground(const QColor &var) {
  rBackground = var.redF();
  gBackground = var.greenF();
  bBackground = var.blueF();
  alphaBackground = var.alphaF();
  update();
}
void Viewport::saveBmp() {
  auto image = grab();
  image.save("screen.bmp");
}
void Viewport::saveJpeg() {
  auto image = grab();
  image.save("screen.jpeg");
}
void Viewport::recordGif() {
  if (timer->isActive() == false) {
    timer->start(100);
  }
  static int countFrames = 0;
  auto pixmap = grab();
  countFrames += 1;
  QImage image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
  auto imageRes = image.scaled(640, 480);
  gif.push_back(imageRes);
  if (countFrames == 50) {
    auto fileName = "result.gif";
    int width = 640;
    int height = 480;
    int delay = 10;
    GifWriter g;
    GifBegin(&g, fileName, width, height, delay);
    for (auto it = gif.begin(); it != gif.end(); it++) {
      GifWriteFrame(&g, it->bits(), width, height, delay);
    }
    GifEnd(&g);
    timer->stop();
    countFrames = 0;
  }
}
bool Viewport::toBool(const std::string &str) {
  bool res = false;
  if (str == "true") {
    res = true;
  }
  return res;
}

void Viewport::doChangeLineWidth(int size) {
  if (size >= 1 && size <= 50) {
    lineWidth = size;
    update();
  }
}
void Viewport::setRadioButtons() {
  if (isPerspective == false) {
    uiWin->radioButton_isometric->setChecked(true);
  }
  if (isDotted == true) {
    uiWin->radioButton_Dotted->setChecked(true);
  }
  if (drawPoints == true) {
    if (roundedPoints == false) {
      uiWin->radioButton_Quads->setChecked(true);
    }
  } else {
    uiWin->radioButton_Absent->setChecked(true);
  }
}
void Viewport::setSliders() {
  uiWin->horizontalSlider_lineThickness->setSliderPosition(lineWidth);
  uiWin->horizontalSlider_pointsize->setSliderPosition(pointSize);
}
}  // namespace s21