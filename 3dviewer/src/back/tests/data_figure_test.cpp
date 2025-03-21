#include "../data_figure.h"

#include <gtest/gtest.h>

#include <vector>

using namespace s21;

TEST(constructorPoint, noparams) {
  Point3D test;
  ASSERT_EQ(test.GetX(), 0);
  ASSERT_EQ(test.GetY(), 0);
  ASSERT_EQ(test.GetZ(), 0);
  ASSERT_EQ(test.GetW(), 1);
}
TEST(constructorPoint, params) {
  Point3D test(1, 2, 3);
  ASSERT_EQ(test.GetX(), 1);
  ASSERT_EQ(test.GetY(), 2);
  ASSERT_EQ(test.GetZ(), 3);
  ASSERT_EQ(test.GetW(), 1);
}
TEST(setterPoint, def) {
  Point3D test;
  test.SetX(1);
  test.SetY(2);
  test.SetZ(3);
  test.SetW(4);
  ASSERT_EQ(test.GetX(), 1);
  ASSERT_EQ(test.GetY(), 2);
  ASSERT_EQ(test.GetZ(), 3);
  ASSERT_EQ(test.GetW(), 4);
}
TEST(constructorVertex, params) {
  Vertex test(1, 2, 3, 0);
  auto testPoint = test.GetPosition();
  ASSERT_EQ(testPoint.GetX(), 1);
  ASSERT_EQ(testPoint.GetY(), 2);
  ASSERT_EQ(testPoint.GetZ(), 3);
  ASSERT_EQ(test.GetIndex(), 0);
}

TEST(vertexTransform, def) {
  Vertex test(1, 2, 3, 1);
  auto matrix = TransformMatrixBuilder::CreateScaleMatrix(3, 4, 5);
  test.Transform(matrix);
  auto resPoint = test.GetPosition();
  ASSERT_EQ(resPoint.GetX(), 3);
  ASSERT_EQ(resPoint.GetY(), 8);
  ASSERT_EQ(resPoint.GetZ(), 15);
  ASSERT_EQ(test.GetIndex(), 1);
}

