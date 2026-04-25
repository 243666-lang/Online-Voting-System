#include "ElectionSystem.h"
// User
User::User() {}
User::User(string n, string i) : name(n), id(i) {}
void User::display() { cout << "Name: " << name << ", ID: " << id << endl; }
string User::getId() { return id; }
string User::getName() { return name; }
void User::setName(string n) { name = n; }
void User::setId(string i) { id = i; }
User::~User() {}

// Voter
Voter::Voter() : hasVoted(false) {}
Voter::Voter(string n, string i) : User(n, i), hasVoted(false) {}
bool Voter::getHasVoted() { return hasVoted; }
void Voter::setHasVoted(bool val) { hasVoted = val; }
void Voter::vote() { hasVoted = true; }
void Voter::display() {
    cout << "[Voter] Name: " << name << ", ID: " << id
         << ", Has Voted: " << (hasVoted ? "Yes" : "No") << endl;
}
bool Voter::operator==(const Voter& other) { return id == other.id; }

// Admin
Admin::Admin() {}
Admin::Admin(string n, string i) : User(n, i) {}
void Admin::display() { cout << "[Admin] Name: " << name << ", ID: " << id << endl; }
bool Admin::operator==(const Admin& other) { return id == other.id; }

// Candidate
Candidate::Candidate() : voteCount(0) {}
Candidate::Candidate(string n) : name(n), voteCount(0) {}
void Candidate::incrementVote() { voteCount++; }
void Candidate::display() { cout << "Candidate: " << name << " - Votes: " << voteCount << endl; }
string Candidate::getName() { return name; }
int Candidate::getVoteCount() { return voteCount; }
bool Candidate::operator==(const Candidate& other) { return name == other.name; }

// ElectionSystem
ElectionSystem::ElectionSystem() : voterCount(0), adminCount(0), candidateCount(3), isAdminLoggedIn(false) {
    candidates[0] = Candidate("Imran Khan");
    candidates[1] = Candidate("Nawaz Sharif");
    candidates[2] = Candidate("DG ISPR");
    loadVoters();
    loadAdmins();
    loadVotes();
}

void ElectionSystem::registerVoter() {
    string name, id;
    cout << "Enter Voter Name: "; getline(cin >> ws, name);
    cout << "Enter Voter ID: "; getline(cin >> ws, id);
    Voter v(name, id);
    for (int i = 0; i < voterCount; ++i) if (voters[i] == v) { cout << "Voter already registered.\n"; return; }
    voters[voterCount++] = v;
    saveVoters(); cout << "Voter registered successfully.\n";
}

void ElectionSystem::registerAdmin() {
    string name, id;
    cout << "Enter Admin Name: "; getline(cin >> ws, name);
    cout << "Enter Admin ID: "; getline(cin >> ws, id);
    Admin a(name, id);
    for (int i = 0; i < adminCount; ++i) if (admins[i] == a) { cout << "Admin already registered.\n"; return; }
    admins[adminCount++] = a;
    saveAdmins(); cout << "Admin registered successfully.\n";
}

void ElectionSystem::loginAdmin() {
    string id;
    cout << "Enter Admin ID: "; getline(cin >> ws, id);
    for (int i = 0; i < adminCount; ++i)
        if (admins[i].getId() == id) {
            isAdminLoggedIn = true; cout << "Admin logged in successfully.\n"; adminMenu(); return;
        }
    cout << "Invalid Admin ID.\n";
}

void ElectionSystem::adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n1. Show Results\n2. Register New Candidate\n3. Logout\nEnter choice: ";
        cin >> choice; cin.ignore();
        switch (choice) {
            case 1: showResults(); break;
            case 2: registerCandidate(); break;
            case 3: isAdminLoggedIn = false; cout << "Admin logged out.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (isAdminLoggedIn);
}

void ElectionSystem::registerCandidate() {
    if (candidateCount >= 10) { cout << "Candidate limit reached.\n"; return; }
    string name; cout << "Enter Candidate Name: "; getline(cin >> ws, name);
    Candidate c(name);
    for (int i = 0; i < candidateCount; ++i) if (candidates[i] == c) { cout << "Candidate already exists.\n"; return; }
    candidates[candidateCount++] = c; cout << "Candidate registered successfully.\n";
}

void ElectionSystem::castVote() {
    string id; cout << "Enter Voter ID: "; getline(cin >> ws, id);
    int index = -1; for (int i = 0; i < voterCount; ++i) if (voters[i].getId() == id) { index = i; break; }
    if (index == -1) { cout << "Voter not found.\n"; return; }
    if (voters[index].getHasVoted()) { cout << "You have already voted.\n"; return; }
    cout << "Choose a candidate:\n";
    for (int i = 0; i < candidateCount; ++i) cout << i + 1 << ". " << candidates[i].getName() << endl;
    int choice; cout << "Enter choice (1-" << candidateCount << "): "; cin >> choice;
    if (choice < 1 || choice > candidateCount) { cout << "Invalid choice.\n"; return; }
    candidates[choice - 1].incrementVote(); voters[index].setHasVoted(true); saveVotes(); saveVoters(); cout << "Vote cast successfully.\n";
}

void ElectionSystem::showResults() {
    cout << "----- Voting Results -----\n";
    for (int i = 0; i < candidateCount; ++i) candidates[i].display();
}

void ElectionSystem::saveVoters() {
    ofstream fout("voters.txt");
    for (int i = 0; i < voterCount; ++i)
        fout << voters[i].getName() << "," << voters[i].getId() << "," << voters[i].getHasVoted() << endl;
    fout.close();
}

void ElectionSystem::loadVoters() {
    ifstream fin("voters.txt"); string line;
    while (getline(fin, line)) {
        size_t p1 = line.find(','); size_t p2 = line.find(',', p1 + 1);
        string name = line.substr(0, p1); string id = line.substr(p1 + 1, p2 - p1 - 1); bool hasVoted = stoi(line.substr(p2 + 1));
        Voter v(name, id); v.setHasVoted(hasVoted); voters[voterCount++] = v;
    } fin.close();
}

void ElectionSystem::saveAdmins() {
    ofstream fout("admins.txt");
    for (int i = 0; i < adminCount; ++i) fout << admins[i].getName() << "," << admins[i].getId() << endl;
    fout.close();
}

void ElectionSystem::loadAdmins() {
    ifstream fin("admins.txt"); string line;
    while (getline(fin, line)) {
        size_t comma = line.find(','); string name = line.substr(0, comma); string id = line.substr(comma + 1);
        admins[adminCount++] = Admin(name, id);
    } fin.close();
}

void ElectionSystem::saveVotes() {
    ofstream fout("votes.txt");
    for (int i = 0; i < candidateCount; ++i)
        fout << candidates[i].getName() << "," << candidates[i].getVoteCount() << endl;
    fout.close();
}

void ElectionSystem::loadVotes() {
    ifstream fin("votes.txt"); string line;
    while (getline(fin, line)) {
        size_t comma = line.find(','); string name = line.substr(0, comma); int count = stoi(line.substr(comma + 1));
        bool found = false; for (int i = 0; i < candidateCount; ++i) if (candidates[i].getName() == name) {
            for (int j = 0; j < count; ++j) candidates[i].incrementVote(); found = true; break;
        }
        if (!found && candidateCount < 10) { Candidate c(name); for (int j = 0; j < count; ++j) c.incrementVote(); candidates[candidateCount++] = c; }
    } fin.close();
}

ElectionSystem::~ElectionSystem() { saveVoters(); saveVotes(); saveAdmins(); }

