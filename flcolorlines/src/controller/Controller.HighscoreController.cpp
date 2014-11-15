#include <assert.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Controller.HighscoreController.h"

using namespace controller;

HighscoreController::HighscoreController(){
    standardPath = "NULL";
}

HighscoreController::~HighscoreController(){

}

void HighscoreController::setStandardPath(std::string path){
    this->standardPath = path;
}

std::string HighscoreController::getStandardPath(){
    return standardPath;
}

void HighscoreController::clear(){
    entries.clear();
}

std::vector<model::HighscoreEntry> HighscoreController::getEntries(){
    return entries;
}

model::HighscoreEntry HighscoreController::getEntryAt(int pos){

    assert(pos > 0 && pos < entries.size());

    return entries[pos];
}



int HighscoreController::addEntry(int score, std::string name, std::string field){

    model::HighscoreEntry entry;
    entry.score = score;
    entry.name = name;
    entry.timestamp = std::time(0);
    entry.field = field;

    entries.push_back(entry);

    sort(entries.begin(),entries.end(), std::greater<model::HighscoreEntry>());

    int i;
    for(i = 0; i< entries.size();i++)
        if (entries[i].timestamp == entry.timestamp && entries[i].score == entry.score)
            break;

    return i;
}

void HighscoreController::writeToFile(){

    if (standardPath != "NULL")
        writeToFile(standardPath);
}

void HighscoreController::readFromFile(){
    if (standardPath != "NULL")
        readFromFile(standardPath);
}

void HighscoreController::readFromFile(std::string path){

    //clear list first
    entries.clear();

    //read in from file
    std::ifstream readfile(path.c_str());

    while (readfile && !readfile.eof() ){

        model::HighscoreEntry entry;
        readfile >> entry.name;
        if (readfile.eof())
            break;

        readfile >> entry.score;

        if (readfile.eof())
            break;

        readfile >> entry.field;

        if (readfile.eof())
            break;

        readfile >> entry.timestamp;

        entries.push_back(entry);

    }
    readfile.close();

    //sort list just in case
    sort(entries.begin(),entries.end(), std::greater<model::HighscoreEntry>());

}

void HighscoreController::writeToFile(std::string path){

    //write to file
    std::ofstream writefile(path.c_str(), std::ios::out);

    for(int i=0; i< entries.size(); i++)
    {
        writefile << entries[i].name << " " << entries[i].score << " " << entries[i].field << " " << entries[i].timestamp << "\n";
    }

    writefile.close();
}
