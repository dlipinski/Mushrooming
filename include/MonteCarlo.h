#ifndef MONTECARLO_H
#define MONTECARLO_H
#define def_limit 100000
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits.h>
#include <vector>

#include "Field.h"
#include "Dice.h"
#include "Player.h"

using namespace std;

double monte_carlo(string file_name){
//---------------------------------------------------READ INPUT DATA
    fstream input(file_name, std::ios_base::in);
    int board_size;
    input >> board_size;
    int mushroom_amount;
    input >> mushroom_amount;
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
    for(int i=0;i<dice_size;i++)
        input >>dice_propabilities[i];
/*
//--------------------------------------------------PRINT INTPUT DATA
    cout << "            MUSHROOMING             " << endl;
    cout << "------------------------------------" << endl;
    cout << "Board size: "<<board_size<<endl;
    cout << "Mushroom amount: " << mushroom_amount << endl;
    cout << "Mushroom locations: ";
    for(int i=0;i<mushroom_amount;i++)
        cout<<mushroom_locations[i]<<" ";
    cout << endl;
    cout << "Start points: " << start_point_1 << " " << start_point_2 << endl;
    cout << "Dice size: " << dice_size << endl;
    cout << "Dice walls (Value,Probability):" << endl;
    for(int i=0;i<dice_size;i++)
        cout << dice_values[i] << "," << dice_propabilities[i] << endl;
    cout << "------------------------------------" << endl;
*/
//--------------------------------------------------SET PLAYERS AND DICE
    //cout << "Setting board..." ;
    int fields_amount = board_size*2+1;
    int indexes[fields_amount];
    int min_index = -fields_amount;
    for(int i=0;i<fields_amount;i++)
        indexes[i]=min_index++;
    Field board[board_size*2+1];
    for (int i=0;i<=fields_amount;i++){
        board[i].setIndex(indexes[i]);
        for(int j=0;j<mushroom_amount;j++)
            if(indexes[i]==mushroom_locations[j])
                board[i].setMushroom();
    }
    //cout <<"Done"<<endl;
    //cout << "Setting players...";
    Player player[2];
    player[0].setBoardSize(board_size);

    player[1].setBoardSize(board_size);
    //cout <<"Done"<<endl;
    //cout << "Setting dice...";
    Dice dice(dice_size);
    dice.setWalls(dice_values,dice_propabilities);



//---------------------------------------------------------------------------------------MONTE CARLO TESTING
//--------------------------------------------------START GAME

    cout.precision(0);
    srand (time(NULL));
    unsigned long long licznik =0;
    int g = 1; //player number
    int movement=0;
    long long int winner1=0;
    long long int winner2=0;
    int limit = def_limit;
    limit = 1000000;
    int i=0;
    int max_movement=0;
    while(i++<limit){
       // usleep(10);
        //cout << "\r" << fixed <<((double)(++licznik)/limit)*100<<"%";
        player[0].setPosition(start_point_1);
        player[1].setPosition(start_point_2);
        while (true){
                if(g==0) g=1; else g=0;

                //cout << "-----" << endl;
                //cout<<"player"<<g+1<<": "<<player[g].getPosition()<<"("<<player[g].getMushroomAmount()<<")"<<endl;
               // usleep(1);
                movement = dice.throwDice();
                //cout <<"throws: "<< movement<< endl ;
                //cout<<endl<<"dice: "<<movement;
               // cout << movement << endl;
                player[g].moveBy(movement);
                //cout<<"player"<<g+1<<": "<<player[g].getPosition()<<"("<<player[g].getMushroomAmount()<<")"<<endl;
                for(int i=0;i<fields_amount;i++)
                  if ( board[i].getIndex()==player[g].getPosition() && board[i].isMushroom()) { player[g].addMushroom(); board[i].setMushroom(false); };

                //cout<<endl<<"player"<<g<<": "<<player[g].getPosition()<<endl;
                if(player[g].getPosition()==0){
                    if (player[0].getMushroomAmount()==player[1].getMushroomAmount()){
                        if (g==0) winner1++;
                        else winner2++;
                    }
                    else
                        if(player[0].getMushroomAmount()>player[1].getMushroomAmount())
                            winner1++;
                        else
                            winner2++;
                        break;
                }
        }
    }

    //cout <<endl<< "Player 1:" << winner1 << "/" << limit<<endl;
    return (double)winner1/(double)limit;



}

