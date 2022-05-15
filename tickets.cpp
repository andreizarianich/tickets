#include "tickets.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

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

void Tickets::Start()
{
    Tickets::getInstance().ReadHalls();
    Tickets::getInstance().PrintMenu();
}

char Tickets::CheckInput()
{
    char user_input;
    std::cout<< "Please choose an option: "<<std::endl;
    std::cin.get(user_input); //if entered more than one char - prints menu for every next char (which is a bug)
    std::cin.ignore();
    return user_input;
}

void Tickets::PrintMenu()
{
    std::cout<< "--------- Welcome ---------\n1: Buy a ticket\n2: Check for free seats";
    std::cout<< "\n3: Add a new event";
    std::cout<< "\n0: Exit\n---------------------------\n";
    switch (Tickets::getInstance().CheckInput())
    {
    case '1':
        Tickets::getInstance().BuyTicket();
        break;
    case '2':
        Tickets::getInstance().PrintFreeSeats();
        break;
    case '3':
        Tickets::getInstance().NewAct();
        break;
    case '0':
        break;        
    default:
        Tickets::getInstance().PrintMenu();
        break;
    }
}

void Tickets::NewAct()
{
    char name[100], date[100], file_name[206];
    int hall;
    std::cout<<"Name: ";
    std::cin.getline(name, 100);
    std::cout<<"Date (dd.mm.yyyy): ";
    std::cin.getline(date, 100);
    std::cout<<"Hall#: ";
    std::cin>> hall;

    strcpy(file_name, name);
    strcat(file_name, "-");
    strcat(file_name, date);
    strcat(file_name, ".txt");

    //date has to be specifically in day.month.year format! day/month/year breaks the file name (because of '/')

    std::ofstream file(file_name);
    if(file.is_open())
    {
        if (hall <= this->number_of_halls+1)
        {
            file<<hall<<"\n";
            for (int i = 0; i < this->getRows(hall-1); i++)
            {
                for (int j = 0; j < this->getSeats(hall-1); j++)
                {
                    file<<"0";
                }
                file<<"\n";
                
            }
        }
    }    
    else
        std::cout<<"Error! Most likely because \"/\" was entered.\n";
    file.close();
    std::cout<< "Done!"<<std::endl;
    std::cin.ignore();
    Tickets::getInstance().PrintMenu();
}

int Tickets::getRows(const int& hall)
{
    return this->halls[hall][0];
}

int Tickets::getSeats(const int& hall)
{
    return this->halls[hall][1];
}

void Tickets::BuyTicket()
{
    char name[100], date[100], file_name[206];
    int hall, row, seat;

    std::cout<<"Act name: ";
    std::cin.getline(name, 100);

    std::cout<<"Date (dd.mm.yyy.): ";
    std::cin.getline(date, 100);

    std::cout<<"Row: ";
    std::cin>>row;

    std::cout<<"Seat: ";
    std::cin>>seat;

    std::cout<< "Thank you for your purchase!\n";

    strcpy(file_name, name);
    strcat(file_name, "-");
    strcat(file_name, date);
    strcat(file_name, ".txt");

    std::ifstream file(file_name);
    char** act;
    if(file.is_open())
    {
        file>>hall;
        act = new char*[this->getRows(hall-1)+1];
        for (int i = 0; i < this->getRows(hall-1); i++)
        {
            act[i] = new char[this->getSeats(hall-1)+1];
            for (int j = 0; j < this->getSeats(hall-1); j++)
            {
                file.get(act[i][j]);
            }
        }
        act[row-1][seat-1] = '1';  
    }    
    else
        std::cout<<"Act not found!\n";
    file.close();    

    std::ofstream file_p(file_name);
    if(file_p.is_open())
    {
        file_p<<hall;
        for (int i = 0; i < this->getRows(hall-1); i++)
        {
            for (int j = 0; j < this->getSeats(hall-1); j++)
            {
                file_p<<act[i][j];
            }
        }
    }    
    else
        std::cout<<"Act not found!\n";
    for (int i = 0; i < this->getRows(hall-1); i++)
    {
        delete[] act[i];
    }   
    delete[] act;  
    file_p.close(); 
    std::cin.ignore();
    Tickets::getInstance().PrintMenu();       
}

void Tickets::PrintFreeSeats()
{
    char name[100], date[100], file_name[206], temp;
    int hall;

    std::cout<<"Act name: ";
    std::cin.getline(name, 100);

    std::cout<<"Date (dd.mm.yyy.): ";
    std::cin.getline(date, 100);

    strcpy(file_name, name);
    strcat(file_name, "-");
    strcat(file_name, date);
    strcat(file_name, ".txt");

    std::ifstream file(file_name);
    if(file.is_open())
    {
        file>>hall;
        for (int i = 0; i < this->getRows(hall-1); i++)
        {
            std::cout<<i+1<<": ";
            for (int j = 0; j < this->getSeats(hall-1); j++)
            {
                file.get(temp);
                if (temp == '0')
                    std::cout <<j+1<<" ";
            }
            std::cout<<std::endl;
        }
    }    
    else
        std::cout<<"Act not found!\n";
    file.close();  
    //std::cin.ignore();
    Tickets::getInstance().PrintMenu();   
}
