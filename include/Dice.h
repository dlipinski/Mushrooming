#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

class Dice
{
    public:
        std::vector<int> walls;
        Dice();
        Dice(int walls_amount_in) {walls_amount = walls_amount_in;}

        void setWalls(int values[],int probabilities[]){
            int check=0;
            for(int i=0;i<walls_amount;i++)
                check+=probabilities[i];
            walls.resize(check,0);
            int ite=0;
            for (int i=0;i<walls_amount;i++){
                real_walls_amount+=probabilities[i];
                for(int j=0;j<probabilities[i];j++)
                    walls[ite++] = values[i];
            }
        }
        int getRealWallsAmount(void){
            return real_walls_amount;
        }
        int getSize(void){
            return walls_amount;
        }
        int throwDice(void){
            return walls[rand() % real_walls_amount];
        }
        void print_real_walls(){
            for(int i=0;i< real_walls_amount;i++)
                std::cout<<walls[i]<<std::endl;
        }

    private:
        int real_walls_amount=0;
        int walls_amount=0;

};

#endif // DICE_H
