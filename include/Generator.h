#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <cstdlib>
#include "State.h"
#include <Eigen/Dense>
#define def_limit 100000
#define prec 5
#include <limits>
#include <unistd.h>
#include <vector>

int indexOf(vector<int> p, int n){
    for(int i = 0; i < p.size(); i++){
        if(p[i]==n) return i;
    }
    return -1;
}

void print(vector< vector<double> > A, vector<double> B) {
    int n = A.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            (A[i][j] == 0 ) ? printf("%-2d\t", A[i][j]) : printf("%-2.2f\t", A[i][j]);
		}
		cout << "| " << B[i] << "\n";
    }
    cout << endl;
}

void fillBoard(vector<int> &p, int n){
    int number = -n;
    for(int i = 0; i < 2*n+1; i++){
        p[i] = number++;
    }
}

int mod(int a, int b) { return (a % b + b) % b; }

vector < vector <double > > generate_text(){
//WCZYTANIE DANYCH DO OBLICZANIA
    vector <vector <double> > matrix_a;
    fstream input("input_file.txt", std::ios_base::in);
    int board_size;
    input >> board_size;
    int fields_amount = board_size*2+1;
    int mushroom_amount;
    input >> mushroom_amount;
    mushroom_amount=0;
    int mushroom_locations[mushroom_amount];
    for(int i=0;i<mushroom_amount;i++)
        input >> mushroom_locations[i];
    int start_point_1,start_point_2;
    input >> start_point_1;
    input >> start_point_2;
    int dice_size;
    input >> dice_size;
    int dice_values[dice_size];
    int dice_propabilities[dice_size];
    for(int i=0;i<dice_size;i++)
        input >>dice_values[i];
    int dice_propabilities_sum=0;
    for(int i=0;i<dice_size;i++){
        input >>dice_propabilities[i];
        dice_propabilities_sum += dice_propabilities[i];
    }
    input.close();
    set<string> repetition; // set  to checking arleady calculated propabilities
    // map to mapping aready visited propabilities, incase of next meet copy values and factories
    map<string, int> repMap;
    map<string, int>::iterator it;
    pair<map<string,int>::iterator, bool> result;
    bool found;
    int equationas_amount; // amount of arleady generated equations
    vector<int> _dice(dice_size, 0);
    for(int i=0;i<dice_size;i++)
        _dice[i]=dice_values[i];
    vector<int> board(2*board_size+1, 0);
    fillBoard(board, board_size);
    int sumDicePropabilities = 0;
    for(int i=0;i<dice_size;i++)
        sumDicePropabilities+=dice_propabilities[i];
    vector <double> _dice_propabilities(dice_size);;
    for(int i=0;i< _dice_propabilities.size();i++)
        _dice_propabilities[i] = (double)dice_propabilities[i]/sumDicePropabilities;
    map<int, bool> grzyby;
    int s1 = -board_size;
    int s2 = board_size;
    for(int i = s1; i <= s2; i++){
        grzyby[i] = false;
        for(int j=0;j<mushroom_amount;j++){
            if(mushroom_locations[j]==i)
                grzyby[i]=true;
        }
    }
    vector<State> line(dice_size+1, State());
    int MAX_MX = 100000;
    vector< vector<State> > states(MAX_MX, line);
    int x = -board_size, y = board_size, player = 1, wsp=0;
    states[0][0] = State(player, x, y, wsp, 0, 0, grzyby,board_size,1);
    result = repMap.insert(pair<string, int>(states[0][0].toString(), wsp++));
    repetition.insert(states[0][0].toString());
    x = indexOf(board, x);
    y = indexOf(board, y);
    map<int, bool> tmpGrzyby;
    player = player%2 + 1;
    for(int i = 1; i < dice_size+1; i++){
        tmpGrzyby = grzyby;
        int tmpX = x, tmpY = y;
        int tmpG1 = 0, tmpG2 = 0;
        if(player == 2){
            tmpX += _dice[i-1];
            tmpX = board[mod(tmpX, fields_amount)];
            tmpY = board[mod(tmpY, fields_amount)];
        } else{
            tmpY += _dice[i-1];
            tmpY = board[mod(tmpY, fields_amount)];
            if(tmpGrzyby[tmpY]){
                tmpG2++;
                tmpGrzyby[tmpY] = false;
            }
            tmpX = board[mod(tmpX, fields_amount)];
        }
        states[0][i] = State(player, tmpX, tmpY, wsp, tmpG1, tmpG2, tmpGrzyby,board_size, _dice_propabilities[i-1]);
        if(tmpX == 0 || tmpY == 0){
            states[0][i].wsp = -1;
            wsp--;
        }
        result = repMap.insert(pair<string, int>(states[0][i].toString(), wsp++));
    }
// KONIEC WYPELNIANIA PIERWSZEGO WIERSZA
    int r = 0;
    int c = 1;
    int tmp_wsp;
    int i;
    int g1, g2;

    for(i = 1; i < MAX_MX ; i++){
        x = states[r][c].x;
        y = states[r][c].y;
        player = states[r][c].player;
        tmp_wsp = states[r][c].wsp;
        g1 = states[r][c].g1;
        g2 = states[r][c].g2;
        if(r == i) break;
        c = c%dice_size+ 1;
        if (c == 1) r++;
        states[i][0] = State(player, x, y, tmp_wsp, g1, g2, tmpGrzyby,board_size,1);
        found = repetition.count(states[i][0].toString());
        if(found == 1 || (states[i][0].x == 0 || states[i][0].y == 0)){
            i--;
            continue;
        } else {
            repetition.insert(states[i][0].toString());
        }
        x = indexOf(board, x);
        y = indexOf(board, y);
        player = player%2 + 1;

        for(int j = 1; j < dice_size+1; j++){
            int tmpX = x, tmpY = y;
            int tmpG1 = g1, tmpG2 = g2;
            map<int,bool> newGrzyby = tmpGrzyby;
            if(player == 2){
                tmpX += _dice[j-1];
                tmpX = board[mod(tmpX, fields_amount)];
                tmpY = board[mod(tmpY, fields_amount)];

            } else{
                tmpY += _dice[j-1];
                tmpY = board[mod(tmpY, fields_amount)];
                tmpX = board[mod(tmpX, fields_amount)];
            }
            states[i][j] = State(player, tmpX, tmpY, wsp, tmpG1, tmpG2, newGrzyby,board_size,_dice_propabilities[j-1]);
            if(tmpX == 0 || tmpY == 0){
                states[i][j].wsp = -1;
                continue;
            }

            result = repMap.insert(pair<string, int>(states[i][j].toString(), states[i][j].wsp));

            if(result.second == 0){
                it = repMap.find(states[i][j].toString());
                states[i][j].wsp = it->second;
                continue;
            }
            wsp++;
        }
    }
    equationas_amount = i;
    matrix_a.resize(equationas_amount);
    for(int i=0;i<matrix_a.size();i++)
        matrix_a[i].resize(equationas_amount+1,0.0);
    for(int i=0;i<equationas_amount;i++){
        for(int j=0;j<equationas_amount;j++){
            if(i==j)
                matrix_a[i][j]=1;
        }
    }
    int xy=0;
    bool testt=true;
    for(int i=0;i<equationas_amount;i++){
        for(int j=0;j<dice_size+1;j++){
            testt=true;
            xy=0;
            if(states[i][j].player==2 && states[i][j].x==0){
                matrix_a[i][equationas_amount] = states[i][j].wage;
               }
            else{
                xy=0;
                bool testtt=false;
                while(testt && xy<equationas_amount){
                    if(states[i][j].player==states[xy][0].player &&
                       states[i][j].x==states[xy][0].x &&
                       states[i][j].y==states[xy][0].y
                       ){
                        testtt=true;
                        testt=false;

                       }
                    xy++;
                }
                if(testtt)
                    if(states[i][j].wage != 1)
                        matrix_a[i][xy-1]=-states[i][j].wage;
                testtt=false;
            }
        }
    }
    ofstream oF("equotations.txt");
    for(int i = 0; i < equationas_amount; i++){
        cout << i << ": ";

        for(int j = 0; j < dice_size+1; j++){
            if (j==0) oF<<endl << i+1<< ": ";
            if( j!= 0 && j!= 1 ){ cout << setw(5) << left <<  " + "; oF << " + ";}
            int zero_one =2;
            if(states[i][j].player==1 && states[i][j].x==0) zero_one = 1;
            if(states[i][j].player==1 && states[i][j].y==0) zero_one = 0;
            if(states[i][j].player==2 && states[i][j].x==0) zero_one = 1;
            if(states[i][j].player==2 && states[i][j].y==0) zero_one = 0;
            states[i][j].print();
            oF << states[i][j].to_stringg(zero_one);
            if(j == 0) {cout << setw(5) << left << " = ";oF << " = ";}
        }
    }
    cout<< "..................."<<endl;
        typedef map<string,int>::const_iterator MapIterator;
        map<int,string> mymapp;
        for (MapIterator iter = repMap.begin(); iter != repMap.end(); iter++){
            mymapp.insert(pair<int,string>(iter->second,iter->first));
            cout << iter->second << ": " << iter->first << endl;
        }
        return matrix_a;

}



#endif // GENERATOR_H
