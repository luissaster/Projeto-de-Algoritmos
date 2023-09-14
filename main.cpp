#include <iostream>
#include <string>
#include <chrono>
#include "interface.hpp"
#include "fileManager.hpp"
#include "algorithms.hpp"

int main(void)
{
    Interface ui;
    FileManager fm;
    Algorithms algorithm;
    std::string fileAddress;
    std::vector<int> arr;
    int algorithmChoice, inputChoice, inputSize;

    do
    {
        ui.showTitle();

        algorithmChoice = ui.chooseAlgorithm();
        if (algorithmChoice == 0) // End application
        {
            return 0;
        }
        else if (algorithmChoice > 0 && algorithmChoice <= 3) // Replace 2 with the number of the last algorithm (check interface.hpp)
        {
            inputChoice = ui.chooseInputStyle();
            inputSize = ui.chooseInputSize();
            fileAddress = fm.generateFile(algorithmChoice, inputChoice, inputSize);
            arr = fm.loadFile(fileAddress);
            ui.runAlgorithm(arr, algorithmChoice, inputChoice, inputSize);
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }

    } while (algorithmChoice != 0);

    return 0;
}