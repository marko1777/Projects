#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
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
      gD.graphVertexVec[u].vertexAdjacentVec.push_back(v);
      gD.graphVertexVec[v].vertexAdjacentVec.push_back(u);
      in >> u;
    }
    in >> u; //Az utolsó nulla beolvasása miatt
  return in;
}

void throwIfNotPositiveCount(int throwValue)
{
  if(throwValue <= 0) throw NOT_POSITIVE_COUNT;
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
    maxDistanceInd = 1;
    srand(time(NULL));
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