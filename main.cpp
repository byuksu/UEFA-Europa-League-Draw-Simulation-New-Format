#include <iostream>
#include <string>
#include <ctime>
#include "Node.hpp"  
#include "Team.hpp"
#include "NodeLib.hpp"
#include <vector>
//#################################################


//problem pot_countlarını nasıl 3 yapmalıyım?
//yukarıdaki problemi çözerken canmatch fonksiyonunu değiştirdim bu defa segmentation fault aldım.
// isvalid fonksiyonuna gönderilen takımların sırası yanlış düzeltince segmentation fault aldım.
// önce matchcountu kontrol etmeyi dene

//#################################################
using namespace std;
//rakipleri yazdırma
void printOpponents(const Team& team) {
    int i=1;
    for (const nextmatch& match : team.matches) {
        if (match.m == home) {
            cout <<i<<". "<< team.name << " - " << match.opponent << "    (home) "<< endl;
        } else if (match.m == away) {
            cout <<i<<". " << match.opponent << " - " << team.name  << "    (away) "<< endl;
        }
        i++;
    }
}

// Listedeki takım sayısını bulma
int countTeams(Node<Team>* head) {
    int count = 0;
    Node<Team>* current = head;
    while (current != nullptr) {
        count++;
        current = current->NextNode();
    }
    return count;
}
// Ülke kontrolü
bool isValidMatch(const Team& team1, const Team& team2) {
    // Geçersiz takımlara sahip olup olmadığını kontrol et
    if (team1.name.empty() || team2.name.empty()) {
        return false; // Geçersiz takım
    }

    // Daha önce eşleşmiş olmaları durumu
    for (const nextmatch& match : team1.matches) {
        if (match.opponent == team2.name) {
            return false; // Daha önce eşleşmişler
        }
    }

    // Aynı ülkeden olamazlar
    if (team1.country == team2.country) {
        return false; // Aynı ülke
    }

    // Pot karşılaşma limitine ulaşıldıysa eşleşemez
    if (team2.pot_count[team1.pot-1] >= 3) {
        return false; // Pot karşılaşma limiti aşıldı
    }

    // Her iki takım da daha önce ev sahibi olarak aynı pottan bir takım ile eşleştiyse, bu takımlar birbirine karşı eşleşemez
    if (team1.pot_count[team1.pot-1] == 1 && team2.pot_count[team1.pot-1] == 1) {
        return false; // Her iki takım da ev sahibi olarak eşleşemez
    }

    // Her iki takım da daha önce aynı pottan bir takım ile deplasmanda eşleştiyse, bu takımlar birbirine karşı eşleşemez
    if (team1.pot_count[team1.pot-1] == 2 && team2.pot_count[team1.pot-1] == 2) {
        return false; // Her iki takım da deplasmanda eşleşemez
    }

    // Takımlar aynı pottaki maçlarını tamamladıysa eşleşme yapılamaz
    if (team1.pot_count[team1.pot-1] == 3 || team2.pot_count[team1.pot-1] == 3) {
        return false; // Eşleşme tamamlandı
    }

    return true; // Tüm kontrolleri geçti, eşleşme yapılabilir
}

string matchToString(match m) {
    switch(m) {
        case home:
            return "home";
        case away:
            return "away";
        case unselected:
        default:
            return "unselected";
    }
}

void canmatch(Team& team1, Team& selected_team) {
    int randomMatchType;
    if(team1.pot_count[selected_team.pot-1]==0){
        // Ev sahibi ve deplasman durumunu rastgele seç
        randomMatchType = rand() % 2; // 0: home, 1: away
    }else if(team1.pot_count[selected_team.pot-1]==1){
        randomMatchType=1;
    }else if(team1.pot_count[selected_team.pot-1]==2){
        randomMatchType=0;
    }else if(team1.pot_count[selected_team.pot-1]==3)
        cout<<"no more match for "<<team1.name<<endl;

    if (randomMatchType == 0) {
        // team1 ev sahibi, selected_team deplasmanda
        team1.addMatch(selected_team.name, home);
        if((team1.match_count % 2) == 0)
            team1.pot_count[selected_team.pot-1] = 3; //home and away işaretlendi
        else
            team1.pot_count[selected_team.pot-1] = 1; //  home işaretlendi

        selected_team.addMatch(team1.name, away);
        if((selected_team.match_count % 2) == 0)
            selected_team.pot_count[team1.pot-1] = 3; //home and away işaretlendi
        else
            selected_team.pot_count[team1.pot-1] = 2; //  away işaretlendi
        
    } else {
        // team1 deplasmanda, selected_team ev sahibi
        team1.addMatch(selected_team.name, away);
        if((team1.match_count % 2) == 0)
            team1.pot_count[selected_team.pot-1] = 3; //home and away işaretlendi
        else
            team1.pot_count[selected_team.pot-1] = 2; //  away işaretlendi
        
        selected_team.addMatch(team1.name, home);
        if((selected_team.match_count % 2) == 0)
            selected_team.pot_count[team1.pot-1] = 3; //home and away işaretlendi
        else
            selected_team.pot_count[team1.pot-1] = 1; //  home işaretlendi
        
    }
}

