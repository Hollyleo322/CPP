#include "../facade.h"

#include <gtest/gtest.h>

#include "../data_figure.h"

using namespace s21;

TEST(FacadeOperationResult, constructor) {
  FacadeOperationResult result;
  ASSERT_EQ(result.GetErrorMessage(), "SUCCESS");
  ASSERT_EQ(result.isSuccess(), true);
}
TEST(FacadeOperationResult, constructorParams) {
  FacadeOperationResult result("FAILED");
  ASSERT_EQ(result.GetErrorMessage(), "FAILED");
  ASSERT_EQ(result.isSuccess(), false);
}
TEST(FacadeOperationResult, setters) {
  FacadeOperationResult result;
  result.SetErrorMessage("mmm");
  ASSERT_EQ(result.GetErrorMessage(), "mmm");
  result.SetResult(false);
  ASSERT_EQ(result.isSuccess(), false);
}
TEST(FacadeTransformedVertex, constructor) {
  Point3D pt1(1, 2, 3);
  Point3D pt2(3, 2, 4);
  std::vector<Point3D> points = {pt1, pt2};
  std::vector<unsigned int> indeces = {0, 1, 2};
  FacadeTransformedVertex vertex(points, indeces);
  auto resPoints = vertex.GetVertices();
  auto resIndeces = vertex.GetIndices();
  ASSERT_EQ(resPoints.size(), 2);
  ASSERT_EQ(resIndeces.size(), 3);
}
TEST(FacadeTransformedVertex, constructorcpy) {
  Point3D pt1(1, 2, 3);
  Point3D pt2(3, 2, 4);
  std::vector<Point3D> points = {pt1, pt2};
  std::vector<unsigned int> indeces = {0, 1, 2};
  FacadeTransformedVertex vertex(points, indeces);
  FacadeTransformedVertex vertexCopy(vertex);
  auto resPoints = vertexCopy.GetVertices();
  auto resIndeces = vertexCopy.GetIndices();
  ASSERT_EQ(resPoints.size(), 2);
  ASSERT_EQ(resIndeces.size(), 3);
}
TEST(FacadeTransformedVertex, operatoreq) {
  Point3D pt1(1, 2, 3);
  Point3D pt2(3, 2, 4);
  std::vector<Point3D> points = {pt1, pt2};
  std::vector<unsigned int> indeces = {0, 1, 2};
  FacadeTransformedVertex vertex(points, indeces);
  FacadeTransformedVertex vertexCopy = vertex;
  auto resPoints = vertexCopy.GetVertices();
  auto resIndeces = vertexCopy.GetIndices();
  ASSERT_EQ(resPoints.size(), 2);
  ASSERT_EQ(resIndeces.size(), 3);
}
TEST(Facade, constructor) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resScene = facade.GetScene();
  auto resFigures = resScene.GetFigures();
  ASSERT_EQ(resFigures.size(), 0);
}
TEST(Facade, loadscenefail) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resLoad = facade.LoadScene("../../front/cub.obj");
  ASSERT_EQ(resLoad.isSuccess(), false);
  ASSERT_EQ(resLoad.GetErrorMessage(), "File isn't existing");
}
TEST(Facade, loadanddrawscene) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resLoad = facade.LoadScene("../../front/cube.obj");
  ASSERT_EQ(resLoad.isSuccess(), true);
  ASSERT_EQ(resLoad.GetErrorMessage(), "SUCCESS");
  auto resDraw = facade.DrawScene(100, 100, true);
  auto resVertices = resDraw.GetVertices();
  auto resIndeces = resDraw.GetIndices();
  ASSERT_EQ(resVertices.size(), 8);
  ASSERT_EQ(resIndeces.size(), 36);
}
TEST(Facade, movescene) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resLoad = facade.LoadScene("../../front/cube.obj");
  ASSERT_EQ(resLoad.isSuccess(), true);
  ASSERT_EQ(resLoad.GetErrorMessage(), "SUCCESS");
  auto resMove = facade.MoveScene(1, 1, 1);
  ASSERT_EQ(resMove.isSuccess(), true);
  ASSERT_EQ(resMove.GetErrorMessage(), "SUCCESS");
}
TEST(Facade, rotatescene) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resLoad = facade.LoadScene("../../front/cube.obj");
  ASSERT_EQ(resLoad.isSuccess(), true);
  ASSERT_EQ(resLoad.GetErrorMessage(), "SUCCESS");
  auto resRotate = facade.RotateScene(30, 0, 0);
  ASSERT_EQ(resRotate.isSuccess(), true);
  ASSERT_EQ(resRotate.GetErrorMessage(), "SUCCESS");
}
TEST(Facade, scalescene) {
  FileReader reader;
  Scene scene;
  Facade facade(reader, scene);
  auto resLoad = facade.LoadScene("../../front/cube.obj");
  ASSERT_EQ(resLoad.isSuccess(), true);
  ASSERT_EQ(resLoad.GetErrorMessage(), "SUCCESS");
  auto resScale = facade.ScaleScene(2);
  ASSERT_EQ(resScale.isSuccess(), true);
  ASSERT_EQ(resScale.GetErrorMessage(), "SUCCESS");
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
