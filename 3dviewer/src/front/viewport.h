#ifndef WIDGET_H
#define WIDGET_H
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QVector3D>
#include <filesystem>

#include "../controller/control.h"
#include "./ui_mainwindow.h"
#include "gif.h"
#include "profiler.h"
namespace s21 {
class MainWindow;
class Viewport : public QOpenGLWidget {
  Q_OBJECT

 public:
  Viewport(Control *ctr, Ui::MainWindow *ptrui, QWidget *parent = nullptr);
  ~Viewport();

  void doRotate(int horizontal, int vertical);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initShaders();
  void initShadersPoint();
  void destroyBuffers();
  void updateBufferVertixes();
  void updateBuffers();

 private:
  Profiler profiler;
  QOpenGLBuffer *vertixesBuffer;
  QOpenGLBuffer *indexBuffer;
  QOpenGLShaderProgram shaderProgram;
  QOpenGLShaderProgram shaderProgramPoints;
  Control *ptrControl;
  Ui::MainWindow *uiWin;
  QTimer *timer;
  bool isDotted = false;
  float rVertex = 1, gVertex = 0, bVertex = 0, alphaVertex = 1;
  float lineWidth = 1, pointSize = 0;
  float rPoint = 0, gPoint = 0, bPoint = 1, alphaPoint = 1;
  float rBackground = 0, gBackground = 0, bBackground = 0, alphaBackground = 1;
  bool isPerspective = true;
  bool drawPoints = true;
  bool roundedPoints = true;
  std::vector<QImage> gif;
  bool toBool(const std::string &str);
  void setRadioButtons();
  void setSliders();
  void setSpinboxes();
 public slots:
  void loadObj(const std::string &path);
  void doScale(int size);
  void doMove(float x, float y, float z);
  void doSetPerspectiveMode();
  void doSetOrthoMode();
  void doSolid();
  void doDotted();
  void doChangeLineWidth(int size);
  void changeColorPoints(const QColor &var);
  void changeColorLines(const QColor &var);
  void changePointSize(int value);
  void setQuads();
  void setCircles();
  void setAbsent();
  void changeColorBackground(const QColor &var);
  void saveBmp();
  void saveJpeg();
  void recordGif();
};
}  // namespace s21
#endif  // WIDGET_H
