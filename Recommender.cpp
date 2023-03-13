#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = &user_database;
    m_movie_database = &movie_database;
 }

bool Recommender::alphabeticallyEarlier(const Movie* m1, const Movie* m2){
    return m1->get_title() < m2->get_title();
}

bool Recommender::hasHigherRating(const Movie* m1, const Movie* m2){
    return m1->get_rating() > m2->get_rating();
}

bool Recommender::hasHigherCompatibility(const MovieAndRank& m1, const MovieAndRank& m2){
    return m1.compatibility_score > m2.compatibility_score;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<MovieAndRank> final_movie_ranks;
    unordered_map<Movie*, int> rating_map;
    
    User* user = m_user_database->get_user_from_email(user_email);
    vector<string> movieIDs = user->get_watch_history();
    
    vector<string>::iterator it;
    for(it = movieIDs.begin(); it != movieIDs.end(); it++){
        Movie* currMovie = m_movie_database->get_movie_from_id(*it);
        //movies with same director +20
        vector<string> directors = currMovie->get_directors();
        //traversing through everyone who directed the current movie
        for(vector<string>::iterator j = directors.begin(); j != directors.end(); j++){
            //list of movies in the database with same director
            vector<Movie*> movies = m_movie_database->get_movies_with_director(*j);
            for(vector<Movie*>::iterator k = movies.begin(); k != movies.end(); k++){
                rating_map[*k] += 20;
            }
        }
        //movies with same actor +30
        vector<string> actors = currMovie->get_actors();
        for(vector<string>::iterator j = actors.begin(); j != actors.end(); j++){
            //list of movies in the database with same actor
            vector<Movie*> movies = m_movie_database->get_movies_with_actor(*j);
            //iterate through these movies
            for(vector<Movie*>::iterator k = movies.begin(); k != movies.end(); k++){
                rating_map[*k] += 30;
            }
        }
        //movies with same genre +1
        vector<string> genres = currMovie->get_genres();
        for(vector<string>::iterator j = genres.begin(); j != genres.end(); j++){
            //list of movies in the database with same genre
            vector<Movie*> movies = m_movie_database->get_movies_with_genre(*j);
            //iterate through these movies
            for(vector<Movie*>::iterator k = movies.begin(); k != movies.end(); k++){
                if(*k != currMovie){
                    rating_map[*k]++;
                }
            }
        }
    }
    
    //create vector of movies pointers (all movies with scores >=1)
    vector<Movie*> all_movies;
    for (auto i : rating_map){
        //filter out movies already watched
        vector<string>::iterator it;
        it = find(movieIDs.begin(), movieIDs.end(), i.first->get_id());
        if(it == movieIDs.end()){
            all_movies.push_back(i.first);
        }
    }
    sort(all_movies.begin(), all_movies.end(), alphabeticallyEarlier);
    stable_sort(all_movies.begin(), all_movies.end(), hasHigherRating);
    
    vector<MovieAndRank> movie_ranks;
    for(vector<Movie*>::iterator it = all_movies.begin(); it != all_movies.end(); it++){
        string id = (*it)->get_id();
        int score = rating_map[*it];
        MovieAndRank temp(id, score);
        movie_ranks.push_back(temp);
    }
    stable_sort(movie_ranks.begin(), movie_ranks.end(), hasHigherCompatibility);
    
//        final_movie_ranks.assign(movie_ranks.begin(), movie_ranks.end());
    long count = movie_count >= movie_ranks.size() ? movie_ranks.size() : movie_count;
    for(vector<MovieAndRank>::iterator it = movie_ranks.begin(); it != movie_ranks.begin() + count; it++){
        final_movie_ranks.push_back(*it);
    }
    return final_movie_ranks;
}

//MovieAndRank* temp = new MovieAndRank(currID, 20);
//map<Movie*, int>::iterator it;
//it = rating_map.find(*k);
//if(it == rating_map.end()) rating_map[*k] = 30;
//else rating_map[*k] = it->second + 1;
