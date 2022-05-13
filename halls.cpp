#include "halls.hpp"
#include <fstream>
#include <iostream>

const size_t MAX_HALLS = 20;
const size_t MAX_LINE_LENGTH = 100;

Halls::Halls()
{
    this->delete_hall_list = false;
    std::ifstream hall_list("halls.txt");

    if (!hall_list.is_open())
        std::cout<< "Couldn't find or open halls.txt"<<std::endl;
    else
    {
        char temp[MAX_LINE_LENGTH];
        this->number_of_halls = 0;
        this->delete_hall_list = true;

        //counting the number of halls and allocating them
        while (!hall_list.eof())
        {
            hall_list.getline(temp, MAX_LINE_LENGTH);
            this->number_of_halls++;
        }
        this->halls = new char**[this->number_of_halls + 1];

        //resetting to start of file 
        hall_list.seekg(0, std::ios::beg);

        int read_rows, read_seats, reset_pos = 1, hall_counter = 0; // reset_pos is used for getting the number of rows from the hall list file
        
        //getting the numbers of rows and allocating them
        while (!hall_list.eof())
        {
            hall_list >> read_rows;
            if (reset_pos++ == 2)
            {
                reset_pos = 1;
                this->halls[hall_counter] = new char*[read_rows + 1];
                hall_list >> read_seats;
                for (int i = 0; i < read_rows; i++)
                {
                    this->halls[hall_counter][i] = new char[read_seats + 1];
                    for (int j = 0; j < read_seats; j++)
                    {
                        this->halls[hall_counter][i][j] = '0'; //initializing all seats with 0, which means free
                    }
                }
                hall_counter++;
            }
        }
    }
    hall_list.close();
}

Halls::~Halls()
{
    if (this->delete_hall_list == true)
    {
        std::ifstream hall_list("halls.txt");

        int read_rows, read_seats, reset_pos = 1, hall_counter = 0;

        while (!hall_list.eof())
        {
            hall_list >> read_rows;
            if (reset_pos++ == 2)
            {
                reset_pos = 0;

                hall_list >> read_seats;

                for (int i = 0; i < read_rows; i++)
                {
                    delete[] this->halls[hall_counter][i];
                }

                delete[] this->halls[hall_counter++];
            }
        }
        delete[] this->halls;
        hall_list.close();
    }
}