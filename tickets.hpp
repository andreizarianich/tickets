#ifndef __TICKETS_HPP
#define __TICKETS_HPP

class Tickets
{
    private:

    //level 0

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

    void StartInternal();

    //reads halls.txt
    void ReadHalls();
    
    char CheckInput();

    void PrintMenu();

    //deallocates memory if needed
    ~Tickets();

    public:
    
    //level 1

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

    //this is made to replace Tickets::getInstance().Start() with Tickets::Start()
    static void Start() { return getInstance().StartInternal(); };

};

#endif