double monte_carlo_without_mushrooms(string file_name){
//---------------------------------------------------READ INPUT DATA
    fstream input(file_name, std::ios_base::in);
    int board_size;
    input >> board_size;
    int mushroom_amount;
    input >> mushroom_amount;
    mushroom_amount =0;
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
    for(int i=0;i<dice_size;i++)
        input >>dice_propabilities[i];
/*
//--------------------------------------------------PRINT INTPUT DATA
    cout << "            MUSHROOMING             " << endl;
    cout << "------------------------------------" << endl;
    cout << "Board size: "<<board_size<<endl;
    cout << "Mushroom amount: " << mushroom_amount << endl;
    cout << "Mushroom locations: ";
    for(int i=0;i<mushroom_amount;i++)
        cout<<mushroom_locations[i]<<" ";
    cout << endl;
    cout << "Start points: " << start_point_1 << " " << start_point_2 << endl;
    cout << "Dice size: " << dice_size << endl;
    cout << "Dice walls (Value,Probability):" << endl;
    for(int i=0;i<dice_size;i++)
        cout << dice_values[i] << "," << dice_propabilities[i] << endl;
    cout << "------------------------------------" << endl;
*/
//--------------------------------------------------SET PLAYERS AND DICE
    //cout << "Setting board..." ;
    int fields_amount = board_size*2+1;
    int indexes[fields_amount];
    int min_index = -fields_amount;
    for(int i=0;i<fields_amount;i++)
        indexes[i]=min_index++;
    Field board[board_size*2+1];
    for (int i=0;i<=fields_amount;i++){
        board[i].setIndex(indexes[i]);
        for(int j=0;j<mushroom_amount;j++)
            if(indexes[i]==mushroom_locations[j])
                board[i].setMushroom();
    }
    //cout <<"Done"<<endl;
    //cout << "Setting players...";
    Player player[2];
    player[0].setBoardSize(board_size);

    player[1].setBoardSize(board_size);
    //cout <<"Done"<<endl;
    //cout << "Setting dice...";
    Dice dice(dice_size);
    dice.setWalls(dice_values,dice_propabilities);



//---------------------------------------------------------------------------------------MONTE CARLO TESTING
//--------------------------------------------------START GAME

    cout.precision(0);
    srand (time(NULL));
    unsigned long long licznik =0;
    int g = 1; //player number
    int movement=0;
    long long int winner1=0;
    long long int winner2=0;
    int limit = def_limit;
    int i=0;
    int max_movement=0;
    while(i++<limit){
       // usleep(10);
        //cout << "\r" << fixed <<((double)(++licznik)/limit)*100<<"%";
        player[0].setPosition(start_point_1);
        player[1].setPosition(start_point_2);
        while (true){
                if(g==0) g=1; else g=0;

                //cout << "-----" << endl;
                //cout<<"player"<<g+1<<": "<<player[g].getPosition()<<"("<<player[g].getMushroomAmount()<<")"<<endl;
               // usleep(1);
                movement = dice.throwDice();
                //cout <<"throws: "<< movement<< endl ;
                //cout<<endl<<"dice: "<<movement;
               // cout << movement << endl;
                player[g].moveBy(movement);
                //cout<<"player"<<g+1<<": "<<player[g].getPosition()<<"("<<player[g].getMushroomAmount()<<")"<<endl;
                for(int i=0;i<fields_amount;i++)
                  if ( board[i].getIndex()==player[g].getPosition() && board[i].isMushroom()) { player[g].addMushroom(); board[i].setMushroom(false); };

                //cout<<endl<<"player"<<g<<": "<<player[g].getPosition()<<endl;
                if(player[g].getPosition()==0){
                    if (player[0].getMushroomAmount()==player[1].getMushroomAmount()){
                        if (g==0) winner1++;
                        else winner2++;
                    }
                    else
                        if(player[0].getMushroomAmount()>player[1].getMushroomAmount())
                            winner1++;
                        else
                            winner2++;
                        break;
                }
        }
    }

    //cout <<endl<< "Player 1:" << winner1 << "/" << limit<<endl;
    return (double)winner1/(double)limit;



}


#endif // MONTECARLO_H
