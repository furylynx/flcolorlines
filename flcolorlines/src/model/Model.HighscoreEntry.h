#ifndef MODEL_HIGHSCOREENTRY
#define MODEL_HIGHSCOREENTRY

#include <string>
#include <ctime>

namespace model{
struct HighscoreEntry{

    int score;
    std::string name;
    std::time_t timestamp;
    std::string field;

    bool operator==(HighscoreEntry const& c2) const;
    bool operator<(HighscoreEntry const& c2) const;
    bool operator>(HighscoreEntry const& c2) const;

};

}

#endif // MODEL_HIGHSCOREENTRY
