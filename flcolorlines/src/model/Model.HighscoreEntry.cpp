#include "Model.HighscoreEntry.hpp"

using namespace model;


bool HighscoreEntry::operator==(HighscoreEntry const& c2) const
{
    return (this->score == c2.score);
}

bool HighscoreEntry::operator<(HighscoreEntry const& c2) const
{
    return (this->score < c2.score);
}

bool HighscoreEntry::operator>(HighscoreEntry const& c2) const
{
    return (this->score > c2.score);
}
