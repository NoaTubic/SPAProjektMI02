#include <iostream>
#include "Movie.h"
#include <vector>
#include <fstream>;
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <chrono>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std::chrono;
using namespace std;

//31
void printMainMenu()
{
	cout << endl;
	cout << "--------------------------------------" << endl;
	cout << "Choose one option (type 1, 2, 3, ... ): " << '\n';
	cout << "--------------------------------------" << endl;
	cout << "1.) Search by metascore " << endl;
	cout << "2.) Sort by year " << endl;
	cout << "3.) Copy to a new vector" << endl;
	cout << "4.) Selection vs Insertion" << endl;
	cout << "5.) Guess the duration" << endl;
	cout << "6.) Lets Bogo!" << endl;
	cout << "7.) The Merge Dance" << endl;
	cout << "8.) Search by genre" << endl;
	cout << "9.) Visualize" << endl;
	cout << "10.) String from string" << endl;
}


template<typename T>
T convert(string& s)
{
	stringstream c(s);
	T t;
	c >> t;
	return t;
}


//database creation
void dataImport(ifstream &in, vector<Movie> &movies)
{

	string line;
	int rank, year, runtime, votes, metascore;
	double rating, revenue;
	string title, genre, description, director, actors;
	string temp, temp2;
	getline(in, line);
	while (getline(in, line))
	{
	stringstream ss(line);
	getline(ss, temp, ',');
	rank = convert<int>(temp);
	getline(ss, title, ',');
	getline(ss, genre, ',');
	if (genre[0] == '"') 
	{
		getline(ss, temp2, '"');
		genre.erase(0, 1);
		genre = genre + "," + temp2;
		getline(ss, temp2, ','); //da se isprazni zarez s kraja
	}
	getline(ss, description, ',');
	if (description[0] == '"')
	{
		getline(ss, temp2, '"');
		description.erase(0, 1);
		description = description + "," + temp2;
		getline(ss, temp2, ',');
	}
	getline(ss, director, ',');
	getline(ss, actors, ',');
	if (actors[0] == '"')
	{
		getline(ss, temp2, '"');
		actors.erase(0, 1);
		actors = actors + "," + temp2;
		getline(ss, temp2, ',');
	}
	getline(ss, temp, ',');
	year = convert<int>(temp);
	getline(ss, temp, ',');
	runtime = convert<int>(temp);
	getline(ss, temp, ',');
	rating = convert<double>(temp);
	getline(ss, temp, ',');
	votes = convert<int>(temp);
	getline(ss, temp, ',');
	revenue = convert<double>(temp);
	getline(ss, temp, ',');
	metascore = convert<int>(temp);

	movies.emplace_back(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);

	}

}

//33
void searchMetascoreInRange(set<Movie> &movieSet, int min, int max)
{
	for (Movie m : movieSet) {
		if (m.get_metascore() >= min && m.get_metascore() <= max)
		{
			cout << m.to_string() << " ";
		}

	}
}

//34 	//VECTOR
void searchMetascoreInRange(vector<Movie> &movies, int min, int max)
{

	for (auto it = movies.begin(); it != movies.end(); ) //search by metascore in range
	{
		if (it->get_metascore() >= min && it->get_metascore() <= max)
		{
			cout << it->to_string() << endl;
			++it;
		}

		else
		{
			++it;
		}
	}
}
//34 	//LIST
void searchMetascoreInRange(list<Movie> &movieList, int min, int max)
{
	for (auto it = movieList.begin(); it != movieList.end(); ) //search by metascore in range
	{
		if (it->get_metascore() >= min && it->get_metascore() <= max)
		{
			cout << it->to_string() << endl;
			++it;
		}

		else
		{
			++it;
		}
	}
}

