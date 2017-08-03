#include <iostream>

template <class T>
class Array2D {
public:
    class Array1D {
    public:
        Array1D(){}
        Array1D(int size) : oneDContainer(new T[size]) {
            std::cout << "1D created\n";
        }
        ~Array1D() {
            std::cout << "1D destroyed\n";
        //    delete[] oneDContainer;
        }

        T& operator[](int index) {
            return oneDContainer[index];
        }

        const T& operator[](int index) const{
            return oneDContainer[index];
        }

    private:
        T* oneDContainer;
    };

    Array2D(int row, int col) : twoDContainer(new Array1D[row]), twoDSIZE(row) {
      std::cout << "2D created\n";
        for (int i = 0; i < row; ++i) {
            twoDContainer[i] = Array1D(col);
        }
    }

    ~Array2D() {
        delete []twoDContainer;
        /*
        for (int i = 0; i < twoDSIZE; ++i) {
            delete twoDContainer[i];
        }
        */
        std::cout << "2D destroyed\n";
    }

    Array1D& operator[](int index) {
        return twoDContainer[index];
    }

    const Array1D& operator[](int index) const {
        return twoDContainer[index];
    }

private:
    Array1D* twoDContainer;
    unsigned twoDSIZE;
};

int main(){
     {
      Array2D<int> container(3,5);

      int smt = 1;
      for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 5; ++j) {
              container[i][j] = smt++;
          }
      }

      for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 5; ++j) {
              std::cout << container[i][j] << ' ';
          }
          std::cout << "\n";
      }
    }
    Array2D<int>::Array1D* p = new Array2D<int>::Array1D(5);
    delete p;
}
