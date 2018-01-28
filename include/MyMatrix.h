#ifndef MYMATRIX_H
#define MYMATRIX_H
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <vector>


using namespace std;


class MyMatrix {
 private:
  vector<vector <double> > matrix;
  int height;
  int width;

 double abs(double x) {
        return (x >= 0) ? x : -x;
    }

 public:
 MyMatrix(int _rows, int _cols) {
  matrix.resize(_rows);
 double  _initial=0;
  for (int i=0; i<matrix.size(); i++) {
    matrix[i].resize(_cols, _initial);
  }
  height = _rows;
  width = _cols;
}

MyMatrix(const MyMatrix& arg) {
  matrix = arg.matrix;
  height = arg.get_rows();
  width = arg.get_cols();
}
virtual ~MyMatrix() {}
MyMatrix& operator=(const MyMatrix& arg) {
  if (&arg == this)
    return *this;
  int new_rows = arg.get_rows();
  int new_cols = arg.get_cols();
  matrix.resize(new_rows);
  for (int i=0; i<matrix.size(); i++) {
    matrix[i].resize(new_cols);
  }
  for (int i=0; i<new_rows; i++) {
    for (int j=0; j<new_cols; j++) {
      matrix[i][j] = arg(i, j);
    }
  }
  height = new_rows;
  width = new_cols;
  return *this;
}



MyMatrix& operator=(const double tab[]) {
    for(int i=0; i< height;i++)
        for(int j=0; j<width;j++)
            matrix[i][j]=tab[i*height+j];
    return *this;
}

MyMatrix& operator=(const vector< vector <double> > tab) {
    for(int i=0; i< height;i++)
        for(int j=0; j<width;j++)
            matrix[i][j]=tab[i][j];
    return *this;
}


MyMatrix operator+(const MyMatrix& arg) {
  MyMatrix result(height, width);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      result(i,j) = this->matrix[i][j] + arg(i,j);
    }
  }
  return result;
}


MyMatrix& operator+=(const MyMatrix& arg) {
  int height = arg.get_rows();
  int width = arg.get_cols();
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      this->matrix[i][j] += arg(i,j);
    }
  }
  return *this;
}

MyMatrix operator-(const MyMatrix& arg) {
  int height = arg.get_rows();
  int width = arg.get_cols();
  MyMatrix result(height, width);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      result(i,j) = this->matrix[i][j] - arg(i,j);
    }
  }
  return result;
}

MyMatrix& operator-=(const MyMatrix& arg) {
  int height = arg.get_rows();
  int width = arg.get_cols();
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      this->matrix[i][j] -= arg(i,j);
    }
  }
  return *this;
}


MyMatrix operator*(const MyMatrix& arg) {
  int height = arg.get_rows();
  int width = arg.get_cols();
  MyMatrix result(height, width);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      for (int k=0; k<height; k++) {
        result(i,j) += this->matrix[i][k] * arg(k,j);
      }
    }
  }
  return result;
}

MyMatrix operator*(const double& arg) {
  MyMatrix result(this->height, this->width);
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      result(i,j) = this->matrix[i][j]*arg;
    }
  }
  return result;
}

MyMatrix& operator*=(const MyMatrix& arg) {
  MyMatrix result = (*this) * arg;
  (*this) = result;
  return *this;
}

MyMatrix transpose() {
  MyMatrix result(height, width);

  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      result(i,j) = this->matrix[j][i];
    }
  }
  return result;
}

double determinant(){
    double sum=0;
    double temp[2*height-1][width];
    double num=0;
    for(int i=0;i<height;i++)
        for(int j=0;j<width;i++)
            temp[i][j]=matrix[i][j];

    for(int i=0;i<height-1;i++)
        for(int j=0;j<width;i++)
            temp[i+height][j]=matrix[i][j];

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int y=0;y<width;y++){
                sum*=temp[i-y][j-y];
            }
            sum+=num;
        }
    }
    for(int i=0;i<height;i++){
        for(int j=width-1;j>=0;j++){
            for(int y=0;y<width;y++){
                sum*=temp[i-y][j-y];
            }
            sum-=num;
        }
    }
    return sum;
}



MyMatrix inverse_diag(){
    MyMatrix result(height,width);
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            result(i,j)=matrix[i][j];
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        if(i==j){
                double temp = result[i][j];
                result(i,j) = 1/temp;
        }
    return result;
}

// Macierz * wektor
vector<double> operator[](std::size_t idx)
{return matrix[idx];}

vector<double> operator*(const vector<double>& arg) {
            vector<double> result(arg.size());
            for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    result[i] += this->matrix[i][j] * arg[j];
                }
            }
            return result;
        }



vector<double> diag_vec() {
  vector<double> result(height);

  for (int i=0; i<height; i++) {
    result[i] = this->matrix[i][i];
  }

  return result;
}


double& operator()(const int& row, const int& col) {
  return this->matrix[row][col];
}


const double& operator()(const int& row, const int& col) const {
  return this->matrix[row][col];
}

int get_rows() const {
  return this->height;
}

