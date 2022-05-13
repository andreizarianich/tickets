#include <iostream>
#include <fstream>
#include "halls.hpp"

void PrintMenu()
{
    std::cout<< "--------- Welcome ---------\n1: Buy a ticket\n2: Reserve a ticket\n3: Check for free seats";
    std::cout<< "\n4: Cancel reservation\n5: See list of reservations\n6: See list of sold tickets\n7: Add a new event";
    std::cout<< "\n0: Exit\n---------------------------\n";
}

char CheckInput()
{
    char user_input;
    std::cout<< "Please choose an option: \n";
    std::cin.get(user_input);
    return user_input;
}

int main()
{
    
    Halls halls;

    do
    {
        PrintMenu();
    } while (CheckInput()!='0');

    return 0;
}