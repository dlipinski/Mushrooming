#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <unistd.h>
#include "Field.h"
#include "Dice.h"
#include "Player.h"
#include "MyMatrix.h"
#include "MyFunctions.h"
#include "State.h"
#include "MonteCarlo.h"
#include "Generator.h"
#include <Eigen/Dense>
#define def_limit 100000
#define prec 5

typedef std::numeric_limits< double > dbl;

using namespace std;


int main()
{
 vector < vector <double > > wynik;

    wynik = generate_text();
    print_to_file(wynik,"generated_matrix.txt");
    print_to_table(wynik,"generated_matrix.html");

vector <vector <double> > matrix_a;
    matrix_a.resize(wynik.size());
    for (int i=0; i<matrix_a.size(); i++)
        matrix_a[i].resize(wynik.size(), 0);
    for(int i=0;i<matrix_a.size();i++)
        for(int j=0;j<matrix_a.size();j++)
             matrix_a[i][j] = wynik[i][j];

//wczytanie b
    vector <double>  matrix_b;
    int size = wynik.size();
    matrix_b.resize(size,0);
    for(int i=0;i<matrix_b.size();i++)
        matrix_b[i]=wynik[i][size-1];

//stworzenie ostatecznej macierzy
    vector <vector <double> > matrix;
    int rows = matrix_a.size();
    int cols = rows+1;
    matrix.resize(rows);
    for (int i=0; i<rows; i++)
        matrix[i].resize(cols, 0);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols-1;j++)
        matrix[i][j] = matrix_a[i][j];
    for(int i=0;i<rows;i++)
        matrix[i][cols-1] = matrix_b[i];

//stworzenie macierzy do obliczen i wektorow do wynikow;
    Eigen::MatrixXd eigen_a(rows,rows);
    for(int i=0;i<rows;i++)
        for(int j=0;j<rows;j++)
            eigen_a(i,j) = matrix_a[i][j];
    Eigen::VectorXd eigen_b(rows);
    for(int i=0;i<rows;i++)
        eigen_b(i)=matrix_b[i];
    Eigen::VectorXd eigen_ans(rows);
    vector<double> eigen_ans_v; eigen_ans_v.resize(rows);

    Eigen::SparseMatrix<double> sparseigen_a(rows,rows);
    for(int i=0;i<rows;i++)
        for(int j=0;j<rows;j++)
            sparseigen_a.insert(i,j) = matrix_a[i][j];
    Eigen::SparseLU <Eigen::SparseMatrix<double> > solver;
    solver.analyzePattern(sparseigen_a);
    solver.factorize(sparseigen_a);
    Eigen::VectorXd sparseigen_b(rows);
    for(int i=0;i<rows;i++)
        sparseigen_b[i]=matrix_b[i];
    Eigen::VectorXd sparseigen_ans(rows);
    vector<double> sparseigen_ans_v; sparseigen_ans_v.resize(rows);

    MyMatrix gauss(rows,cols);
    gauss = matrix;
    vector<double> gauss_ans; gauss_ans.resize(rows,0);


    MyMatrix gauss_opt(rows,cols);
    gauss_opt = matrix;
    vector<double> gauss_opt_ans; gauss_opt_ans.resize(rows,0);

    MyMatrix jacob(rows,cols);
    jacob = matrix;
    vector<double> jacob_ans; jacob_ans.resize(rows,0);

    MyMatrix seidel(rows,cols);
    seidel = matrix;
    vector<double> seidel_ans; seidel_ans.resize(rows,0);

    cout << "CALCULATING" << endl;

    cout << "\t" <<"Eigen...";
    clock_t eigen_s= clock();
    eigen_ans =  eigen_a.partialPivLu().solve(eigen_b);

    clock_t eigen_e= clock();
    cout << "Done "<<endl;

    cout << "\t" <<"SparsEigen...";
    clock_t sparseigen_s= clock();
    sparseigen_ans =  solver.solve(sparseigen_b);
    clock_t sparseigen_e= clock();
    cout << "Done "<<endl;

    cout << "\t" <<"Gaus partial...";
    clock_t gauss_s= clock();
    gauss_ans = gauss.Gauss_partial();
    clock_t gauss_e= clock();
    cout << "Done "<<endl;

    cout << "\t" <<"Gaus partial optimized...";
    clock_t gauss_opt_s= clock();
    gauss_opt_ans = gauss_opt.Gauss_partial();
    clock_t gauss_opt_e= clock();
    cout << "Done "<<endl;

    cout << "\t" <<"Jacob...";
    clock_t jacob_s= clock();
    jacob_ans = jacob.Jacobi(1000,1);
    clock_t jacob_e= clock();

    cout << "Done "<<endl<<"\t" <<"Seidel...";
    clock_t seidel_s= clock();
    seidel_ans = seidel.Siedel(1000,1);
    clock_t seidel_e= clock();
    cout << "Done "<<endl;

    long int eigen_t = eigen_e - eigen_s;
    long int sparseigen_t = sparseigen_e - sparseigen_s;
    long int gauss_t = gauss_e - gauss_s;
    long int gauss_opt_t = gauss_opt_e - gauss_opt_s;
    long int jacob_t = jacob_e - jacob_s;
    long int seidel_t = seidel_e - seidel_s;

    cout << "TIMES" << endl;
    cout << fixed <<"\teigen     : "<<eigen_t<<endl;
    cout << fixed <<"\tsparseigen: "<<sparseigen_t<<endl;
    cout << fixed <<"\tgauss     : "<<gauss_t<<endl;
    cout << fixed <<"\tgauss_opt : "<<gauss_opt_t<<endl;
    cout << fixed <<"\tjacob     : "<<jacob_t<<endl;
    cout << fixed <<"\tseidel    : " << seidel_t<<endl;

    vector<double> sparseigen_lol(rows);
    for(int i=0;i<rows;i++)
        sparseigen_lol[i]=sparseigen_ans(i);
    for(int i=0;i<rows;i++)
        eigen_ans_v[i]=eigen_ans(i);
    cout << "ERRORS"<<endl;
    cout <<"\tsparseigen : ";biggest_diff(eigen_ans_v,sparseigen_lol);
    cout <<"\tgauss : ";biggest_diff(eigen_ans_v,gauss_ans);
    cout <<"\tgauss_opt : ";biggest_diff(eigen_ans_v,gauss_opt_ans);
    cout <<"\tjacob : ";biggest_diff(eigen_ans_v,jacob_ans);
    cout <<"\tseidel: ";biggest_diff(eigen_ans_v,seidel_ans);

    cout << "ANSWERS" << endl;
    cout << "\tCalculated: "<<sparseigen_ans(0)<<endl;

    double  mc = monte_carlo("input_file.txt");

    cout.precision(dbl::max_digits10);
    cout<<fixed<<endl<<"\tSimulated: " <<mc;
    cout <<endl<<"Scientific simulated: "<< scientific << mc<<endl;

    return 0;
}