void drawmatch(Team &team1, Node<Team>* &pot){
    if (pot == nullptr) {
        cerr << "pot is empty!" << endl;
        exit(1);
    }
    int teamCount = countTeams(pot);
    int randomIndex = rand() % teamCount;  // 0 ile takım sayısı arasında rastgele bir index
    
    Node<Team>* current = pot;
    Node<Team>* prev = nullptr;

    // İlk düğüm mü seçildi?
    if (randomIndex == 0) {
        Team selected_team = pot->data;
        //önce ülke kontrolü yap
        //rakip kontrolü yap (daha önce aynı pottan 2 takım ile maç yaptı mı?)
        // uyuşmazsa randomIndexi bir arttır
        
        if(isValidMatch(selected_team,team1)){
            //burada seçilen takımı team1 ile eşleştir
            canmatch(team1,selected_team);
        }else {
            // burayı düzelt kod iki defa yazıldı
            randomIndex++;
            // İlerleyerek rastgele düğüme git
            for (int i = 0; i < randomIndex; i++) {
                prev = current;
                current = current->NextNode();
            }

            // Şu an rastgele düğüme geldik
            Team selected_team = current->data;
            //burada seçilen takımı team1 ile eşleştir
            if(isValidMatch(selected_team,team1)){
                    //burada seçilen takımı team1 ile eşleştir
                    canmatch(team1,selected_team);
                }else drawmatch(team1,pot);
        }

    }else{
            // İlerleyerek rastgele düğüme git
            for (int i = 0; i < randomIndex; i++) {
                prev = current;
                current = current->NextNode();
            }

            // Şu an rastgele düğüme geldik
            Team selected_team = current->data;
            //burada seçilen takımı team1 ile eşleştir
            if(isValidMatch(selected_team,team1)){
                    //burada seçilen takımı team1 ile eşleştir
                    canmatch(team1,selected_team);
                }else drawmatch(team1,pot);
    }





}
// Rastgele bir index'teki takımı seçme ve silme
Team removeRandomTeam(Node<Team>* &head) {
    if (head == nullptr) {
        cerr << "List is empty!" << endl;
        exit(1);
    }

    int teamCount = countTeams(head);
    int randomIndex = rand() % teamCount;  // 0 ile takım sayısı arasında rastgele bir index

    Node<Team>* current = head;
    Node<Team>* prev = nullptr;

    // İlk düğüm mü seçildi?
    if (randomIndex == 0) {
        Team selected_team = head->data;
        Node<Team>* temp = head;
        head = head->NextNode();  // Yeni head'e geç
        delete temp;  // Eski başı sil
        return selected_team;
    }

    // İlerleyerek rastgele düğüme git
    for (int i = 0; i < randomIndex; i++) {
        prev = current;
        current = current->NextNode();
    }

    // Şu an rastgele düğüme geldik
    Team selected_team = current->data;
    prev->delete_after();
    // 'delete current;' kaldırıldı

    return selected_team;
}

