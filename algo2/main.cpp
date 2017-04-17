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
  // trick: http://en.cppreference.com/w/cpp/language/class
  // just above "Member specification"
  //
  // Note: Im not sure whats going on, but im pretty convinced that
  //   it is related someway to name lookup and thats why it ccould not find the typedef
  //   and yea, "friend class" forward decls a type as you know
  //   You can check this, making a pointer to the forward declared type
  //   and the compiler will happily allow it for you, becouse it doesnt have to know the
  //   whole definition for a pointer, and recognizes the name as a type.
  //   As a last note, i repeate that i dont really know whats going on, but happens on gcc and clang too
  friend class GraphDiameter;
  GraphVertex(Color vC = WHITE,int d = 0) : vertexColor(vC), distance(d){}
  friend std::istream& operator>>(std::istream &in, class GraphDiameter &g);
  friend std::ostream& operator<<(std::ostream &out,const class GraphDiameter &g);
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
    int u, v;
    in >> u;
    while(u)
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
  for(auto i = 1u; i < g.graphVertexVec.size(); i++)
  {
    out << i << ".vertex adjacments: ";
    for(auto j = 0u; j < g.graphVertexVec[i].adjAr.size(); j++)
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
  if(maxDistanceVec.size() >= 2u)
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
  for(auto i = 0u; i < graphVertexVec[firstVertex].adjAr.size(); i++)
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
  for(auto i = 0u; i < graphVertexVec[examinedAdj].adjAr.size(); i++)
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
