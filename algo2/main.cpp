#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
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
  friend std::ostream& operator<<(std::ostream &out, const GraphVertex &gV);
private:
  Color vertexColor;
  int distance;
  std::vector<int> vertexAdjacentVec;
};

enum Exceptions{NOT_POSITIVE_COUNT};

void throwIfNotPositiveCount(int throwValue)
{
  if(throwValue <= 0) throw NOT_POSITIVE_COUNT;
}

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
  friend std::ostream& operator<<(std::ostream &out, const GraphVertex &gV);
private:
  int maxDistanceInd;
  MyQueue::Queue graphQueue;
  std::vector<GraphVertex> graphVertexVec;
};

std::istream& operator>>(std::istream &in, GraphDiameter &gD)
{
    int vertexDb;
    in >> vertexDb;
    throwIfNotPositiveCount(vertexDb);
    gD.graphVertexVec.resize(vertexDb + 1);
    int u, v;
    in >> u;
    while(u != 0)
    {
      in >> v;
      gD.graphVertexVec[u].vertexAdjacentVec.push_back(v);
      gD.graphVertexVec[v].vertexAdjacentVec.push_back(u);
      in >> u;
    }
    in >> u; //Az utolsó nulla beolvasása miatt
  return in;
}

std::ostream& operator<<(std::ostream &out,const GraphDiameter &gD)
{
  for(auto i = 1u; i < gD.graphVertexVec.size(); i++)
  {
    out << i << ".vertex adjacent: ";
    for(auto j = 0u; j < gD.graphVertexVec[i].vertexAdjacentVec.size(); j++)
    {
      out << gD.graphVertexVec[i].vertexAdjacentVec[j] << " "; 
    }
    out << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream &out, const GraphVertex &gV)
{
  for(auto i = 0u; i < gV.vertexAdjacentVec.size(); ++i)
  {
    out << i + 1 << " .Adjacent: " << gV.vertexAdjacentVec[i] << " ";
  }
  out << std::endl;

  return out;
}

int GraphDiameter::calculateDiameter()
{
    initStartVertexAndQueue();
    calculateDistanceWithBfs();
    reInitVertexesAndQueue();
    calculateDistanceWithBfs();
    return graphVertexVec[maxDistanceInd].distance;
}

void GraphDiameter::initStartVertexAndQueue()
{
    srand(time(NULL));
    maxDistanceInd = 1;
    int startVertex = (rand() % (graphVertexVec.size()));
    graphVertexVec[startVertex].vertexColor = GRAY;
    graphQueue.push(checkStartVertex(startVertex));
}

int GraphDiameter::checkStartVertex(int startVertex)
{
  return startVertex == 0 ? 1 : startVertex;
}

void GraphDiameter::calculateDistanceWithBfs()
{
  while(!graphQueue.isEmpty())
  {
     const auto actVertex = graphQueue.pop();
     for(auto i = 0u; i < graphVertexVec[actVertex].vertexAdjacentVec.size(); i++)
      {
        const auto actAdjacent = graphVertexVec[actVertex].vertexAdjacentVec[i];
        if(graphVertexVec[actAdjacent].vertexColor == WHITE)
        {
          incrementAdjDistanceAndPushToQueue(actVertex, actAdjacent);
          decideMaxDistanceInd(actVertex, actAdjacent);
        }
      }
      graphVertexVec[actVertex].vertexColor = BLACK;
  }
}

void GraphDiameter::incrementAdjDistanceAndPushToQueue(int actVertex, int actAdjacent)
{
    graphVertexVec[actAdjacent].distance = graphVertexVec[actVertex].distance + 1;
    graphVertexVec[actAdjacent].vertexColor = GRAY;
    graphQueue.push(actAdjacent);
}

void GraphDiameter::decideMaxDistanceInd(int actVertex, int actAdjacent)
{
    if(graphVertexVec[maxDistanceInd].distance <  graphVertexVec[actAdjacent].distance)
    {
        maxDistanceInd = actAdjacent;
    }   
}

void GraphDiameter::reInitVertexesAndQueue()
{
    graphQueue.push(maxDistanceInd);
    for(auto i = 1u; i < graphVertexVec.size();++i) 
    {
        graphVertexVec[i].vertexColor = WHITE;
        graphVertexVec[i].distance = 0;
    }  
}

void mainProcedure()
{
    std::string fileName;
    std::cout << "Type your input file:"; std::cin >> fileName;
    std::ifstream fileIn(fileName);
    std::ofstream fileOut("out.txt");
    int numberOfGraphs;
    fileIn >> numberOfGraphs;
    throwIfNotPositiveCount(numberOfGraphs);
    for(int i = 0; i < numberOfGraphs; i++)
    {
      GraphDiameter gD;
      fileIn >> gD;
      int actGraphDiameter = gD.calculateDiameter();
      std::cout << i + 1 << " .Graph Diameter is: "<<actGraphDiameter << std::endl;
      std::cout << gD.graphVertexVec[actGraphDiameter] << std::endl;
      fileOut << i + 1 << " .Graph Diameter is: "<<actGraphDiameter << std::endl;
      fileOut << gD.graphVertexVec[actGraphDiameter] << std::endl;
    }
}

int main()
{
  try{
    mainProcedure();
  }catch(Exceptions e)
  {
    if (e == NOT_POSITIVE_COUNT) std::cout << "The input must be positive" << std::endl;    
  }
  catch(MyQueue::Queue::Exceptions e)
  {
    if(e == MyQueue::Queue::EMPTY_LIST) std::cout << "You can't erase if your List is empty" << std::endl;
  }
}