//34 MEASURE SEARCH TIMES AND SORT ASC
void measureTimeAndSort(set<Movie>& movieSet, vector<Movie>& movies, list<Movie>& movieList, int min, int max)
{
	vector< pair<string, double> > measuredTimes;
	auto begin = high_resolution_clock::now();
	searchMetascoreInRange(movieSet, min, max);
	auto end = high_resolution_clock::now();
	double sTime = duration_cast<milliseconds>(end - begin).count();
	measuredTimes.emplace_back(make_pair("Set", sTime));

	auto begin2 = high_resolution_clock::now();
	searchMetascoreInRange(movies, min, max);
	auto end2 = high_resolution_clock::now();
	double vTime = duration_cast<milliseconds>(end2 - begin2).count();
	measuredTimes.emplace_back(make_pair("Vector", vTime));

	auto begin3 = high_resolution_clock::now();
	searchMetascoreInRange(movieList, min, max);
	auto end3 = high_resolution_clock::now();
	double lTime = duration_cast<milliseconds>(end3 - begin3).count();
	measuredTimes.emplace_back(make_pair("List", lTime));

	sort(measuredTimes.begin(), measuredTimes.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (int i = 0; i < measuredTimes.size(); i++)
	{
		cout << i + 1 << ".) " << measuredTimes.at(i).first << "   " << measuredTimes.at(i).second << " ms" << endl;

	}
}

//36 //SEARCH BY 1. LETTER
void searchByFirstLetter(vector<Movie>& movies2, set<Movie>& movieSet2)
{
	bool again;
	do
	{
		char fl;
		cout << "Enter the 1. letter of the movie title: ";
		cin >> fl;

		for (Movie m : movieSet2) {
			if (m.get_title()[0] == toupper(fl))
			{
				movies2.push_back(m);
			}

		}


		cout << "Continue searching by letter? (1 - yes, 0 - no): ";
		cin >> again;
	} while (again);

	for (unsigned int i = 0; i < movies2.size(); i++)
	{
		cout << movies2.at(i).to_string() << endl;
	}
}

//42 SELECTION SORT
void selectionSort(vector<Movie>& v1) 
{
	auto begin = high_resolution_clock::now();
	for (int i = 0; i < v1.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < v1.size(); j++)
		{
			if (v1.at(j).get_title() < v1.at(min_index).get_title())
			{
				min_index = j;
			}
		}
		swap(v1.at(min_index), v1.at(i));
	}
	auto end = high_resolution_clock::now();
	cout<< "Duration of Selection Sort: "
		<< duration_cast<chrono::milliseconds>(end - begin).count()
		<< " ms" << '\n' << endl;
}
//42 INSERTION SORT
void insertionSort(vector<Movie>& v2)
{	
	auto begin = high_resolution_clock::now();
	for (int i = 1; i < v2.size(); i++) { 
		for (int j = i; j > v2.size() ; j--)
		{
			if (v2.at(j - 1).get_title() > v2.at(j).get_title())
			{
				swap(v2.at(j), v2.at(j - 1));
			}
			
		}
	}
	auto end = high_resolution_clock::now();
	cout << "Duration of Insertion Sort: "
		<< duration_cast<chrono::milliseconds>(end - begin).count()
		<< " ms" << '\n' << endl;
}
//43
int measureSwapsSelectionSort(vector<Movie> &v1)
{
	int counter = 0;
	for (int i = 0; i < v1.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < v1.size(); j++)
		{
			if (v1.at(j).get_title() < v1.at(min_index).get_title())
			{
				min_index = j;
			}
		}
		swap(v1.at(min_index), v1.at(i));
		counter++;
	}
	return counter;
}

int measureSwapsInsertionSort(vector<Movie>& v2)
{
	int counter = 0;
	for (int i = 1; i < v2.size(); i++) 
	{
		for (int j = i; j > v2.size(); j--)
		{
			if (v2.at(j - 1).get_title() > v2.at(j).get_title())
			{
				swap(v2.at(j), v2.at(j - 1));
				counter++;
			}

		}
	}
	return counter;
}
//45 BOGO SORT
bool isSortedAscending(vector<Movie> &v)
{
	for (unsigned i = 0; i < v.size() -1; i++)
	{
		if (v.at(i).get_title() > v.at(i+1).get_title())
		{
			return false;
		}
	}
	return true;
}
//46 MERGE SORT
void merge(vector<Movie> poljea, int na, vector<Movie> poljeb, int nb) {
	vector<Movie> poljec;
	int ia = 0, ib = 0;
	for (int ic = 0; ic < na + nb; ic++) {
		if (ia == na) {
			poljec[ic] = poljeb[ib++];
			continue;
		}
		if (ib == nb) {
			poljec[ic] = poljea[ia++];
				continue;
		}
		if (poljea[ia].get_rank() < poljeb[ib].get_rank())
			poljec[ic] = poljea[ia++];

		else
			poljec[ic] = poljeb[ib++];
	}

	for (int i = 0; i < na + nb; i++)
		poljea[i] = poljec[i];
}

