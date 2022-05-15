#ifndef __TICKETS_HPP
#define __TICKETS_HPP

class Tickets
{
    private:

    //array of integers to hold values from halls.txt
    int** halls;

    //stores the number of halls read from halls.txt
    int number_of_halls;

    //tells the destructor whether there is memory to deallocate (if opened halls.txt successfully)
    bool delete_hall_list;

    //create an array of integers from halls.txt to hold its values (so the program has them even if something happens to the text file during runtime)
    Tickets()
    {
        this->number_of_halls = 0;
        this->delete_hall_list = false;
    }

    //reads halls.txt
    void ReadHalls();
    
    char CheckInput();

    void PrintMenu();

    //deallocates memory if needed
    ~Tickets();

    //AddEvent saves event to text file, and then just open it like halls.txt - if you can't - the event doesn't exist
    void NewAct();

    void PrintFreeSeats();

    void BuyTicket();

    int getRows(const int& hall);
    int getSeats(const int& hall);

    public:

    //code snippet taken from github (triffon/oop-2021-22/practicum/4/Week09-StaticAndTemplates/snippets/03-singleton.cpp)
    //restricting copy
    Tickets (const Tickets&) = delete;

    //restricting assignment
    Tickets& operator =(const Tickets&) = delete;
    
    //access the tickets singleton
    static Tickets& getInstance()
    {
        //the instance
        static Tickets object;

        return object;
    }
    //end of code snippet
    
    void Start();

};

#endif