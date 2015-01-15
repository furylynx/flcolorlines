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

    /**
     * Creates a new highscore controller.
     */
    HighscoreController();
    virtual ~HighscoreController();

    /**
     * Adds a new entry to the highscores table and returns the position of the new entry in the list.
     *
     * @param score The achieved score.
     * @param name The name of the player.
     * @param field The field string describing the details of the field.
     * @return The position in the table.
     */
    virtual int addEntry(int score, std::string name, std::string field);

    /**
     * Returns the entry at the given position.
     *
     * @param pos The position
     * @return The entry.
     */
    virtual model::HighscoreEntry getEntryAt(int pos);

    /**
     * Returns all entries of the table.
     *
     * @return All entries.
     */
    virtual std::vector<model::HighscoreEntry> getEntries();

    /**
     * Reads the highscores table from the default file.
     */
    virtual void readFromFile();

    /**
     * Reads the highscores table from the given file.
     *
     * @param path The path to the highscores file.
     */
    virtual void readFromFile(std::string path);

    /**
     * Writes the highscores table to the default file.
     */
    virtual void writeToFile();

    /**
     * Writes the highscores table to the given file.
     * @param path The path to the highscores file.
     */
    virtual void writeToFile(std::string path);

    /**
     * Sets the default path for the highscores file.
     *
     * @param path The default path.
     */
    virtual void setDefaultPath(std::string path);

    /**
     * Returns the default path for the highscores file.
     *
     * @return The default path.
     */
    virtual std::string getDefaultPath();

    /**
     * Clears the highscores table.
     */
    virtual void clear();

private:
    /**
     * The highscore entries.
     */
    std::vector<model::HighscoreEntry> entries;

    /**
     * The default path.
     */
    std::string defaultPath;

};

}//namespace controller

#endif // CONTROLLER_HIGHSCORECONTROLLER
