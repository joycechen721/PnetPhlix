#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED
#include "treemm.h"
#include <string>
#include <vector>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> m_id_map;
    TreeMultimap<std::string, Movie*> m_director_map;
    TreeMultimap<std::string, Movie*> m_actor_map;
    TreeMultimap<std::string, Movie*> m_genre_map;
    std::vector<Movie*> m_ptrs;
    bool m_called;
    string& toLowercase(string& str) const;
};

#endif // MOVIEDATABASE_INCLUDED