TEST(vertex, lt) {
  Vertex test(1, 2, 3, 1);
  Vertex test2(1, 2, 3, 2);
  ASSERT_EQ(test < test2, true);
  ASSERT_EQ(test2 < test, false);
}
TEST(vertex, eq) {
  Vertex test(1, 2, 3, 1);
  Vertex test2(1, 2, 3, 2);
  Vertex test3(1, 2, 3, 1);
  ASSERT_EQ(test == test2, false);
  ASSERT_EQ(test == test3, true);
}
TEST(edge, constructor) {
  Vertex test1(1, 2, 3, 1);
  Vertex test2(2, 3, 4, 2);
  Edge test(test1, test2);
  auto vertBegin = test.GetBegin();
  auto vertEnd = test.GetEnd();
  auto begin = vertBegin.GetPosition();
  auto end = vertEnd.GetPosition();
  ASSERT_EQ(begin.GetX(), 1);
  ASSERT_EQ(begin.GetY(), 2);
  ASSERT_EQ(begin.GetZ(), 3);
  ASSERT_EQ(vertBegin.GetIndex(), 1);
  ASSERT_EQ(end.GetX(), 2);
  ASSERT_EQ(end.GetY(), 3);
  ASSERT_EQ(end.GetZ(), 4);
  ASSERT_EQ(vertEnd.GetIndex(), 2);
}
TEST(edge, constructorcpy) {
  Vertex test1(1, 2, 3, 1);
  Vertex test2(2, 3, 4, 2);
  Edge test(test1, test2);
  Edge cpy(test);
  auto vertBegin = cpy.GetBegin();
  auto vertEnd = cpy.GetEnd();
  auto begin = vertBegin.GetPosition();
  auto end = vertEnd.GetPosition();
  ASSERT_EQ(begin.GetX(), 1);
  ASSERT_EQ(begin.GetY(), 2);
  ASSERT_EQ(begin.GetZ(), 3);
  ASSERT_EQ(vertBegin.GetIndex(), 1);
  ASSERT_EQ(end.GetX(), 2);
  ASSERT_EQ(end.GetY(), 3);
  ASSERT_EQ(end.GetZ(), 4);
  ASSERT_EQ(vertEnd.GetIndex(), 2);
}
TEST(edge, eq) {
  Vertex test1(1, 2, 3, 1);
  Vertex test2(2, 3, 4, 2);
  Edge test(test1, test2);
  Edge cpy = test;
  auto vertBegin = cpy.GetBegin();
  auto vertEnd = cpy.GetEnd();
  auto begin = vertBegin.GetPosition();
  auto end = vertEnd.GetPosition();
  ASSERT_EQ(begin.GetX(), 1);
  ASSERT_EQ(begin.GetY(), 2);
  ASSERT_EQ(begin.GetZ(), 3);
  ASSERT_EQ(vertBegin.GetIndex(), 1);
  ASSERT_EQ(end.GetX(), 2);
  ASSERT_EQ(end.GetY(), 3);
  ASSERT_EQ(end.GetZ(), 4);
  ASSERT_EQ(vertEnd.GetIndex(), 2);
}
TEST(edge, lt) {
  Vertex test1(1, 2, 3, 1);
  Vertex test2(2, 3, 4, 2);
  Vertex test3(1, 1, 1, 1);
  Vertex test4(1, 1, 1, 1);
  Edge testEdge(test1, test2);
  Edge testEdge2(test3, test4);
  ASSERT_EQ(testEdge < testEdge2, false);
  ASSERT_EQ(testEdge2 < testEdge, true);
}
TEST(edge, eqeq) {
  Vertex test1(1, 2, 3, 1);
  Vertex test2(2, 3, 4, 2);
  Vertex test3(1, 1, 1, 1);
  Vertex test4(1, 1, 1, 1);
  Edge testEdge(test1, test2);
  Edge testEdge2(test3, test4);
  ASSERT_EQ(testEdge == testEdge2, false);
  Edge testEdge3(test1, test2);
  ASSERT_EQ(testEdge == testEdge3, true);
}
TEST(boundingbox, constructor) {
  Vertex begin(1, 2, 3, 1);
  Vertex another(2, 3, 4, 2);
  Vertex end(3, 4, 5, 3);
  std::vector<Vertex> testVertices = {begin, another, end};
  BoundingBox test(testVertices);
  auto min = test.GetMin();
  auto max = test.GetMax();
  auto mid = test.GetCenter();
  ASSERT_EQ(min.GetX(), 1);
  ASSERT_EQ(min.GetY(), 2);
  ASSERT_EQ(min.GetZ(), 3);
  ASSERT_EQ(max.GetX(), 3);
  ASSERT_EQ(max.GetY(), 4);
  ASSERT_EQ(max.GetZ(), 5);
  ASSERT_EQ(mid.GetX(), 2);
  ASSERT_EQ(mid.GetY(), 3);
  ASSERT_EQ(mid.GetZ(), 4);
}
TEST(figure, constructor) {
  Vertex begin(1, 2, 3, 1);
  Vertex another(2, 3, 4, 2);
  Edge edge(begin, another);
  std::vector<Vertex> vertices = {begin, another};
  std::vector<Edge> edges = {edge};
  Figure res(vertices, edges);
  ASSERT_EQ(res.GetVerticesSize(), 2);
  ASSERT_EQ(res.GetEdgesSize(), 1);
}
TEST(figure, getters) {
  Vertex begin(1, 2, 3, 1);
  Vertex another(2, 3, 4, 2);
  Edge edge(begin, another);
  std::vector<Vertex> vertices = {begin, another};
  std::vector<Edge> edges = {edge};
  Figure res(vertices, edges);
  res.addIndeces(0);
  res.addIndeces(1);
  res.addIndeces(2);
  auto resVertex = res.GetVertices();
  auto resEdge = res.GetEdges();
  auto resIndex = res.GetIndices();
  auto resPoints = res.GetPoints();
  auto resBoundingBox = res.GetBoundingBox();
  auto min = resBoundingBox.GetMin();
  auto max = resBoundingBox.GetMax();
  ASSERT_EQ(min.GetX(), 1);
  ASSERT_EQ(min.GetY(), 2);
  ASSERT_EQ(min.GetZ(), 3);
  ASSERT_EQ(max.GetX(), 2);
  ASSERT_EQ(max.GetY(), 3);
  ASSERT_EQ(max.GetZ(), 4);
  ASSERT_EQ(resVertex.size(), 2);
  ASSERT_EQ(resEdge.size(), 1);
  ASSERT_EQ(resIndex.size(), 3);
  ASSERT_EQ(resPoints.size(), 2);
}
TEST(figure, transform) {
  Vertex begin(1, 2, 3, 1);
  Vertex another(2, 3, 4, 2);
  Edge edge(begin, another);
  auto matrix = TransformMatrixBuilder::CreateScaleMatrix(3, 4, 5);
  std::vector<Vertex> vertices = {begin, another};
  std::vector<Edge> edges = {edge};
  Figure figure(vertices, edges);
  figure.Transform(matrix);
  auto transformedVertices = figure.GetVertices();
  auto beginPoint = transformedVertices[0].GetPosition();
  auto endPoint = transformedVertices[1].GetPosition();
  ASSERT_EQ(beginPoint.GetX(), 3);
  ASSERT_EQ(beginPoint.GetY(), 8);
  ASSERT_EQ(beginPoint.GetZ(), 15);
  ASSERT_EQ(endPoint.GetX(), 6);
  ASSERT_EQ(endPoint.GetY(), 12);
  ASSERT_EQ(endPoint.GetZ(), 20);
}
TEST(camera, constructor) {
  Camera test(1.0f, 2.0f, 3.0f);
  auto res = test.GetPosition();
  ASSERT_EQ(res.GetX(), 1.0f);
  ASSERT_EQ(res.GetY(), 2.0f);
  ASSERT_EQ(res.GetZ(), 3.0f);
}
TEST(camera, setters) {
  Camera test(1.0f, 2.0f, 3.0f);
  Point3D testPoint(4.0f, 5.0f, 6.0f);
  test.SetPosition(testPoint);
  test.SetBounds(2.0f, 10.0f);
  test.SetScaleFactor(1.5f);
  auto resPoint = test.GetPosition();
  ASSERT_EQ(resPoint.GetX(), 4.0f);
  ASSERT_EQ(resPoint.GetY(), 5.0f);
  ASSERT_EQ(resPoint.GetZ(), 6.0f);
  ASSERT_EQ(test.GetZNear(), 2.0f);
  ASSERT_EQ(test.GetZFar(), 10.0f);
  ASSERT_EQ(test.GetScaleNormalisedFactor(), 0.985f);
  ASSERT_EQ(test.GetViewAngle(), 61.6375f);
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
