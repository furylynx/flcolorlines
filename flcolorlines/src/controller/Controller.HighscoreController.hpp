#ifndef CONTROLLER_HIGHSCORECONTROLLER
#define CONTROLLER_HIGHSCORECONTROLLER

//custom includes
#include "../model/Model.HighscoreEntry.hpp"

//global includes
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>


namespace controller
{

class HighscoreController
{

public:

    HighscoreController();
    ~HighscoreController();

    int addEntry(int score, std::string name, std::string field); //returns the position

    model::HighscoreEntry getEntryAt(int pos);

    std::vector<model::HighscoreEntry> getEntries();

    void readFromFile();
    void readFromFile(std::string path);

    void writeToFile();
    void writeToFile(std::string path);

    void setStandardPath(std::string path);
    std::string getStandardPath();

    void clear();

private:
    std::vector<model::HighscoreEntry> entries;
    std::string standardPath;

};

}//namespace controller

#endif // CONTROLLER_HIGHSCORECONTROLLER
