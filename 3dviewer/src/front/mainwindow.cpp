#include "mainwindow.h"

#include "./ui_mainwindow.h"
namespace s21 {
MainWindow::MainWindow(Control *ctr, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ptrControl(ctr) {
  ui->setupUi(this);
  glWidget = new Viewport(ctr, ui, this);
  setWindowTitle("3D Viewer");
  ui->layout_main->replaceWidget(ui->viewport_placeholder, glWidget);
  connectButtons();
  connectSlidersandSpinBoxes();
}

void MainWindow::showFileDialog() {
  auto fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/src",
                                               tr("Objects (*.obj)"));
  std::string filePath = fileName.toStdString();
  if (!filePath.empty()) {
    glWidget->loadObj(filePath);
    auto lastIndex = fileName.lastIndexOf('/');
    auto shortFileName = fileName.sliced(lastIndex + 1);
    ui->label_12->setText(shortFileName);
    auto vert = ptrControl->getVerticesCount();
    auto edge = ptrControl->getEdgesCount();
    QString vertStr = "Vertices: " + QString::number(vert);
    QString edgeStr = "Edges: " + QString::number(edge);
    ui->statusbar->showMessage(vertStr + " " + edgeStr);
    toZeroSliders();
  }
}
void MainWindow::toZeroSliders() {
  ui->slider_horizont_rotation->setValue(0);
  ui->slider_vertical_rotation->setValue(0);
  ui->slider_scaling->setValue(0);
}
void MainWindow::showChangeColorPoints() {
  auto color = QColorDialog::getColor();
  if (color.isValid()) {
    glWidget->changeColorPoints(color);
  }
}
void MainWindow::showColorDialog() {
  auto color = QColorDialog::getColor();
  if (color.isValid()) {
    glWidget->changeColorLines(color);
  }
}
void MainWindow::showChangeBackground() {
  auto color = QColorDialog::getColor();
  if (color.isValid()) {
    glWidget->changeColorBackground(color);
  }
}
void MainWindow::connectSlidersandSpinBoxes() {
  // lamdas
  auto rotate_lamda = [&]() {
    glWidget->doRotate(ui->slider_horizont_rotation->value(),
                       ui->slider_vertical_rotation->value());
  };

  auto move_lamda = [&]() {
    glWidget->doMove(ui->horizontalSlider_move_x->value(),
                     ui->horizontalSlider_move_y->value(),
                     ui->horizontalSlider_move_z->value());
  };
  // scale
  ui->spinBox_7->setMinimum(-100);
  connect(ui->slider_scaling, &QSlider::valueChanged, ui->spinBox_7,
          &QSpinBox::setValue);
  connect(ui->spinBox_7, &QSpinBox::valueChanged, ui->slider_scaling,
          &QSlider::setValue);
  connect(ui->slider_scaling, &QSlider::valueChanged, glWidget,
          &Viewport::doScale);
  // rotate horizont
  ui->slider_horizont_rotation->setRange(-90, 90);
  ui->spinBox_horizontal_rotation->setMinimum(-90);
  connect(ui->slider_horizont_rotation, &QSlider::valueChanged,
          ui->spinBox_horizontal_rotation, &QSpinBox::setValue);
  connect(ui->slider_horizont_rotation, &QSlider::valueChanged, rotate_lamda);
  connect(ui->spinBox_horizontal_rotation, &QSpinBox::valueChanged,
          ui->slider_horizont_rotation, &QSlider::setValue);
  // rotate vertical
  ui->slider_vertical_rotation->setRange(-90, 90);
  ui->spinBox_vertical_rotation->setMinimum(-90);
  connect(ui->slider_vertical_rotation, &QSlider::valueChanged, rotate_lamda);
  connect(ui->slider_vertical_rotation, &QSlider::valueChanged,
          ui->spinBox_vertical_rotation, &QSpinBox::setValue);
  connect(ui->spinBox_vertical_rotation, &QSpinBox::valueChanged,
          ui->slider_vertical_rotation, &QSlider::setValue);
  // move x
  ui->spinBox->setMinimum(-100);
  connect(ui->horizontalSlider_move_x, &QSlider::valueChanged, move_lamda);
  connect(ui->horizontalSlider_move_x, &QSlider::valueChanged, ui->spinBox,
          &QSpinBox::setValue);
  connect(ui->spinBox, &QSpinBox::valueChanged, ui->horizontalSlider_move_x,
          &QSlider::setValue);
  // move y
  ui->spinBox_3->setMinimum(-100);
  connect(ui->horizontalSlider_move_y, &QSlider::valueChanged, move_lamda);
  connect(ui->horizontalSlider_move_y, &QSlider::valueChanged, ui->spinBox_3,
          &QSpinBox::setValue);
  connect(ui->spinBox_3, &QSpinBox::valueChanged, ui->horizontalSlider_move_y,
          &QSlider::setValue);
  // move z
  ui->spinBox_4->setMinimum(-100);
  connect(ui->horizontalSlider_move_z, &QSlider::valueChanged, move_lamda);
  connect(ui->horizontalSlider_move_z, &QSlider::valueChanged, ui->spinBox_4,
          &QSpinBox::setValue);
  connect(ui->spinBox_4, &QSpinBox::valueChanged, ui->horizontalSlider_move_z,
          &QSlider::setValue);
}
void MainWindow::connectButtons() {
  connect(ui->radioButton_perspective, &QRadioButton::toggled, glWidget,
          &Viewport::doSetPerspectiveMode);
  connect(ui->radioButton_isometric, &QRadioButton::toggled, glWidget,
          &Viewport::doSetOrthoMode);
  connect(ui->pushButton, &QPushButton::clicked, this,
          &MainWindow::showFileDialog);
  connect(ui->radioButton_Solid, &QRadioButton::toggled, glWidget,
          &Viewport::doSolid);
  connect(ui->radioButton_Dotted, &QRadioButton::toggled, glWidget,
          &Viewport::doDotted);
  connect(ui->horizontalSlider_lineThickness, &QSlider::valueChanged, glWidget,
          &Viewport::doChangeLineWidth);
  connect(ui->pushButton_color, &QPushButton::clicked, this,
          &MainWindow::showColorDialog);
  connect(ui->pushButton_color_points, &QPushButton::clicked, this,
          &MainWindow::showChangeColorPoints);
  connect(ui->horizontalSlider_pointsize, &QSlider::valueChanged, glWidget,
          &Viewport::changePointSize);
  connect(ui->radioButton_Quads, &QRadioButton::toggled, glWidget,
          &Viewport::setQuads);
  connect(ui->radioButton_Circles, &QRadioButton::toggled, glWidget,
          &Viewport::setCircles);
  connect(ui->radioButton_Absent, &QRadioButton::toggled, glWidget,
          &Viewport::setAbsent);
  connect(ui->pushButton_colorBackground, &QPushButton::clicked, this,
          &MainWindow::showChangeBackground);
  connect(ui->pushButtonBmp, &QPushButton::clicked, glWidget,
          &Viewport::saveBmp);
  connect(ui->pushButtonJpeg, &QPushButton::clicked, glWidget,
          &Viewport::saveJpeg);
  connect(ui->pushButton_gif, &QPushButton::clicked, glWidget,
          &Viewport::recordGif);
}
MainWindow::~MainWindow() { delete ui; }
}  // namespace s21