// Listedeki tüm takımları yazdırma
void printTeams(Node<Team>* head) {
    if(head==nullptr){
        cerr<<"no any team in the pot"<<endl;
        return;
    }
    Node<Team>* current = head;
    while (current != nullptr) {
        current->data.print();
        current = current->NextNode();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    
    Node<Team>* pot1 = nullptr;
    Node<Team>* pot2 = nullptr;
    Node<Team>* pot3 = nullptr;
    Node<Team>* pot4 = nullptr;
    cout << "Creating the teams in the pot 1........................" << endl;
    InsertRear(pot1,Team("AS Roma", "Italy", 1));
    InsertRear(pot1,Team("Manchester United", "England", 1));
    InsertRear(pot1,Team("Porto", "Portugal", 1));
    InsertRear(pot1,Team("Ajax", "Netherlands", 1));
    InsertRear(pot1,Team("Rangers", "Scotland", 1));
    InsertRear(pot1,Team("Eintracht Frankfurt", "Germany", 1));
    InsertRear(pot1,Team("Lazio", "Italy", 1));
    InsertRear(pot1,Team("Tottenham", "England", 1));
    InsertRear(pot1,Team("Slavia Praha", "Czechia", 1));
    cout<<"_______________________________________________________"<<endl;
    cout << "Pot 1 Teams: " << endl;
    printTeams(pot1);
    cout<<"_______________________________________________________"<<endl;

    cout << "Creating the teams in the Pot 2........................" << endl;
    InsertRear(pot2,Team("Real Sociedad", "Spain", 2));
    InsertRear(pot2,Team("AZ Alkmaar", "Netherlands", 2));
    InsertRear(pot2,Team("Braga", "Portugal", 2));
    InsertRear(pot2,Team("Olympiacos", "Greece", 2));
    InsertRear(pot2,Team("Lyon", "France", 2));
    InsertRear(pot2,Team("Crvena Zvezda", "Serbia", 2));
    InsertRear(pot2,Team("PAOK", "Greece", 2));
    InsertRear(pot2,Team("Fenerbahçe", "Turkey", 2));
    InsertRear(pot2,Team("LASK", "Austria", 2));
    cout<<"_______________________________________________________"<<endl;
    cout << "Pot 2 Teams: " << endl;
    printTeams(pot2);
    cout<<"_______________________________________________________"<<endl;

    cout << "Creating the teams in the Pot 3........................" << endl;
    InsertRear(pot3,Team("Maccabi Tel Aviv", "Israel", 3));
    InsertRear(pot3,Team("Ferencváros", "Hungary", 3));
    InsertRear(pot3,Team("Qarabağ", "Azerbaijan", 3));
    InsertRear(pot3,Team("Galatasaray", "Turkey", 3));
    InsertRear(pot3,Team("Slovan Bratislava", "Slovakia", 3));
    InsertRear(pot3,Team("Viktoria Plzeň", "Czech Republic", 3));
    InsertRear(pot3,Team("Union SG", "Belgium", 3));
    InsertRear(pot3,Team("Dynamo Kyiv", "Ukraine", 3));
    InsertRear(pot3,Team("Ludogorets", "Bulgaria", 3));
    cout<<"_______________________________________________________"<<endl;
    cout << "Pot 3 Teams: " << endl;
    printTeams(pot3);
    cout<<"_______________________________________________________"<<endl;

    cout << "Creating the teams in the Pot 4........................" << endl;
    InsertRear(pot4,Team("Malmö", "Sweden", 4));
    InsertRear(pot4,Team("Athletic Club", "Spain", 4));
    InsertRear(pot4,Team("Hoffenheim", "Germany", 4));
    InsertRear(pot4,Team("Nice", "France", 4));
    InsertRear(pot4,Team("APOEL Nicosia", "Cyprus", 4));
    InsertRear(pot4,Team("Anderlecht", "Belgium", 4));
    InsertRear(pot4,Team("Twente", "Netherlands", 4));
    InsertRear(pot4,Team("Beşiktaş", "Turkey", 4));
    InsertRear(pot4,Team("Elfsborg", "Sweden", 4));
    cout<<"_______________________________________________________"<<endl;
    cout << "Pot 4 Teams: " << endl;
    printTeams(pot4);
    cout<<"_______________________________________________________"<<endl;

    cout<<"Start to choose select a team from pot 1 by press 1"<<endl;
    int x=0;
    cin>>x;
    while (x==1){
        if(pot1 != nullptr){
        //Node<Team>* p1 = nullptr;
        Team selected_team = removeRandomTeam(pot1);
        cout<<"_______________________________________________________"<<endl;
        cout<<"opponents for "<<selected_team.name<<" are drawing....\n";
        cout<<"_______________________________________________________"<<endl;
        drawmatch(selected_team,pot1);
        drawmatch(selected_team,pot1);
        drawmatch(selected_team,pot2);
        drawmatch(selected_team,pot2);
        drawmatch(selected_team,pot3);
        drawmatch(selected_team,pot3);
        drawmatch(selected_team,pot4);
        drawmatch(selected_team,pot4);
        printOpponents(selected_team);
        cout<<"_______________________________________________________"<<endl;
        cout<<"Start to choose select a team from pot 1 by press 1"<<endl;
        x=0;
        cin>>x;
    }
    
    }

    ClearList(pot1);
    ClearList(pot2);
    ClearList(pot3);
    ClearList(pot4);
    return 0;
}