int get_cols() const {
  return this->width;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                   METODY OBLICZENIOWE
//////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------partial Gauss
        vector<double> Gauss_partial() {
            int n = get_rows();
            for (int i = 0; i < n; i++) {
                // znajd wiersz z maksymalnym elementem
                double maxEl = abs(matrix[i][i]);
                int maxRow = i;
                for (int k = i+1; k < n; k++) {
                    if (abs(matrix[k][i]) > maxEl) {
                        maxEl = abs(matrix[k][i]);
                        maxRow = k;
                    }
                }
                // zamieñ maksymalny wiersz z obecnym
                for (int k = i; k < n+1; k++) {
                    double pom = matrix[maxRow][k];
                    matrix[maxRow][k] = matrix[i][k];
                    matrix[i][k] = pom;
                }
                // wyprowad zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    double c = -matrix[k][i] / matrix[i][i];
                    for (int j = i; j < n+1; j++) {
                        if (i == j) {
                            if(matrix[k][j] > 0)
                                matrix[k][j] = 0;
                        } else {
                            matrix[k][j] += c * matrix[i][j];
                        }
                    }
                }
            }
            // rozwi¹¿ Ax = B za pomoc¹ powsta³ej macierzy trójk¹tnej
            vector<double> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }
//-------------------------------------------------------------------partial Gauss optimized
        vector<double> Gauss_partial_optimized() {
            int n = get_rows();
            for (int i = 0; i < n; i++) {
                // znajd wiersz z maksymalnym elementem
                double maxEl = abs(matrix[i][i]);
                int maxRow = i;
                for (int k = i+1; k < n; k++) {
                    if (abs(matrix[k][i]) > maxEl) {
                        maxEl = abs(matrix[k][i]);
                        maxRow = k;
                    }
                }
                // zamieñ maksymalny wiersz z obecnym
                for (int k = i; k < n+1; k++) {
                    double pom = matrix[maxRow][k];
                    matrix[maxRow][k] = matrix[i][k];
                    matrix[i][k] = pom;
                }
                // wyprowad zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    double c = -matrix[k][i] / matrix[i][i];
                    for (int j = i; j < n+1; j++) {
                        if (i == j) {
                            if(matrix[k][j] > 0  && matrix[k][j] !=0)
                                matrix[k][j] = 0;
                        } else {
                            matrix[k][j] += c * matrix[i][j];
                        }
                    }
                }
            }
            // rozwi¹¿ Ax = B za pomoc¹ powsta³ej macierzy trójk¹tnej
            vector<double> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }

//-----------------------------------------------------------Jacobi
vector<double> Jacobi(int iter,double initial){
    //Create,resize and fill matrix A
    vector < vector < double > > A;
    A.resize(width-1);
    for(int i=0;i<width-1;i++){
        A[i].resize(width-1,0);
        for(int j=0;j<width-1;j++)
            A[i][j]=matrix[i][j];
    }
    //Create,resize and fill vector B
    vector <double > B;
    B.resize(width-1,0);
    for(int i=0;i<width-1;i++)
        B[i]=matrix[i][width-1];
    //Create matrix X (answer)
    vector <double > X;       // <--- x(k+1)
    X.resize(width-1,initial);
    //Create matrix X (previous answer)
    vector <double > _X;      // <--- x(k)
    _X.resize(width-1,0);
    double sum=0;

    //Start counting
    for(int it=0;it<iter;it++){
        for(int i=0;i<width-1;i++){
            sum=0;
            for(int j=0;j<width-1;j++){
                if(j!=i)
                    sum+=A[i][j] * _X[j]; //sum(AijXj)
            }
            sum=-sum;// -sum(AijXj)
            sum+=B[i]; // -sum(AijXj)+Bi
            sum/=A[i][i]; // ( -sum(AijXj)+Bi ) / Aii
            X[i]=sum; // X =
        }
        _X=X;
    }
    return X;
}
//-------------------------------------------------------------------Gauss Seidel
vector<double> Siedel(int iter,double initial){
    //Create,resize and fill matrix A
    vector < vector < double > > A;
    A.resize(width-1);
    for(int i=0;i<width-1;i++){
        A[i].resize(width-1,0);
        for(int j=0;j<width-1;j++)
            A[i][j]=matrix[i][j];
    }
    //Create,resize and fill vector B
    vector <double > B;
    B.resize(width-1,0);
    for(int i=0;i<width-1;i++)
        B[i]=matrix[i][width-1];
    //Create matrix X (answer)
    vector <double > X;            // <--- x(k+1)
    X.resize(width-1,initial);
    //Create matrix _X (previous answer)
    vector <double > _X;           // <--- x(k)
    _X.resize(width-1,initial);
    double sum1=0,sum2=0,sum=0;

    //Start counting
    for(int it=0;it<iter;it++){
        for(int i=0;i<width-1;i++){
            sum=sum1=sum2=0;
            for(int j=0;j<i-1;j++){
                    sum1+=A[i][j] * X[j];
            }
            sum1=-sum1;
            for(int j=i+1;j<width-1;j++){
                    sum2+=A[i][j] * _X[j];
            }
            sum2=-sum2;
            sum=sum1+sum2+B[i];
            sum/=A[i][i];
            X[i]=sum;
        }
        _X=X;
    }
    return X;
}


};
#endif // MYMATRIX_H