void printCounter(int counter, ofstream &out)
{
	for (unsigned i = 0; i < counter; i++)
	{
		out << "#";
	}
	out << endl;
}

void merge_sort(vector<Movie> data, int from, int to, ofstream &out) {
	int counter = 0;
	if (from == to)
		return;

	int mid = (from + to) / 2;
	//povecaj brojac 
	counter++;
	printCounter(counter, out);
	merge_sort(data, from, mid, out);
	//smanji brojac
	counter--;
	printCounter(counter, out);
	//povecaj brojac
	counter++;
	printCounter(counter, out);
	merge_sort(data, mid + 1, to, out);
	counter--;
	printCounter(counter, out);
	//smanji brojac

	vector<Movie>::const_iterator first = data.begin() + from;
	vector<Movie>::const_iterator last = data.begin() + to;
	vector<Movie>::const_iterator middle = data.begin() + ((from + to) / 2) + 1;
	vector<Movie> v(first, middle);
	vector<Movie> v2(middle, last);


	merge(v, mid - from + 1, v2, to - mid);
}

class MyHashFunction {
public:
	// id is returned as hash function 
	size_t operator()(const Movie& m) const
	{
		return m.get_rank();
	}
};


//53 //UNORDERED SET
void searchGenre(unordered_set<Movie, MyHashFunction>& movieSet, string genreSearch)
{
	for (Movie m : movieSet) {
		if (m.get_genre().find(genreSearch) != string::npos)
		{
			cout << m.to_string() << endl;
		}

	}
}

//53 //VECTOR
void searchGenre(vector<Movie>& movies, string genreSearch)
{

	for (auto it = movies.begin(); it != movies.end(); ) //search by metascore in range
	{
		if (it->get_genre().find(genreSearch) != string::npos)
		{
			cout << it->to_string() << endl;
			++it;
		}

		else
		{
			++it;
		}
	}
}


