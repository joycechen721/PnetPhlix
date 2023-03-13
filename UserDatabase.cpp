#include "UserDatabase.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called = false;
}

//delete the dynamically allocated User
UserDatabase::~UserDatabase(){
    vector<User*>::iterator it = m_ptrs.begin();
    while(it != m_ptrs.end()){
        delete *it;
        it++;
    }
}

bool UserDatabase::load(const string& filename)
{
    if(m_called) return false;
    ifstream infile(filename);
    string newline;
    do{
        string name;
        getline(infile, name);
        
        string email;
        getline(infile, email);
        
        int movies;
        infile >> movies;
        infile.ignore(10000, '\n');
        
        vector<string> movieList;
        for(int i = 0; i < movies; i++){
            string id;
            getline(infile, id);
            movieList.push_back(id);
        }
        
        User* usr = new User(name, email, movieList);
        m_map.insert(email, usr);
        m_ptrs.push_back(usr);
        
    } while (getline(infile, newline));
    m_called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator it = m_map.find(email);
    if(it.is_valid())
        return it.get_value();
    return nullptr;
}
