#include <iostream>
#include <fstream>

int main()
{
    std::ifstream hall_List("halls.txt"); 

    if (!hall_List.is_open())
    {
        std::cout << "Problem while opening halls.txt" << std::endl;
        return 1;
    }

    char temp[10];

    while (!hall_List.eof())
    {
        hall_List >> temp;
        std::cout << temp << std::endl;
    }
    

    hall_List.close();

    return 0;
}