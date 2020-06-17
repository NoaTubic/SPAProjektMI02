#include "Movie.h"
#include <sstream>

Movie::Movie(int rank, string title, string genre, string descripiton, string director, string actors, int year, int runtime, int rating, int votes, int revenue, int metascore)
{
    this->rank = rank;
    this->title = title;
    this->genre = genre;
    this->description = descripiton;
    this->director = director;
    this->actors = actors;
    this->year = year;
    this->runtime = runtime;
    this->rating = rating;
    this->votes = votes;
    this->revenue = revenue;
    this->metascore = metascore;
}

int Movie::get_rank() const
{
    return rank;
}

void Movie::set_rank(int rank)
{
    this->rank = rank;
}

string Movie::get_title()
{
    return title;
}

void Movie::set_title(string title)
{
    this->title = title;
}

string Movie::get_genre()
{
    return genre;
}

void Movie::set_genre(string genre)
{
    this->genre = genre;
}

string Movie::get_description()
{
    return description;
}

void Movie::set_description(string description)
{
    this->description = description;
}

string Movie::get_director()
{
    return director;
}

void Movie::set_director(string director)
{
    this->director = director;
}

string Movie::get_actors()
{
    return actors;
}

void Movie::set_actors(string actors)
{
    this->actors = actors;
}

int Movie::get_year() const
{
    return year;
}

void Movie::set_year(int year)
{
    this->year = year;
}

int Movie::get_runtime()
{
    return runtime;
}

void Movie::set_runtime(int runtime)
{
    this->runtime = runtime;
}

double Movie::get_rating()
{
    return rating;
}

void Movie::set_rating(double rating)
{
    if (rating > 0 && rating < 11)
    {
        this->rating = rating;
    }
    else
    {
        throw exception("Rating must be from 0 to 10!!");
    }
}

int Movie::get_votes()
{
    return votes;
}

void Movie::set_votes(int votes)
{
    this->votes = votes;
}

double Movie::get_revenue()
{
    return revenue;
}

void Movie::set_revenue(double revenue)
{
    this->revenue = revenue;
}

int Movie::get_metascore()
{
    return metascore;
}

void Movie::set_metascore(int metascore)
{
    
    if (metascore > 0 && metascore < 101)
    {
        this->metascore = metascore;
    }
    else
    {
        throw exception("Metascore must be from 0 to 100!!");
    }
}

string Movie::to_string() const
{

    stringstream ss;
    ss
        << "Title: " << title << '\n'
        << "Short description: " << description << '\n'
        << "Year: " << year << '\n'
        << "Revenue: ";
        if (revenue < 10000)
        {
             ss << revenue << ".000.000,00 USD" << endl;
        }
        else
        {
            ss << revenue / 1000 << "." << revenue - (revenue / 1000 * 1000) << " 000,00 USD" << endl;
        }
   
    return ss.str();
}

bool Movie::operator<(const Movie& Other) const
{
    return (Other.rank<rank);
}

bool Movie::operator==(const Movie& Other) const
{
    return (this->rank == Other.rank);
}




