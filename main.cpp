#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Recommender.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

//const string USER_DATAFILE  = "/Users/joycechen/users.txt";
const string MOVIE_DATAFILE = "/Users/joycechen/movies.txt";

const string USER_DATAFILE  = "/Users/joycechen/Desktop/users.txt";
//const string MOVIE_DATAFILE = "/Users/joycechen/Desktop/movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
    // get up to ten movie recommendations for the user
        vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
        if (recommendations.empty())
           cout << "We found no movies to recommend :(.\n";
        else {
            for (int i = 0; i < recommendations.size(); i++) {
                const MovieAndRank& mr = recommendations[i];
                Movie* m = md.get_movie_from_id(mr.movie_id);
                cout << i + 1 << ". " << m->get_title() << " ("
                    << m->get_release_year() << ")\n Rating: "
                    << m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n";
                }
            }
    }

int main()
{
//        map<string,char> namemap;
//        namemap["yogi"]='c';
//    namemap["yogi"] = 'd';
//        namemap.insert(pair<string,char>("yogendra",'a'));
//        namemap.insert(pair<string,char>("yogendra",'b'));

//        cout<<namemap["yogi"]<<endl;
    
    UserDatabase udb;
    udb.load(USER_DATAFILE);
    MovieDatabase mdb;
    mdb.load(MOVIE_DATAFILE);
    Recommender rc(udb, mdb);
    findMatches(rc, mdb, "climberkip@gmail.com", 10);
    
//    for (;;)
//    {
//        cout << "Enter movie ID (or quit): ";
//        string id;
//        getline(cin, id);
//        if (id == "quit")
//            return 0;
//        Movie* u = mdb.get_movie_from_id(id);
//        if (u == nullptr)
//            cout << "No movie in the database has that id." << endl;
//        else
//            cout << "Found " << u->get_title() << endl;
//    }
    
//    MovieDatabase udb;
//    if (!udb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
//    {
//        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//        return 1;
//    }
//    for (;;)
//    {
//        cout << "Enter movie ID (or quit): ";
//        string id;
//        getline(cin, id);
//        if (id == "quit")
//            return 0;
//        vector<Movie*> u = mdb.get_movies_with_actor("Newton");
//        if (u == "")
//            cout << "No movie in the database has that id." << endl;
//        else
//        for(vector<Movie*>::iterator i = u.begin(); i != u.end(); i++)
//            cout << "Found " << (*i)->get_title() << endl;
//    }
    
//    UserDatabase udb;
//    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
//    {
//        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//        return 1;
//    }
//    for (;;)
//    {
//        cout << "Enter user email address (or quit): ";
//        string email;
//        getline(cin, email);
//        if (email == "quit")
//            return 0;
//        User* u = udb.get_user_from_email(email);
//        if (u == nullptr)
//            cout << "No user in the database has that email address." << endl;
//        else
//            cout << "Found " << u->get_full_name() << endl;
//    }
}
