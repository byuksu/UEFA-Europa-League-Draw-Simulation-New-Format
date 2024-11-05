#pragma once
#include <iostream>
#include <vector>
using namespace std;
enum match{
    unselected,
    home,
    away
};
class nextmatch{
    public:
        string  opponent;
        match m=unselected;
    
    nextmatch(string rakip, match match_type):opponent(rakip), m(match_type){}
};
class Team {
public:
    string name;
    string country;
    int pot;
    vector<nextmatch> matches;  // 8 maç için bir liste
    int match_count=0;
    int pot_count[4]={0,0,0,0}; //her takım her pottan iki takım ile eşleşir.
    // 0: eşleşmemiş
    // 1: home
    // 2: away
    // 3: home and away
    Team(string n, string c, int p) : name(n), country(c), pot(p) {}
    // Maç ekleme fonksiyonu
    void addMatch(const string& opponent, match m) {
        matches.emplace_back(opponent, m); // Doğrudan vector'e push_back yerine emplace_back kullanıldı
        match_count++;
    }
    //print opponents.
    // extra print team function
    void print() const {
        cout << name << " from " << country << endl;
    }
};