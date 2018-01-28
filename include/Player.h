#ifndef PLAYER_H
#define PLAYER_H



class Player
{
    public:
        Player();
        Player(int board_size_in) { board_size=board_size_in;} //we get field amount to

        void setPosition(int position_in) { position = position_in; }
        int  getPosition(void) { return position;}
        void setBoardSize(int board_size_in) { board_size = board_size_in; }

        void moveBy(int number) {
            int number1 =0;
            if (number<0) number1=-number;
            for(int i=0;i<number1;i++){
                if(number >0){
                    position++;
                    if(position==board_size+1) position = -board_size;
                }
                if(number <0){
                    position --;
                    if(position==-board_size-1)position = board_size;
                }

            }
        }


        void addMushroom(void){ mushroom_amount++; }

        int getMushroomAmount(void){ return mushroom_amount; }


    private:
        int position;
        int mushroom_amount =0;

        int board_size=0;
};

#endif // PLAYER_H
