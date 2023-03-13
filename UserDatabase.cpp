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

//int main() {
//  TreeMultimap<std::string, int> tmm;
//  tmm.insert("carey", 5);
//  tmm.insert("carey", 6);
//  tmm.insert("carey", 7);
//  tmm.insert("david", 25);
//  tmm.insert("david", 425);
//    tmm.insert("cAReY", 90);
//    tmm.insert("Laura", 1);
//    TreeMultimap<std::string,int>::Iterator it = tmm.find("carey"); // prints 5, 6, and 7 in some order
//    while (it.is_valid()) {
//        std::cout << it.get_value() << std::endl;
//        it.advance();
//    }
//    TreeMultimap<std::string,int>::Iterator itt = tmm.find("Laura");
//    if (itt.is_valid())
//        std::cout << "Laura is in the multimap!\n";
//
//}
