#ifndef FIELD_H
#define FIELD_H


class Field
{
    public:

        Field();

        void setMushroom(void){
            is_mushroom = true;
        }

        bool isMushroom(void){
            return is_mushroom;
        }
        void setMushroom(bool change){
            is_mushroom=change;
        }
        void setIndex(int index_in) { index = index_in; }
        int getIndex(void) { return index;}
    private:
        int index=0;
        bool is_mushroom=false;
};

#endif // FIELD_H
