#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_called = false;
}

MovieDatabase::~MovieDatabase(){
    vector<Movie*>::iterator it = m_ptrs.begin();
    while(it != m_ptrs.end()){
        delete *it;
        it++;
    }
}

bool MovieDatabase::load(const string& filename)
{
    if(m_called) return false;
    ifstream infile(filename);
    string newline;
    do{
        string id;
        getline(infile, id);

        string title;
        getline(infile, title);

        string releaseYear;
        getline(infile, releaseYear);
        
        string directors;
        getline(infile, directors);
        string director = "";
        vector<string> directorList;
        for(int i = 0; i != directors.size(); i++){
            if(directors.at(i) != ','){
                director += tolower(directors.at(i));
            }
            else{
                directorList.push_back(director);
                director = "";
            }
        }
        directorList.push_back(director);
        
        string actors;
        getline(infile, actors);
        string actor = "";
        vector<string> actorList;
        for(int i = 0; i != actors.size(); i++){
            if(actors.at(i) != ','){
                actor += tolower(actors.at(i));
            }
            else{
                actorList.push_back(actor);
                actor = "";
            }
        }
        actorList.push_back(actor);
        
        string genres;
        getline(infile, genres);
        string genre = "";
        vector<string> genreList;
        for(int i = 0; i != genres.size(); i++){
            if(genres.at(i) != ','){
                genre += tolower(genres.at(i));
            }
            else{
                genreList.push_back(genre);
                genre = "";
            }
        }
        genreList.push_back(genre);
        
        float rating;
        infile >> rating;
        infile.ignore(10000, '\n');


        Movie* currMovie = new Movie(id, title, releaseYear, directorList, actorList, genreList, rating);
        
        m_id_map.insert(id, currMovie);
        
        for(vector<string>::iterator it = directorList.begin(); it != directorList.end(); it++){
            m_director_map.insert(*it, currMovie);
        }
        
        for(vector<string>::iterator it = actorList.begin(); it != actorList.end(); it++){
            m_actor_map.insert(*it, currMovie);
        }
        
        for(vector<string>::iterator it = genreList.begin(); it != genreList.end(); it++){
            m_genre_map.insert(*it, currMovie);
        }
        
        m_ptrs.push_back(currMovie);
    } while (getline(infile, newline));
    m_called = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = m_id_map.find(id);
    if(it.is_valid())
        return it.get_value();
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string temp = director;
    TreeMultimap<std::string, Movie*>::Iterator it = m_director_map.find(toLowercase(temp));
    vector<Movie*> movies;
    while(it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string temp = actor;
    TreeMultimap<std::string, Movie*>::Iterator it = m_actor_map.find(toLowercase(temp));
    vector<Movie*> movies;
    while(it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string temp = genre;
    TreeMultimap<std::string, Movie*>::Iterator it = m_genre_map.find(toLowercase(temp));
    vector<Movie*> movies;
    while(it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

string& MovieDatabase::toLowercase(string &str) const{
    for(int i = 0; i < str.size(); i++){
        str.at(i) = tolower(str.at(i));
    }
    return str;
}