//53 //LIST
void searchGenre(list<Movie>& movieList, string genreSearch) {

	for (auto it = movieList.begin(); it != movieList.end(); ) //search by genre
	{
		if (it->get_genre().find(genreSearch) != string::npos)
		{
			cout << it->to_string() << endl;
			++it;
		}

		else
		{
			++it;
		}
	}
} 
//53 MEASURE SEARCH TIMES AND SORT ASC
void measureTimeAndSort(unordered_set<Movie, MyHashFunction>& movieSet, vector<Movie>& movies, list<Movie>& movieList, string genreSearch)
{
	vector< pair<string, double> > measuredTimes;
	auto begin = high_resolution_clock::now();
	searchGenre(movieSet, genreSearch);
	auto end = high_resolution_clock::now();
	double sTime = duration_cast<milliseconds>(end - begin).count();
	measuredTimes.emplace_back(make_pair("Set", sTime));

	auto begin2 = high_resolution_clock::now();
	searchGenre(movies, genreSearch);
	auto end2 = high_resolution_clock::now();
	double vTime = duration_cast<milliseconds>(end2 - begin2).count();
	measuredTimes.emplace_back(make_pair("Vector", vTime));

	auto begin3 = high_resolution_clock::now();
	searchGenre(movieList, genreSearch);
	auto end3 = high_resolution_clock::now();
	double lTime = duration_cast<milliseconds>(end3 - begin3).count();
	measuredTimes.emplace_back(make_pair("List", lTime));

	sort(measuredTimes.begin(), measuredTimes.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (int i = 0; i < measuredTimes.size(); i++)
	{
		cout << i + 1 << ".) " << measuredTimes.at(i).first << "   " << measuredTimes.at(i).second << " ms" << endl;

	}
}
//55
bool checkString(string desc, char c)
{
	for (unsigned i = 0; i < desc.size(); i++)
	{
		if (desc.at(i) == c || tolower(desc.at(i)) == c)
		{
			return true;
		}
	}
	return false;
}



int main() {

	//31
	vector<Movie> movies;
	ifstream in("SPA_PROJ_011_IMDB_data.csv");
	if (!in)
	{
		cout << "Can't access file!" << endl;
		return 1;
	}
	dataImport(in, movies);
	in.close();

	//cout << movies.at(1).to_string() << endl;

	do
	{
		printMainMenu();
		int optionSelection;
		cin >> optionSelection;
		if (optionSelection == 1)
		{
			set<Movie> movieSet(movies.begin(), movies.end());

			//for (Movie m : movieSet) {
			//	cout << m.to_string() << " ";
			//}

			int min, max;
			cout << "--------------------------------------" << endl;
			cout << "Search by metascore" << endl;
			cout << "--------------------------------------" << endl;
			cout << "Enter min metascore for searching: ";
			cin >> min;
			cout << "Enter max metascore for searching: ";
			cin >> max;
			//33
			searchMetascoreInRange(movieSet, min, max);

			//34 
			list<Movie> movieList;
			for (unsigned i = 0; i < movies.size(); i++) // copy to list 
			{
				movieList.push_back(movies.at(i));
			}
			measureTimeAndSort(movieSet, movies, movieList, min, max); // MEASURE SEARCH TIMES AND SORT ASC
		}
		else if (optionSelection == 2)
		{
			//35
			cout << "--------------------------------------" << endl;
			cout << "Sort by year" << endl;
			cout << "--------------------------------------" << endl;
			priority_queue<Movie, vector<Movie>, movie_year_comparer_desc> pq(movies.begin(), movies.end());
			while (!pq.empty()) //SORT BY YEAR DESC
			{
				cout << pq.top().to_string() << endl;
				pq.pop();
			}



		}
		else if (optionSelection == 3)
		{
			//36 
			cout << "--------------------------------------" << endl;
			cout << "Copy to a new vector and seatch by first letter" << endl;
			cout << "--------------------------------------" << endl;
			vector<Movie> movies2;
			set<Movie> movieSet2(movies.begin(), movies.end());
			searchByFirstLetter(movies2, movieSet2); //SEARCH BY 1. LETTER

		}
		else if (optionSelection == 4)
		{
			//42
			cout << "--------------------------------------" << endl;
			cout << "Selection vs Insertion" << endl;
			cout << "--------------------------------------" << endl;
			vector <Movie> v1(movies.begin(), movies.end());
			vector <Movie> v2(movies.begin(), movies.end());

			selectionSort(v1);
			insertionSort(v2);

			//43 *NOTE* - zakomentirati funkcije iznad za tocan rezultat
			cout << "Number of swaps in Selection Sort: " << measureSwapsSelectionSort(v1) << endl;
			cout << "Number of swaps in Insertion Sort: " << measureSwapsInsertionSort(v2) << endl;


		}
		else if (optionSelection == 5)
		{
			//44
			cout << "--------------------------------------" << endl;
			cout << "Guess the duration" << endl;
			cout << "--------------------------------------" << endl;
			srand(time(NULL));
			int n = rand() % 100000000 + 1;
			int ms;
			cout << "How many milliseconds does it take to randomize, sort, and binary search that field in search of number 7?: ";
			cin >> ms;
			int *array = new int[n];
			for (size_t i = 0; i < n; i++)
			{
				array[i] = i + 1;

			}
			auto begin = high_resolution_clock::now();
			random_shuffle(array, array + n);
			sort(array, array + n);
			binary_search(array, array + n, 7);
			auto end = high_resolution_clock::now();
			cout << "Difference between your guess time and measuered time: "
				<< abs(duration_cast<chrono::milliseconds>(end - begin).count() - ms)
				<< " ms" << '\n' << endl;
			delete[] array;
		}
		else if (optionSelection == 6)
		{
			//45 BOGO SORT
			cout << "--------------------------------------" << endl;
			cout << "Bogo Sort" << endl;
			cout << "--------------------------------------" << endl;
			srand((unsigned)time(NULL));
			vector<Movie> randomMovies;
			for (unsigned int i = 0; i < 5; i++)
			{
				int n = rand() % movies.size() + 1;
				randomMovies.emplace_back(movies.at(n));

			}
			int counter = 0;
			while (!isSortedAscending(randomMovies))
			{
				counter++;
				cout << "--------------------------------------" << endl;
				cout << counter << ". permuatation: " << endl;
				cout << "--------------------------------------" << endl;
				for (unsigned int i = 0; i < randomMovies.size(); i++)
				{
					cout << i + 1 << ".) " << randomMovies.at(i).to_string() << endl;
				}

				next_permutation(randomMovies.begin(), randomMovies.end());
			}

		}
		else if (optionSelection == 7)
		{
		//46 MERGE DANCE
		cout << "--------------------------------------" << endl;
		cout << "The Merge Dance" << endl;
		cout << "--------------------------------------" << endl;
		int n;
		vector<Movie> randomMovies;
		cout << "Enter number of elements: ";
		cin >> n;
		srand((unsigned)time(NULL));
		for (unsigned int i = 0; i < n; i++)
		{
			int r = rand() % movies.size() + 1;
			randomMovies.emplace_back(movies.at(r));

		}
		ofstream out("CounterValues.txt");
		merge_sort(randomMovies, 0, n - 1, out);
		out.close();

		}
		else if (optionSelection == 8)
		{
			//52
			cout << "--------------------------------------" << endl;
			cout << "Search by genre: (*NOTE* Enter genre name with first letter capital (Horror, Action, ... )" << endl;
			cout << "--------------------------------------" << endl;
			unordered_set<Movie, MyHashFunction> movieSet(movies.begin(), movies.end());
			string genreSearch;
			cin.ignore();
			cout << "Search by genre " << endl;
			cout << "Enter genre:";
			getline(cin, genreSearch);

			searchGenre(movieSet, genreSearch);

			//53
			list<Movie> movieList;
			for (unsigned i = 0; i < movies.size(); i++) // copy to list 
			{
				movieList.push_back(movies.at(i));
			}

			measureTimeAndSort(movieSet, movies, movieList, genreSearch); // MEASURE SEARCH TIMES AND SORT ASC
		}
		else if (optionSelection == 9)
		{
			cout << "--------------------------------------" << endl;
			cout << "Visualize" << endl;
			cout << "--------------------------------------" << endl;
			unordered_multimap<int, Movie> mm;
			for (unsigned i = 0; i < movies.size(); i++)
			{
				mm.emplace(movies.at(i).get_year(), movies.at(i));
			}
			for (unsigned i = 0; i < mm.bucket_count(); i++)
			{
				cout << "Bucket: " << i << ": ";
				if (mm.bucket_size(i) == 0)
				{
					cout << "[EMPTY]" << endl;
				}

				for (auto it = mm.begin(i); it != mm.end(i); it++)
						cout << it->second.get_title() << " --  ";
						cout << endl;	
			}

		}
		else if (optionSelection == 10)
			{
			cout << "--------------------------------------" << endl;
			cout << "String from string" << endl;
			cout << "--------------------------------------" << endl;
			cin.ignore();
			unordered_multimap<string, string> mm;
			for (unsigned i = 0; i < movies.size(); i++)
			{
				mm.emplace(movies.at(i).get_title(), movies.at(i).get_description());
			}
			string m;
			string s;
			bool again = 0;
			do
			{
				cout << "Choose one movie: *NOTE* First letter of the title must be capital!! " ;
				getline(cin, m);
				cout << "Enter a string: ";
				getline(cin, s);
				string desc = mm.find(m) ->second;
				int counter = 0;

				for (unsigned i = 0; i < s.size(); i++)
				{
					
					if (checkString(desc, s.at(i)))
					{
						counter++;
						
					}

				}
				if (counter == s.size())
				{
					cout << "String \"" << s << "\" can be constructed from movie description " << desc << endl;
				}
				else
				{
					cout << "String \"" << s << "\" can't be constructed from movie description " << desc << endl;
				}
				

				cout << endl;
				cout << "Again? (1 - yes, 0 - no)";
				cin >> again;
				cin.ignore();
			} while (again);



		}
	
	}
	while (true);


		return 0;
}