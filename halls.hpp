#ifndef __HALL_HPP
#define __HALL_HPP

struct Halls
{
    private:

    //level 0
    char*** halls;
    int number_of_halls;
    bool delete_hall_list;

    public:

    //level 1

    //create halls from text file on execution
    Halls();

    ~Halls();

    char* getRow(int hall, int row) const { return this->halls[hall][row]; };
    char checkSeat(int hall, int row, int seat) const { return this->halls[hall][row][seat]; };

    //change seat occupation
    void setSeatOccupied(int hall, int row, int seat) { this->halls[hall][row][seat] = '1';};
    void setSeatFree(int hall, int row, int seat) { this->halls[hall][row][seat] = '0';};

};

#endif