#include "tickets.hpp"
#include <fstream>
#include <iostream>

void Tickets::ReadHalls()
{
    std::ifstream hall_list("halls.txt");

    if (!hall_list.is_open())
        std::cout<< "Couldn't find or open halls.txt"<<std::endl;
    else
    {
        char temp[20];
        this->delete_hall_list = true;

        //counting the number of halls and allocating them
        while (!hall_list.eof())
        {
            hall_list.getline(temp, 20);
            this->number_of_halls++;
        }
        this->halls = new int*[this->number_of_halls + 1];

        //resetting to start of file 
        hall_list.seekg(0, std::ios::beg);

        int temp_int, hall_counter = 0;
        
        //getting the numbers of rows and allocating them
        while (hall_counter!=this->number_of_halls)
        {
            hall_list >> temp_int; //skipping first number for hall
            hall_list >> temp_int; //reading second number for rows

            this->halls[hall_counter] = new int[2];
            this->halls[hall_counter][0] = temp_int;

            hall_list >> temp_int; //reading third number for seats
            this->halls[hall_counter][1] = temp_int;

            std::cout<< this->halls[hall_counter][0] << " - " << this->halls[hall_counter][1] << std::endl;
            hall_counter++;
        }
    }
    hall_list.close();
}

Tickets::~Tickets()
{
    if (this->delete_hall_list == true)
    {
        for (int i = 0; i < this->number_of_halls; i++)
        {
            delete[] this->halls[i];
        }
        delete[] this->halls;
    }
}

void Tickets::StartInternal()
{
    Tickets::getInstance().ReadHalls();

    do
    {
        Tickets::getInstance().PrintMenu();
    } while (Tickets::getInstance().CheckInput()!='0');

}

char Tickets::CheckInput()
{
    char user_input;
    std::cout<< "Please choose an option: \n";
    std::cin.get(user_input);
    return user_input;
}

void Tickets::PrintMenu()
{
    std::cout<< "--------- Welcome ---------\n1: Buy a ticket\n2: Reserve a ticket\n3: Check for free seats";
    std::cout<< "\n4: Cancel reservation\n5: See list of reservations\n6: See list of sold tickets\n7: Add a new event";
    std::cout<< "\n0: Exit\n---------------------------\n";
}