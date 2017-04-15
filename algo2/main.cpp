#include <iostream>
#include <fstream>
#include <vector>

enum Color{
  WHITE,
  BLACK,
  GRAY
};
class GraphVertex
{
public:
  GraphVertex(int v,Color vC = WHITE,int d = 0) : vertex(v),vertexColor(vC), distance(d){}
  friend std::istream& operator>>(std::istream& in, GraphVertex &g);
private:
  int vertex;
  Color vertexColor;
  int distance;
  std::vector<int> adjAr;
};

class GraphDiameter{
public:
  int calculateDiameter();
  void calculateDistance(int actAdj);
  friend std::istream& operator>>(std::istream &in, GraphDiameter &g);
  friend std::ostream& operator<<(std::ostream &out,const GraphDiameter &g);
private:
  std::vector<GraphVertex> graphVertexVec;
  int maxDistance;
};

std::istream& operator>>(std::istream &in, GraphDiameter &g)
{
    int vertexDb;
    in >> vertexDb;
    g.adjAr.resize(vertexDb + 1);
    int u;
    int v;
    in >> u;
    while(u != 0)
    {
      GraphVertex tempVertexU(u);
      in >> v;
      GraphVertex tempVertexV(v);
      g.adjAr[u].push_back(tempVertexV);
      g.adjAr[v].push_back(tempVertexU);
      in >> u;
    }
  return in;
}
std::ostream& operator<<(std::ostream &out,const GraphDiameter &g)
{
  for(int i = 1; i < g.adjAr.size(); i++)
  {
    out << i << ".vertex adjacments: ";
    for(int j = 0; j < g.adjAr[i].size(); j++)
    {
      out << g.adjAr[i][j].vertex << " "; 
    }
    out << std::endl;
  }
  return out;
}

int GraphDiameter::calculateDiameter()
{
  maxDistance = 0;
  GraphVertex startVertex (1, GRAY);
  for(int i = 0; i < adjAr[1].size(); i++)
  {
    adjAr[1][i].vertexColor = GRAY;
    int actVertex = adjAr[1][i].vertex;
    calculateDistance(actVertex);
    if(maxDistance < adjAr[1][actVertex].distanceFromStart)
      adjAr[1][actVertex].distanceFromStart = maxDistance;
  }
}

void GraphDiameter::calculateDistance(int actAdj)
{
  for(int i = 0; i < adjAr[actAdj].size(); i++)
  {
    adjAr[actAdj][i].distanceFromStart++;
    if(adjAr[actAdj][i].vertexColor == WHITE )
      calculateDistance(i);
  }
}
int main()
{
  std::ifstream f("input.txt");
  GraphDiameter dg;
  f >> dg;
  std::cout << dg;
}
