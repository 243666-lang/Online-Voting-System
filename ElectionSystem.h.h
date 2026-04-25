#ifndef ELECTION_SYSTEM_H
#define ELECTION_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
protected:
    string name;
    string id;
public:
    User();
    User(string n, string i);
    virtual void display();
    string getId();
    string getName();
    void setName(string n);
    void setId(string i);
    virtual ~User();
};

class Voter : public User {
    bool hasVoted;
public:
    Voter();
    Voter(string n, string i);
    bool getHasVoted();
    void setHasVoted(bool val);
    void vote();
    void display();
    bool operator==(const Voter& other);
};

class Admin : public User {
public:
    Admin();
    Admin(string n, string i);
    void display();
    bool operator==(const Admin& other);
};

class Candidate {
    string name;
    int voteCount;
public:
    Candidate();
    Candidate(string n);
    void incrementVote();
    void display();
    string getName();
    int getVoteCount();
    bool operator==(const Candidate& other);
};

class ElectionSystem {
    Voter voters[100];
    int voterCount;
    Admin admins[10];
    int adminCount;
    Candidate candidates[10];
    int candidateCount;
    bool isAdminLoggedIn;

public:
    ElectionSystem();
    void registerVoter();
    void registerAdmin();
    void loginAdmin();
    void adminMenu();
    void registerCandidate();
    void castVote();
    void showResults();
    void saveVoters();
    void loadVoters();
    void saveAdmins();
    void loadAdmins();
    void saveVotes();
    void loadVotes();
    ~ElectionSystem();
};

#endif

