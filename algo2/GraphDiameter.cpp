#include <iostream>
#include <vector>
#include <random>
#include "GraphDiameter.h"

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
      gD.graphVertexVec[u].adjacentVec.push_back(v);
      gD.graphVertexVec[v].adjacentVec.push_back(u);
      in >> u;
    }
    in >> u; //Az utolsó nulla beolvasása miatt
  return in;
}

void throwIfNotPositiveCount(int throwValue)
{
  if(throwValue <= 0) throw NOT_POSITIVE_COUNT;
}

int GraphDiameter::calculateDiameter()
{
    initStartVertexAndQueue();
    calculateDistanceWithBfsAndDecideDiameter();
    reInitVertexesAndQueue();
    calculateDistanceWithBfsAndDecideDiameter();
    return graphVertexVec[maxDistanceInd].distance;
}

void GraphDiameter::initStartVertexAndQueue()
{
    maxDistanceInd = 1;
    int startVertex = createRandNumber();
    graphVertexVec[startVertex].color = GRAY;
    graphQueue.push(startVertex);
}

int GraphDiameter::createRandNumber()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(1, graphVertexVec.size());
    return dis(gen);
}

void GraphDiameter::calculateDistanceWithBfsAndDecideDiameter()
{
  while(!graphQueue.isEmpty())
  {
     const auto actVertex = graphQueue.pop();
     for(auto i = 0u; i < graphVertexVec[actVertex].adjacentVec.size(); i++)
      {
        const auto actAdjacent = graphVertexVec[actVertex].adjacentVec[i];
        if(graphVertexVec[actAdjacent].color == WHITE)
        {
          incrementActAdjDistanceAndPushItToQueue(actVertex, actAdjacent);
          decideMaxDistanceInd(actVertex, actAdjacent);
        }
      }
      graphVertexVec[actVertex].color = BLACK;
  }
}

void GraphDiameter::incrementActAdjDistanceAndPushItToQueue(int actVertex, int actAdjacent)
{
    graphVertexVec[actAdjacent].distance = graphVertexVec[actVertex].distance + 1;
    graphVertexVec[actAdjacent].color = GRAY;
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
        graphVertexVec[i].color = WHITE;
        graphVertexVec[i].distance = 0;
    }  
}