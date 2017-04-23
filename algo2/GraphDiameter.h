#ifndef _GRAPHDIAMETER_
#define _GRAPHDIAMETER_

#include <iosfwd>
#include <vector>
#include "queue.h"

enum Color{
  WHITE,
  BLACK,
  GRAY
};

class GraphVertex
{
public:
  friend class GraphDiameter;
  GraphVertex(Color vC = WHITE,int d = 0) : vertexColor(vC), distance(d){}
  friend std::istream& operator>>(std::istream &in, class GraphDiameter &gD);
  friend std::ostream& operator<<(std::ostream &out, const class GraphDiameter &gD);
private:
  Color vertexColor;
  int distance;
  std::vector<int> vertexAdjacentVec;
};

enum Exceptions{NOT_POSITIVE_COUNT};

void throwIfNotPositiveCount(int throwValue);

class GraphDiameter{
public:
  void initStartVertexAndQueue();
  int calculateDiameter();
  void calculateDistanceWithBfs();
  void reInitVertexesAndQueue();
  void incrementAdjDistanceAndPushToQueue(int actVertex, int actAdjacent);
  void decideMaxDistanceInd(int actVertex, int actAdjacent);
  int checkStartVertex(int startVertex);
  friend std::istream& operator>>(std::istream &in, GraphDiameter &gD);
  friend std::ostream& operator<<(std::ostream &out, const GraphDiameter &gD);
private:
  int maxDistanceInd;
  MyQueue::Queue graphQueue;
  std::vector<GraphVertex> graphVertexVec;
};

#endif