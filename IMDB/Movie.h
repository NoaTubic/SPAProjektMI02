#pragma once
#include <string>;
using namespace std;
class Movie
{
private:
	int rank;
	string title;
	string genre;
	string description;
	string director;
	string actors;
	int year;
	int runtime;
	double rating;
	int votes;
	double revenue;
	int metascore;

public:
	Movie(int rank, string title, string genre, string descripiton, string director, string actors, int year, int runtime,
	int rating, int votes, int revenue, int metascore);
	int get_rank() const;
	void set_rank(int rank);
	string get_title();
	void set_title(string title);
	string get_genre();
	void set_genre(string genre);
	string get_description();
	void set_description(string description);
	string get_director();
	void set_director(string director);
	string get_actors();
	void set_actors(string actors);
	int get_year() const;
	void set_year(int year);
	int get_runtime();
	void set_runtime(int runtime);
	double get_rating();
	void set_rating(double rating);
	int get_votes();
	void set_votes(int votes);
	double get_revenue();
	void set_revenue(double revenue);
	int get_metascore();
	void set_metascore(int metascore);
	string to_string() const;
	bool operator<(const Movie &Other) const;
	bool operator==(const Movie& Other) const;
	
};

struct movie_year_comparer_desc
{
	bool operator() ( Movie& m1,  Movie& m2) const
	{
		return m1.get_year() < m2.get_year();
	}
};
