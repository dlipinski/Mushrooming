#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <iomanip>
#include <cmath>
#include <string>
#include "State.h"
using namespace std;

void biggest_diff (vector<double> eigen, vector<double> meth ){

    cout <<  abs(eigen[0]-meth[0])<<endl;

}

void print_to_file(vector < vector <double > > a,string file_name){
    ofstream oF(file_name);

    for(int i=0;i<a.size();i++){
        for(int j=0;j<a[0].size();j++)
            oF << " " << a[i][j];
        oF << endl;
    }

    oF.close();
}

void print_to_table(vector < vector <double > > a,string file_name){
    ofstream oF(file_name);
    oF << "<table style=\"border:1px solid black; border-collapse: collapse;\">" << endl;
    oF << "<tr style=\"border:1px solid black; border-collapse: collapse;\">"<<endl;;
    for(int i=0;i<a[0].size()-1;i++){
        oF << "<th style=\"width:5px\"> x" <<i+1<<"</th>"<<endl;
    }
    oF << "<th style=\"width:5px\">" << "B" << "</th>"<<endl;
    oF << "</tr>" << endl;
    for(int i=0;i<a.size();i++){
        oF << "<tr style=\"border:1px solid black; border-collapse: collapse;\">" << endl;
        for(int j=0;j<a[0].size();j++){
            if(a[i][j]==1) oF << "<td  style=\"align:center;border:1px solid black; border-collapse: collapse;background:blue;\">" << endl;
            else
            if(a[i][j]!=0)oF << "<td  style=\"align:center;border:1px solid black; border-collapse: collapse;background:lightgreen;\">" << endl;
            else oF << "<td  style=\"align:center;border:1px solid black; border-collapse: collapse;\">"<<endl;
            oF << a[i][j];
            oF << "</td>" << endl;
        }
        oF << "</tr>" << endl;
    }
    oF << "</table>" << endl;
    oF.close();
}

 bool compare_state(State arg,State arg1) {
            if(
               //arg1.player == arg.player &&
               arg1.x == arg.x &&
               arg1.y == arg.y
               )
                return true;
            else
                return false;
        }
#endif // MYFUNCTIONS_H
