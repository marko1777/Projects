#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

enum Color{
  WHITE,
  BLACK,
  GRAY
};
//class GraphDiameter;

class GraphVertex
{
public:
//friend GraphDiameter;
  friend class GraphDiameter;
  GraphVertex(Color vC = WHITE,int d = 0) : vertexColor(vC), distance(d){}
  friend std::istream& operator>>(std::istream &in, GraphDiameter &g);
  friend std::ostream& operator<<(std::ostream &out,const GraphDiameter &g);
private:
  Color vertexColor;
  int distance;
  std::vector<int> adjAr;
};

class GraphDiameter{
public:
  int calculateDiameter();
  void calculateDistance(int examinedAdj, int &vertexDepth);
  void pushToMaxDistanceVec(int pushingElement);
  void calculateDistanceAndPushToMaxDistanceVec(int firstVertex);
  int firstTwoElementSumFromMaxDistanceVec();
  void recursiveCallForCalculateDistanceAndDecideMaxDistance(int actAdj,int &vertexDepth);
  friend std::istream& operator>>(std::istream &in, GraphDiameter &g);
  friend std::ostream& operator<<(std::ostream &out,const GraphDiameter &g);
private:
  int maxDistance;
  std::vector<GraphVertex> graphVertexVec;
  std::vector<int> maxDistanceVec;
};

std::istream& operator>>(std::istream &in, GraphDiameter &g)
{
    int vertexDb;
    in >> vertexDb;
    g.graphVertexVec.resize(vertexDb + 1);
    int u;
    int v;
    in >> u;
    while(u != 0)
    {
      in >> v;
      g.graphVertexVec[u].adjAr.push_back(v);
      g.graphVertexVec[v].adjAr.push_back(u);
      in >> u;
    }
    in >> u; //Az utolsó nulla beolvasása miatt
  return in;
}
std::ostream& operator<<(std::ostream &out,const GraphDiameter &g)
{
  for(int i = 1; i < g.graphVertexVec.size(); i++)
  {
    out << i << ".vertex adjacments: ";
    for(int j = 0; j < g.graphVertexVec[i].adjAr.size(); j++)
    {
      out << g.graphVertexVec[i].adjAr[j] << " "; 
    }
    out << std::endl;
  }
  return out;
}
int GraphDiameter::calculateDiameter()
{
  int firstVertex = 1;
  calculateDistanceAndPushToMaxDistanceVec(firstVertex);
  if(maxDistanceVec.size() >= 2)
  {
    std::sort(maxDistanceVec.begin(),maxDistanceVec.end(), std::greater<int>());
    return maxDistance = firstTwoElementSumFromMaxDistanceVec();
  }else{
    return maxDistance = maxDistanceVec.front();
  }
}
void GraphDiameter::calculateDistanceAndPushToMaxDistanceVec(int firstVertex)
{
  maxDistance = 0;
  graphVertexVec[firstVertex].vertexColor = GRAY;
  for(int i = 0; i < graphVertexVec[firstVertex].adjAr.size(); i++)
  {
    int mainDepth = 0;
    int actAdj = graphVertexVec[firstVertex].adjAr[i];
    calculateDistance(actAdj, mainDepth);
    pushToMaxDistanceVec(mainDepth);
    graphVertexVec[actAdj].vertexColor = BLACK;
  }
}
void GraphDiameter::calculateDistance(int examinedAdj, int &vertexDepth)
{
  graphVertexVec[examinedAdj].distance = ++vertexDepth;
  graphVertexVec[examinedAdj].vertexColor = GRAY;
  for(int i = 0; i < graphVertexVec[examinedAdj].adjAr.size(); i++)
  {
    int actAdj = graphVertexVec[examinedAdj].adjAr[i];
    if(graphVertexVec[actAdj].vertexColor == WHITE)
    {
      recursiveCallForCalculateDistanceAndDecideMaxDistance(actAdj,vertexDepth);
    }
  }
  graphVertexVec[examinedAdj].vertexColor = BLACK;
}
void GraphDiameter::recursiveCallForCalculateDistanceAndDecideMaxDistance(int actAdj,int &vertexDepth)
{
    int postVertexDepth = vertexDepth;
    calculateDistance(actAdj,postVertexDepth);
    graphVertexVec[actAdj].vertexColor = BLACK;
    if(maxDistance < postVertexDepth)
    {
      maxDistance = postVertexDepth;
    }
}
void GraphDiameter::pushToMaxDistanceVec(int pushingElement)
{
    if(maxDistance != 0)
    {
      maxDistanceVec.push_back(maxDistance);
      maxDistance = 0;
    }else{
      maxDistanceVec.push_back(pushingElement);
    }
}
int GraphDiameter::firstTwoElementSumFromMaxDistanceVec()
{
  int a = maxDistanceVec.front();
  maxDistanceVec.pop_back();
  int b = maxDistanceVec.front();
  maxDistanceVec.pop_back();
  return a + b;
}
int main()
{
  std::ifstream f("input.txt");
  int numberOfGraphs;
  f >> numberOfGraphs;
  for(int i = 0; i < numberOfGraphs; i++)
  {
    GraphDiameter gD;
    f >> gD;
    //std::cout << dg; Szomszédok kiírása
    std::cout << gD.calculateDiameter();
  }
}
