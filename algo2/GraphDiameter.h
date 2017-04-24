#ifndef _GRAPHDIAMETER_
#define _GRAPHDIAMETER_

#include <iosfwd>
#include <vector>
#include "queue.h"

enum VertexColor{
  WHITE,
  BLACK,
  GRAY
};

class GraphVertex
{
public:
  friend class GraphDiameter;
  GraphVertex(VertexColor c = WHITE,int d = 0) : color(c), distance(d){}
  friend std::istream& operator>>(std::istream &in, class GraphDiameter &gD);
private:
  VertexColor color;
  int distance;
  std::vector<int> adjacentVec;
};

enum Exceptions{NOT_POSITIVE_COUNT};

void throwIfNotPositiveCount(int throwValue);

class GraphDiameter{
public:
  void initStartVertexAndQueue();
  int calculateDiameter();
  void calculateDistanceWithBfsAndDecideDiameter();
  void reInitVertexesAndQueue();
  void incrementActAdjDistanceAndPushItToQueue(int actVertex, int actAdjacent);
  void decideMaxDistanceInd(int actVertex, int actAdjacent);
  int createRandNumber();
  friend std::istream& operator>>(std::istream &in, GraphDiameter &gD);
private:
  int maxDistanceInd;
  MyQueue::Queue graphQueue;
  std::vector<GraphVertex> graphVertexVec;
};

#endif