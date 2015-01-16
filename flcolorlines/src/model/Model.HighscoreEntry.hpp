#ifndef MODEL_HIGHSCOREENTRY
#define MODEL_HIGHSCOREENTRY

//custom includes
//...

//global includes
#include <string>
#include <ctime>


namespace model
{

struct HighscoreEntry
{
    /**
     * The score.
     */
    int score;

    /**
     * The user name.
     */
    std::string name;

    /**
     * The timestamp.
     */
    std::time_t timestamp;

    /**
     * The field specification string.
     */
    std::string field;

    /**
     * Compares the current entry with the given one.
     *
     * @param c2 The entry to be compared to.
     * @return True if equal.
     */
    bool operator==(HighscoreEntry const& c2) const;

    /**
     * Compares the current entry with the given one.
     *
     * @param c2 The entry to be compared to.
     * @return True if current entry is less than the given one.
     */
    bool operator<(HighscoreEntry const& c2) const;

    /**
     * Compares the current entry with the given one.
     *
     * @param c2 The entry to be compared to.
     * @return True if the current entry is greater than the given one.
     */
    bool operator>(HighscoreEntry const& c2) const;

};

}//namespace model

#endif // MODEL_HIGHSCOREENTRY
