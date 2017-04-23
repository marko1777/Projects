#include <iostream>
#include <fstream>
#include "GraphDiameter.h"
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
      std::cout << i + 1 << ".Graph Diameter is: "<<actGraphDiameter << std::endl;
      fileOut << i + 1 << ".Graph Diameter is: "<<actGraphDiameter << std::endl;
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