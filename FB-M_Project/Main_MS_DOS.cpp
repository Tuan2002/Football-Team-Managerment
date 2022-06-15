#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include "SFML/Audio.hpp"
using namespace std;
// Global Variables
bool savedStatus = true;
bool isAudioOn = false;
// Class Declarations
class footBall_Player;
class footBall_Team;
class footBall_Match;
// Function Prototypes
void clearSystemLog();
string centerAlign(int width, const string &str);
void drawBorder(ofstream &fout, string firstBorder, string expandBorder, int numOfTeam);
void calcPoint(footBall_Match *match, int numofMatch, footBall_Team *team, int numofTeam);
void readFile(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount, footBall_Match *match, int &numOfMatch);
void exportFile(footBall_Team *team, int numOfTeam);
void saveModified(footBall_Team *team, int numOfTeam, footBall_Team *pendingTeam, int pendingTeamAmount, footBall_Match *match, int numOfMatch);
void filter(footBall_Team *team, int n);
void showTeamInfo(footBall_Team *team, int n, string name1, string name2);
void addTeam(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount);
void removeTeam(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount);
void addMatch(footBall_Team *team, int numOfTeam, footBall_Match *match, int &numOfMatch);
void deleteMatch(footBall_Match *match, int &numOfMatch);
void searchMember(footBall_Team *team, int numOfTeam);
void searchTeam(footBall_Team *team, int numOfTeam);
void scoreBoard(footBall_Match *match, int numOfMatch);
void titleBox();
void aboutUS();
class footBall_Player
{
private:
    string name;
    string id;
    string birthDay;
    string nationaly;
    int height;
    int weight;
    string locator;

public:
    footBall_Player();
    footBall_Player(string name, string id, string birthDay, string nationaly, int height, int weight, string locator);
    void showMemberInfo();
    friend class footBall_Team;
};
class footBall_Team
{
private:
    string teamName;
    string country;
    string coach;
    footBall_Player *member;
    int numOfPlayer;
    int point;
    int winMatch;
    int loseMatch;
    int drawMatch;

public:
    footBall_Team();
    footBall_Team(string &teamName, string &country, string &coach);
    void showInfo();
    void showDetail();
    void showPoint();
    string getTeamName();
    string getCoach();
    string getCountry();
    string getMemberName(int index);
    int getPoint();
    void setPoint(int point);
    void setDefaultPoint();
    void setWinMatch(int winMatch);
    void setLoseMatch(int loseMatch);
    void setDrawMatch(int drawMatch);
    bool isPlayerExist(string name);
    footBall_Player searchPlayer(string name);
    void changePlayerInfo();
    void saveChange();
    footBall_Team(footBall_Team &copy);
};
class footBall_Match
{
private:
    string stadium;
    string time;
    string team1Name;
    string team2Name;
    int score1;
    int score2;

public:
    footBall_Match();
    footBall_Match(string stadium, string time, string team1_Name, string team2_Name, int score1, int score2);
    void showMatchInfo();
    void exportMatchInfo(ofstream &fout);
    string getNameTeam1();
    string getNameTeam2();
    friend void calcPoint(footBall_Match *match, int numofMatch, footBall_Team *team, int numofTeam);
};

// Class footBall_Player Methods
footBall_Player ::footBall_Player()
{
    name = "";
    id = "";
    birthDay = "";
    nationaly = "";
    height = 0;
    weight = 0;
    locator = "";
}
footBall_Player ::footBall_Player(string name, string id, string birthDay, string nationaly, int height, int weight, string locator)
{
    this->name = name;
    this->id = id;
    this->birthDay = birthDay;
    this->nationaly = nationaly;
    this->height = height;
    this->weight = weight;
    this->locator = locator;
}
void footBall_Player ::showMemberInfo()
{
    cout << "| " << left << setw(25) << name;
    cout << "| " << left << setw(5) << id;
    cout << "| " << left << setw(11) << birthDay;
    cout << "| " << left << setw(10) << locator;
    cout << "| " << left << setw(4) << weight;
    cout << "| " << left << setw(4) << height;
    cout << "| " << left << setw(10) << nationaly;
    cout << "|" << endl;
}

// Class footBall_Team Methods
footBall_Team ::footBall_Team()
{
    teamName = "";
    country = "";
    coach = "";
    member = NULL;
    numOfPlayer = 0;
    point = 0;
    winMatch = 0;
    loseMatch = 0;
    drawMatch = 0;
}
footBall_Team ::footBall_Team(string &teamName, string &country, string &coach)
{
    this->teamName = teamName;
    this->country = country;
    this->coach = coach;
    numOfPlayer = 0;
    point = 0;
    winMatch = 0;
    loseMatch = 0;
    drawMatch = 0;
    string fileName = "./Danh Sach Cau Thu/" + teamName + ".csv";
    // Ten file vi du "Song Lam Nghe Anh.csv"
    member = new footBall_Player[20];
    ifstream fin;
    fin.open(fileName);
    int count = 0;
    fin.ignore(256, '\n');
    while (!fin.eof())
    {
        string name, id, birthDay, nationaly, locator, height, weight;
        getline(fin, name, ';');
        getline(fin, birthDay, ';');
        getline(fin, nationaly, ';');
        getline(fin, id, ';');
        getline(fin, locator, ';');
        getline(fin, height, ';');
        getline(fin, weight, '\n');
        member[count] = footBall_Player(name, id, birthDay, nationaly, stoi(height), stoi(weight), locator);
        count++;
    }
    numOfPlayer = count;
    fin.close();
}
footBall_Team::footBall_Team(footBall_Team &copy)
{
    this->teamName = copy.teamName;
    this->country = copy.country;
    this->coach = copy.coach;
    this->numOfPlayer = copy.numOfPlayer;
    this->member = new footBall_Player[numOfPlayer];
    for (int i = 0; i < numOfPlayer; i++)
        this->member[i] = copy.member[i];
}
void footBall_Team::showInfo()
{
    cout << "| " << left << setw(25) << teamName
         << "| " << setw(20) << coach
         << "| " << setw(14) << country
         << " |" << endl;
}
void footBall_Team::showDetail()
{
    string border = "+--------------------------+---------------------+----------------+";
    cout << border << endl;
    cout << "| " << left << setw(25) << "TEN DOI"
         << "| " << setw(20) << "HUAN LUYEN VIEN"
         << "| " << setw(14) << "DIA PHUONG"
         << " |" << endl;
    cout << border << endl;
    showInfo();
    cout << border << endl;
    cout << "Danh sach cau thu: " << endl;
    string border1 = "+--------------------------+------+------------+-----------+-----+-----+-----------+";
    cout << border1 << endl;
    cout << "| " << left << setw(25) << "Ho va Ten";
    cout << "| " << left << setw(5) << "CCCD";
    cout << "| " << left << setw(11) << "Ngay Sinh";
    cout << "| " << left << setw(10) << "Vi Tri";
    cout << "| " << left << setw(4) << "CAN";
    cout << "| " << left << setw(4) << "CHC";
    cout << "| " << left << setw(10) << "Quoc Tich";
    cout << "|" << endl;
    cout << border1 << endl;
    for (int i = 0; i < numOfPlayer; i++)
        member[i].showMemberInfo();
    cout << border1 << endl;
}

void footBall_Team::showPoint()
{
    cout << "| " << left << setw(25) << teamName;
    cout << "|   " << left << setw(4) << winMatch;
    cout << "|   " << left << setw(4) << loseMatch;
    cout << "|   " << left << setw(4) << drawMatch;
    cout << "|   " << left << setw(4) << point;
    cout << "|" << endl;
}
string footBall_Team::getTeamName()
{
    return teamName;
}
string footBall_Team::getCoach()
{
    return coach;
}
string footBall_Team::getCountry()
{
    return country;
}
string footBall_Team::getMemberName(int index)
{
    return member[index].name;
}
int footBall_Team::getPoint()
{
    return point;
}
void footBall_Team::setPoint(int point)
{
    this->point += point;
}
void footBall_Team::setDefaultPoint()
{
    this->point = 0;
}
void footBall_Team::setWinMatch(int winMatch)
{
    this->winMatch += winMatch;
}
void footBall_Team::setLoseMatch(int loseMatch)
{
    this->loseMatch += loseMatch;
}
void footBall_Team::setDrawMatch(int drawMatch)
{
    this->drawMatch += drawMatch;
}
bool footBall_Team::isPlayerExist(string name)
{
    for (int i = 0; i < numOfPlayer; i++)
        if (member[i].name == name)
            return true;
    return false;
}
footBall_Player footBall_Team::searchPlayer(string name)
{
    for (int i = 0; i < numOfPlayer; i++)
    {
        if (member[i].name == name)
            return member[i];
    }
    return footBall_Player();
}
void footBall_Team::changePlayerInfo()
{
    string border1 = "+--------------------------+------+------------+-----------+-----+-----+-----------+";
    cout << border1 << endl;
    cout << "| " << left << setw(25) << "Ho va Ten";
    cout << "| " << left << setw(5) << "CCCD";
    cout << "| " << left << setw(11) << "Ngay Sinh";
    cout << "| " << left << setw(10) << "Vi Tri";
    cout << "| " << left << setw(4) << "CAN";
    cout << "| " << left << setw(4) << "CHC";
    cout << "| " << left << setw(10) << "Quoc Tich";
    cout << "|" << endl;
    cout << border1 << endl;
    for (int i = 0; i < numOfPlayer; i++)
    {
        member[i].showMemberInfo();
    }
    cout << border1 << endl;
    cout << "Chon cau thu can thay doi thong tin: ";
    int beSelected;
    cin >> beSelected;
    clearSystemLog();
    cout << "1. Thay doi ten cau thu \n";
    cout << "2. Thay doi ID cau thu \n";
    cout << "3. Thay doi vi tri cau thu \n";
    cout << "4. Thay doi can nang cau thu \n";
    cout << "5. Thay doi chieu cao cau thu \n";
    cout << "6. Thay doi quoc tich cau thu \n";
    cout << "7. Thay doi ngay sinh cau thu \n";
    cout << "Lua chon: ";
    int select;
    cin >> select;
    clearSystemLog();
    while (select <= 7)
    {
        if (select == 1)
        {
            string name;
            cout << "Nhap ten moi: ";
            fflush(stdin);
            getline(cin, name);
            member[beSelected - 1].name = name;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
        if (select == 2)
        {
            string id;
            cout << "Nhap ID moi: ";
            fflush(stdin);
            getline(cin, id);
            member[beSelected - 1].id = id;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
        if (select == 3)
        {
            string locator;
            cout << "Nhap vi tri moi: ";
            fflush(stdin);
            getline(cin, locator);
            member[beSelected - 1].locator = locator;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
        if (select == 4)
        {
            int weight;
            cout << "Nhap can nang moi: ";
            cin >> weight;
            member[beSelected - 1].weight = weight;
            cout << "Thay doi thanh cong!" << endl;
            break;
        }
        if (select == 5)
        {
            int height;
            cout << "Nhap chieu cao moi: ";
            cin >> height;
            member[beSelected - 1].height = height;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
        if (select == 6)
        {
            string nation;
            cout << "Nhap quoc tich moi: ";
            fflush(stdin);
            getline(cin, nation);
            member[beSelected - 1].nationaly = nation;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
        if (select == 7)
        {
            string birth;
            cout << "Nhap ngay sinh moi: ";
            fflush(stdin);
            getline(cin, birth);
            member[beSelected - 1].birthDay = birth;
            cout << "Thay doi thanh cong!" << endl;
            savedStatus = false;
            break;
        }
    }
}
void footBall_Team::saveChange()
{
    string fileName = "./Danh Sach Cau Thu/" + teamName + ".csv";
    ofstream fout;
    fout.open(fileName);
    fout << "HO VA TEN;NGAY SINH;QUOC TICH;SO CCCD;VI TRI;CHIEU CAO;CAN NANG\n";
    for (int i = 0; i < numOfPlayer; i++)
    {
        fout << member[i].name << ";"
             << member[i].birthDay << ";"
             << member[i].nationaly << ";"
             << member[i].id << ";"
             << member[i].locator << ";"
             << member[i].height << ";";
        if (i == numOfPlayer - 1)
        {
            fout << member[i].weight;
            break;
        }
        fout << member[i].weight << endl;
    }
    fout.close();
}

// Class footBall_Match Methods
footBall_Match ::footBall_Match()
{
    stadium = "";
    time = "";
    score1 = 0;
    score2 = 0;
}
footBall_Match ::footBall_Match(string stadium, string time, string team1_Name, string team2_Name, int score1, int score2)
{
    this->stadium = stadium;
    this->time = time;
    this->score1 = score1;
    this->score2 = score2;
    this->team1Name = team1_Name;
    this->team2Name = team2_Name;
}
void footBall_Match::showMatchInfo()
{
    cout << "| " << left << setw(20) << stadium;
    cout << "| " << left << setw(11) << time;
    cout << "| " << left << setw(20) << team1Name;
    cout << "| " << left << setw(5) << score1 << " - " << right << setw(5) << score2;
    cout << " | " << left << setw(20) << team2Name;
    cout << "|" << endl;
}
void footBall_Match::exportMatchInfo(ofstream &fout)
{
    fout << stadium << ";"
         << team1Name << ";"
         << team2Name << ";"
         << time << ";"
         << score1 << ";"
         << score2;
}
string footBall_Match::getNameTeam1()
{
    return team1Name;
}
string footBall_Match::getNameTeam2()
{
    return team2Name;
}

// Define Function

void clearSystemLog()
{
    system("cls");
}

// Fomatting String Align to Center
string centerAlign(int width, const string &str)
{
    int len = str.length();
    if (width < len)
    {
        return str;
    }
    int diff = width - len;
    int pad1 = diff / 2;
    int pad2 = diff - pad1;
    return string(pad1, ' ') + str + string(pad2, ' ');
}
void drawBorder(ofstream &fout, string firstBorder, string expandBorder, int numOfTeam)
{
    fout << firstBorder;
    for (int i = 0; i < numOfTeam; i++)
        fout << expandBorder;
    fout << endl;
}
void calcPoint(footBall_Match *match, int numofMatch, footBall_Team *team, int numofTeam)
{
    for (int i = 0; i < numofTeam; i++)
        team[i].setDefaultPoint();
    for (int i = 0; i < numofMatch; i++)
        if (match[i].score1 > match[i].score2)
            for (int j = 0; j < numofTeam; j++)
            {
                if (match[i].getNameTeam1() == team[j].getTeamName())
                {
                    team[j].setPoint(3);
                    team[j].setWinMatch(1);
                };
                if (match[i].getNameTeam2() == team[j].getTeamName())
                    team[j].setLoseMatch(1);
            }
        else if (match[i].score1 < match[i].score2)
            for (int j = 0; j < numofTeam; j++)
            {
                if (match[i].getNameTeam2() == team[j].getTeamName())
                {
                    team[j].setPoint(3);
                    team[j].setWinMatch(1);
                };
                if (match[i].getNameTeam1() == team[j].getTeamName())
                    team[j].setLoseMatch(1);
            }
        else
            for (int j = 0; j < numofTeam; j++)
            {
                if (match[i].getNameTeam1() == team[j].getTeamName())
                {
                    team[j].setPoint(1);
                    team[j].setDrawMatch(1);
                }
                if (match[i].getNameTeam2() == team[j].getTeamName())
                {
                    team[j].setPoint(1);
                    team[j].setDrawMatch(1);
                }
            }
}
void readFile(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount, footBall_Match *match, int &numOfMatch)
{
    ifstream fin;
    fin.open("./DS Doi Bong.csv");
    string teamName, country, coach, temp;
    int count = 0;
    fin.ignore(256, '\n');
    while (!fin.eof())
    {
        getline(fin, teamName, ';');
        getline(fin, coach, ';');
        getline(fin, temp, '\n');
        int possiton = temp.find('\r');
        country = temp.substr(0, possiton);
        team[count] = footBall_Team(teamName, country, coach);
        count++;
    }
    fin.close();
    numOfTeam = count;
    fin.open("./DS Tran Dau.csv");
    string stadium, time, team1_Name, team2_Name, score1, score2;
    count = 0;
    fin.ignore(256, '\n');
    while (!fin.eof())
    {
        getline(fin, stadium, ';');
        getline(fin, team1_Name, ';');
        getline(fin, team2_Name, ';');
        getline(fin, time, ';');
        getline(fin, score1, ';');
        getline(fin, score2, '\n');
        match[count] = footBall_Match(stadium, time, team1_Name, team2_Name, stoi(score1), stoi(score2));
        count++;
    }
    fin.close();
    numOfMatch = count;
    fin.open("./Doi Bong Cho.csv");
    fin.ignore(256, '\n');
    count = 0;
    while (!fin.eof())
    {
        getline(fin, teamName, ';');
        getline(fin, coach, ';');
        getline(fin, temp, '\n');
        int possiton = temp.find('\r');
        country = temp.substr(0, possiton);
        pendingTeam[count] = footBall_Team(teamName, country, coach);
        count++;
    }
    pendingTeamAmount = count;
    fin.close();
}
void exportFile(footBall_Team *team, int numOfTeam)
{
    string title = "BANG TONG HOP THONG TIN DOI BONG";
    string firstBorder = "+---------------+";
    string expandBorder = "-----------------------+";
    string tilte1 = "|      STT      |";
    string title2 = "|    TEN DOI    |";
    string title3 = "|      HLV      |";
    string title4 = "|   DIA PHUONG  |";
    string title5 = "|   TONG DIEM   |";
    string title6 = "|   DS CAU THU  |";
    string title7 = "|               |";
    ofstream fout;
    int width = 18 + 25 * numOfTeam;
    fout.open("./Export/Bang Tong Hop.txt");
    fout << endl
         << centerAlign(width, title) << endl
         << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << tilte1;
    for (int i = 0; i < numOfTeam; i++)
    {
        fout << centerAlign(23, to_string(i + 1)) << "|";
    }
    fout << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << title2;
    for (int i = 0; i < numOfTeam; i++)
        fout << centerAlign(23, team[i].getTeamName()) << "|";
    fout << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << title3;
    for (int i = 0; i < numOfTeam; i++)
        fout << centerAlign(23, team[i].getCoach()) << "|";
    fout << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << title4;
    for (int i = 0; i < numOfTeam; i++)
        fout << centerAlign(23, team[i].getCountry()) << "|";
    fout << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << title5;
    for (int i = 0; i < numOfTeam; i++)
        fout << centerAlign(23, to_string(team[i].getPoint())) << "|";
    fout << endl;
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    fout << title6;
    for (int i = 0; i < numOfTeam; i++)
        fout << left << " " << setw(22) << team[i].getMemberName(0) << "|";
    fout << endl;
    for (int memberCount = 1; memberCount < 11; memberCount++)
    {
        fout << title7;
        for (int i = 0; i < numOfTeam; i++)
            fout << left << " " << setw(22) << team[i].getMemberName(memberCount) << "|";
        fout << endl;
    }
    drawBorder(fout, firstBorder, expandBorder, numOfTeam);
    const time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    string modifiedDay = "Ngay Tong Hop: " + to_string(localTime->tm_mday) + "/" + to_string(localTime->tm_mon + 1) + "/" + to_string(localTime->tm_year + 1900) + " - " + to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min) + ":" + to_string(localTime->tm_sec);
    fout << centerAlign(width, modifiedDay) << endl;
}
void saveModified(footBall_Team *team, int numOfTeam, footBall_Team *pendingTeam, int pendingTeamAmount, footBall_Match *match, int numOfMatch)
{
    ofstream fout;
    fout.open("./DS Tran Dau.csv");
    fout << "SAN VAN DONG;DOI A;DOI B;THOI GIAN;SBT DOI A;SBT DOI B" << endl;
    for (int i = 0; i < numOfMatch; i++)
    {
        match[i].exportMatchInfo(fout);
        if (i == numOfMatch - 1)
            break;
        fout << endl;
    }
    fout.close();
    fout.open("./DS Doi Bong.csv");
    fout << "TEN DOI BONG;HUAN LUYEN VIEN;DIA PHUONG\n";
    for (int i = 0; i < numOfTeam; i++)
    {
        fout << team[i].getTeamName() << ";"
             << team[i].getCoach() << ";";
        if (i == numOfTeam - 1)
        {
            fout << team[i].getCountry();
            break;
        }
        fout << team[i].getCountry() << endl;
    }
    fout.close();
    fout.open("./Doi Bong Cho.csv");
    fout << "TEN DOI BONG;HUAN LUYEN VIEN;DIA PHUONG\n";
    for (int i = 0; i < pendingTeamAmount; i++)
    {
        fout << pendingTeam[i].getTeamName() << ";"
             << pendingTeam[i].getCoach() << ";";
        if (i == pendingTeamAmount - 1)
        {
            fout << pendingTeam[i].getCountry();
            break;
        }
        fout << pendingTeam[i].getCountry() << endl;
    }
    fout.close();
    for (int i = 0; i < numOfTeam; i++)
        team[i].saveChange();
}
void filter(footBall_Team *team, int n, sf::Sound options)
{
    int FILT_ARRAY[50];
    int count = 0;
    int choice;
    if (isAudioOn == true)
        options.play();
    cout << "1. Loc cac doi bong theo dia phuong" << endl;
    cout << "2. Loc cac doi bong theo diem" << endl;
    cout << "3. Sap xep cac doi theo diem tu cao den thap" << endl;
    cout << "4. Tro ve menu" << endl;
    cout << "Nhap lua chon: ";
    cin >> choice;
    string country;
    int point;
    switch (choice)
    {
    case 1:
        cout << "Nhap dia phuong can loc: ";
        fflush(stdin);
        getline(cin, country);
        for (int i = 0; i < n; i++)
            if (team[i].getCountry() == country)
            {
                FILT_ARRAY[count] = i;
                count++;
            }
        clearSystemLog();
        if (count == 0)
            cout << "Khong co doi bong nao nam trong dia phuong nay" << endl;
        else
        {
            cout << "Co (" << count << ") doi bong thuoc dia phuong: " << country << endl;
            for (int i = 0; i < count; i++)
                team[FILT_ARRAY[i]].showDetail();
        }
        break;
    case 2:
        cout << "Nhap so diem can loc: ";
        cin >> point;
        for (int i = 0; i < n; i++)
            if (team[i].getPoint() == point)
            {
                FILT_ARRAY[count] = i;
                count++;
            }
        clearSystemLog();
        if (count == 0)
            cout << "Khong co doi bong nao co diem: " << point << endl;
        else
        {
            cout << "Co (" << count << ") doi bong co diem: " << point << endl;
            for (int i = 0; i < count; i++)
                team[FILT_ARRAY[i]].showDetail();
        }
        break;
    case 3:

        footBall_Team temp;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (team[i].getPoint() < team[j].getPoint())
                {
                    temp = team[i];
                    team[i] = team[j];
                    team[j] = temp;
                }
        savedStatus = false;
        clearSystemLog();
        string border = "+--------------------------+---------------------+----------------+";
        cout << "Danh sach doi bong sau khi sap xep: " << endl;
        cout << border << endl;
        cout << "| " << left << setw(25) << "TEN DOI"
             << "| " << setw(20) << "HUAN LUYEN VIEN"
             << "| " << setw(14) << "DIA PHUONG"
             << " |" << endl;
        cout << border << endl;
        for (int i = 0; i < n; i++)
            team[i].showInfo();
        cout << border << endl;
        break;
    }
}
void showTeamInfo(footBall_Team *team, int n, string name1, string name2)
{
    clearSystemLog();
    cout << "Thong tin doi thu nhat: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name1)
            team[i].showDetail();
    cout << "Bam phim ENTER de tiep tuc xem ... ";
    fflush(stdin);
    getchar();
    clearSystemLog();
    cout << "Thong tin doi thu hai: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name2)
            team[i].showDetail();
}
void addTeam(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount)
{
    clearSystemLog();
    string border = "+--------------------------+---------------------+----------------+";
    cout << border << endl;
    cout << "| " << left << setw(25) << "TEN DOI"
         << "| " << setw(20) << "HUAN LUYEN VIEN"
         << "| " << setw(14) << "DIA PHUONG"
         << " |" << endl;
    cout << border << endl;
    for (int i = 0; i < pendingTeamAmount; i++)
        pendingTeam[i].showInfo();
    cout << border << endl;
    int select;
    cout << "Co (" << pendingTeamAmount << ") doi bong trong danh sach cho" << endl;
    cout << "Chon doi bong co trong danh sach de them: ";
    cin >> select;
    team[numOfTeam] = pendingTeam[select - 1];
    numOfTeam++;
    for (int i = select - 1; i < pendingTeamAmount - 1; i++)
        pendingTeam[i] = pendingTeam[i + 1];
    pendingTeamAmount--;
    cout << "Doi bong da duoc them vao danh sach" << endl;
    savedStatus = false;
}
void removeTeam(footBall_Team *team, int &numOfTeam, footBall_Team *pendingTeam, int &pendingTeamAmount)
{
    clearSystemLog();
    string border = "+--------------------------+---------------------+----------------+";
    cout << border << endl;
    cout << "| " << left << setw(25) << "TEN DOI"
         << "| " << setw(20) << "HUAN LUYEN VIEN"
         << "| " << setw(14) << "DIA PHUONG"
         << " |" << endl;
    cout << border << endl;
    for (int i = 0; i < numOfTeam; i++)
        team[i].showInfo();
    cout << border << endl;
    int select;
    cout << "Chon doi bong co trong danh sach can xoa: ";
    cin >> select;
    pendingTeam[pendingTeamAmount] = team[select - 1];
    pendingTeamAmount++;
    for (int i = select - 1; i < numOfTeam - 1; i++)
    {
        team[i] = team[i + 1];
    }
    numOfTeam--;
    cout << "Da xoa mot doi bong thanh cong!\n";
    savedStatus = false;
}
void addMatch(footBall_Team *team, int numOfTeam, footBall_Match *match, int &numOfMatch)
{
    clearSystemLog();
    string teamName1, teamName2, stadium, time;
    int score1, score2;
    int select1, select2;
    string border = "+--------------------------+---------------------+----------------+";
    cout << border << endl;
    cout << "| " << left << setw(25) << "TEN DOI"
         << "| " << setw(20) << "HUAN LUYEN VIEN"
         << "| " << setw(14) << "DIA PHUONG"
         << " |" << endl;
    cout << border << endl;
    for (int i = 0; i < numOfTeam; i++)
        team[i].showInfo();
    cout << border << endl;
    cout << "Chon doi thu nhat: ";
    cin >> select1;
    cout << "Chon doi thu hai: ";
    cin >> select2;
    teamName1 = team[select1 - 1].getTeamName();
    teamName2 = team[select2 - 1].getTeamName();
    cout << "Nhap ten SVD: ";
    fflush(stdin);
    getline(cin, stadium);
    cout << "Nhap thoi gian: ";
    fflush(stdin);
    getline(cin, time);
    cout << "Nhap ti so cua tran dau: ";
    cin >> score1 >> score2;
    match[numOfMatch] = footBall_Match(stadium, time, teamName1, teamName2, score1, score2);
    numOfMatch++;
    cout << "Da them mot tran dau thanh cong!\n";
    savedStatus = false;
}
void deleteMatch(footBall_Match *match, int &numOfMatch)
{
    string border = "+---------------------+------------+---------------------+---------------+---------------------+";
    cout << border << endl;
    cout << "| " << left << setw(20) << "SAN VAN DONG";
    cout << "| " << setw(11) << "THOI GIAN";
    cout << "| " << setw(20) << "TEN DOI BONG A";
    cout << "| " << setw(14) << "    TI SO";
    cout << "| " << setw(20) << "TEN DOI BONG B";
    cout << "|" << endl;
    cout << border << endl;
    for (int i = 0; i < numOfMatch; i++)
        match[i].showMatchInfo();
    cout << border << endl;
    int selectMatch;
    cout << "Chon mot tran dau can xoa: ";
    cin >> selectMatch;
    for (int i = selectMatch - 1; i < numOfMatch - 1; i++)
    {
        match[i] = match[i + 1];
    }
    numOfMatch--;
    cout << "Da xoa tran dau thanh cong!" << endl;
    savedStatus = false;
}
void searchMember(footBall_Team *team, int numOfTeam)
{
    footBall_Player *searchResult = new footBall_Player[10];
    string name;
    cout << "Nhap ten can thu can tim: ";
    fflush(stdin);
    getline(cin, name);
    int count = 0;
    for (int i = 0; i < numOfTeam; i++)
        if (team[i].isPlayerExist(name) == true)
        {
            searchResult[count] = team[i].searchPlayer(name);
            count++;
        }
    string border1 = "+--------------------------+------+------------+-----------+-----+-----+-----------+";
    if (count > 0)
    {
        cout << border1 << endl;
        cout << "| " << left << setw(25) << "Ho va Ten";
        cout << "| " << left << setw(5) << "CCCD";
        cout << "| " << left << setw(11) << "Ngay Sinh";
        cout << "| " << left << setw(10) << "Vi Tri";
        cout << "| " << left << setw(4) << "CAN";
        cout << "| " << left << setw(4) << "CHC";
        cout << "| " << left << setw(10) << "Quoc Tich";
        cout << "|" << endl;
        cout << border1 << endl;
        for (int i = 0; i < count; i++)
            searchResult[i].showMemberInfo();
        cout << border1 << endl;
    }
    else
    {
        cout << "Khong tim thay cau thu nao co ten: " << name << endl;
    }
}
void searchTeam(footBall_Team *team, int numOfTeam)
{
    footBall_Team searchResult;
    string name;
    bool isExist = false;
    cout << "Nhap ten doi can tim: ";
    fflush(stdin);
    getline(cin, name);
    for (int i = 0; i < numOfTeam; i++)
        if (team[i].getTeamName() == name)
        {
            searchResult = team[i];
            isExist = true;
            break;
        }
    if (isExist == true)
    {
        cout << "Ket qua tim kiem: " << endl;
        searchResult.showDetail();
    }
    else
    {
        cout << "Khong tim thay doi co ten: " << name << endl;
    }
}
void changMemberInfo(footBall_Team *team, int numOfTeam)
{
    clearSystemLog();
    string border = "+--------------------------+---------------------+----------------+";
    cout << border << endl;
    cout << "| " << left << setw(25) << "TEN DOI"
         << "| " << setw(20) << "HUAN LUYEN VIEN"
         << "| " << setw(14) << "DIA PHUONG"
         << " |" << endl;
    cout << border << endl;
    for (int i = 0; i < numOfTeam; i++)
        team[i].showInfo();
    cout << border << endl;
    int select;
    cout << "Chon doi bong: ";
    cin >> select;
    team[select - 1].changePlayerInfo();
}
void scoreBoard(footBall_Match *match, int numOfMatch)
{
    string border = "+---------------------+------------+---------------------+---------------+---------------------+";
    cout << border << endl;
    cout << "| " << left << setw(20) << "SAN VAN DONG";
    cout << "| " << setw(11) << "THOI GIAN";
    cout << "| " << setw(20) << "TEN DOI BONG A";
    cout << "| " << setw(14) << "    TI SO";
    cout << "| " << setw(20) << "TEN DOI BONG B";
    cout << "|" << endl;
    cout << border << endl;
    for (int i = 0; i < numOfMatch; i++)
        match[i].showMatchInfo();
    cout << border << endl;
}
void titleBox()
{
    string border0 = "*********************************************";
    string border1 = "*                                           *";
    string border3 = "*             VINH UNIVERSITY               *";
    string border4 = "*    FOOTBALL PLAYER MANAGERMENT PROGRAM    *";
    string border6 = "*           Developed by Team 5             *";
    string border7 = "*          Supported by Kim Oanh            *";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << border0 << endl;
    cout << border1 << endl;
    cout << border3 << endl;
    cout << border4 << endl;
    cout << border6 << endl;
    cout << border7 << endl;
    cout << border1 << endl;
    cout << border0 << endl;
}
void aboutUS()
{
    string border0 = "****************************************************";
    string border1 = "*      TEAM 5:                                     *";
    string border2 = "*      Leader:                                     *";
    string border3 = "*      Nguyen Ngoc Anh Tuan                        *";
    string border4 = "*      Members:                                    *";
    string border5 = "*      Nguyen Duy Nguyen                           *";
    string border6 = "*      Bui Truong Phuong                           *";
    string border7 = "*      Duong Dinh Tuan                             *";
    string border8 = "*      Email:                                      *";
    string border9 = "*      contact.footballteammanager@outlook.com     *";
    string border10 = "*              HAVE A GOOD EXPERIENCE              *";
    string border11 = "*                    THANK YOU                     *";
    string border12 = "*                                                  *";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << border0 << endl;
    cout << border12 << endl;
    cout << border1 << endl;
    cout << border12 << endl;
    cout << border2 << endl;
    cout << border3 << endl;
    cout << border4 << endl;
    cout << border5 << endl;
    cout << border6 << endl;
    cout << border7 << endl;
    cout << border12 << endl;
    cout << border8 << endl;
    cout << border9 << endl;
    cout << border12 << endl;
    cout << border0 << endl;
    cout << border12 << endl;
    cout << border10 << endl;
    cout << border11 << endl;
    cout << border12 << endl;
    cout << border0 << endl;
}
int main()
{
    int numOfTeam, pendingTeamAmount, numOfMatch;
    footBall_Team *ListPendingTeam = new footBall_Team[20];
    footBall_Team *ListTeam = new footBall_Team[20];
    footBall_Match *ListMatch = new footBall_Match[20];
    readFile(ListTeam, numOfTeam, ListPendingTeam, pendingTeamAmount, ListMatch, numOfMatch);
    calcPoint(ListMatch, numOfMatch, ListTeam, numOfTeam);

    // Audio Configruation

    sf::SoundBuffer welc, slcOption, slcTeam, slcMatch, about;
    sf::Sound welcome, selectOption, selectTeam, selectMatch, aboutUS;
    if (isAudioOn == true)
    {
        welc.loadFromFile("./Audio/Welcome.wav");
        slcOption.loadFromFile("./Audio/Selectoption.wav");
        slcTeam.loadFromFile("./Audio/Selectteam.wav");
        slcMatch.loadFromFile("./Audio/Selectmatch.wav");
        about.loadFromFile("./Audio/About.wav");
        welcome.setBuffer(welc);
        selectOption.setBuffer(slcOption);
        selectTeam.setBuffer(slcTeam);
        selectMatch.setBuffer(slcMatch);
        aboutUS.setBuffer(about);
    }
    // Menu Configruation

    clearSystemLog();
    int choice;
    titleBox();
    if (isAudioOn == true)
    {
        welcome.play();
        sleep(4);
    }
    while (choice != 9)
    {
        cout << "0. Xuat bang tong hop thong tin" << endl;
        cout << "1. Xem thong tin cac doi bong" << endl;
        cout << "2. Xem thong tin cac tran dau" << endl;
        cout << "3. Bang thong ke diem" << endl;
        cout << "4. Loc va sap xep du lieu" << endl;
        cout << "5. Chinh sua du lieu" << endl;
        cout << "6. Tim kiem thong tin" << endl;
        cout << "7. Luu du lieu" << endl;
        cout << "8. Gioi thieu ve chung toi" << endl;
        cout << "9. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        if (isAudioOn == true)
            selectOption.play();
        cin >> choice;
        switch (choice)
        {
        case 0:
            clearSystemLog();
            exportFile(ListTeam, numOfTeam);
            cout << "Xuat file thanh cong" << endl;
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            clearSystemLog();
            titleBox();
            break;
        case 1:
        {
            clearSystemLog();
            string border = "+--------------------------+---------------------+----------------+";
            cout << border << endl;
            cout << "| " << left << setw(25) << "TEN DOI"
                 << "| " << setw(20) << "HUAN LUYEN VIEN"
                 << "| " << setw(14) << "DIA PHUONG"
                 << " |" << endl;
            cout << border << endl;
            for (int i = 0; i < numOfTeam; i++)
                ListTeam[i].showInfo();
            cout << border << endl;
            int select;
            if (isAudioOn == true)
                selectTeam.play();
            cout << "Chon doi bong can xem thong tin chi tiet: ";
            cin >> select;
            clearSystemLog();
            ListTeam[select - 1].showDetail();
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            clearSystemLog();
            titleBox();
            break;
        }
        case 2:
        {
            int selection;
            clearSystemLog();
            scoreBoard(ListMatch, numOfMatch);
            if (isAudioOn == true)
                selectOption.play();
            cout << "1. Xem thong tin chi tiet hai doi" << endl;
            cout << "2. Xem thong ke diem cua hai doi" << endl;
            cout << "3. Tro ve menu" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
            {
                clearSystemLog();
                scoreBoard(ListMatch, numOfMatch);
                if (isAudioOn == true)
                    selectMatch.play();
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                showTeamInfo(ListTeam, numOfTeam, ListMatch[choice - 1].getNameTeam1(), ListMatch[choice - 1].getNameTeam2());
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            }
            case 2:
            {
                clearSystemLog();
                scoreBoard(ListMatch, numOfMatch);
                if (isAudioOn == true)
                    selectMatch.play();
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                clearSystemLog();
                string border = "+--------------------------+-------+-------+-------+-------+";
                cout << border << endl;
                cout << "| " << left << setw(25) << "TEN DOI BONG"
                     << "| " << setw(6) << "THANG"
                     << "| " << setw(6) << "THUA"
                     << "| " << setw(6) << " HOA"
                     << "| " << setw(6) << "DIEM"
                     << "|" << endl;
                cout << border << endl;
                for (int i = 0; i < numOfTeam; i++)
                {
                    if (ListTeam[i].getTeamName() == ListMatch[choice - 1].getNameTeam1())
                        ListTeam[i].showPoint();
                    if (ListTeam[i].getTeamName() == ListMatch[choice - 1].getNameTeam2())
                        ListTeam[i].showPoint();
                }
                cout << border << endl;
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            }
            case 3:
            {
                clearSystemLog();
                titleBox();
                break;
            }
            }
            break;
        }
        case 3:
        {
            clearSystemLog();
            cout << "Thong tin diem cua cac doi bong: " << endl;
            string border = "+--------------------------+-------+-------+-------+-------+";
            cout << border << endl;
            cout << "| " << left << setw(25) << "TEN DOI BONG"
                 << "| " << setw(6) << "THANG"
                 << "| " << setw(6) << "THUA"
                 << "| " << setw(6) << " HOA"
                 << "| " << setw(6) << "DIEM"
                 << "|" << endl;
            cout << border << endl;
            for (int i = 0; i < numOfTeam; i++)
                ListTeam[i].showPoint();
            cout << border << endl;
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            clearSystemLog();
            titleBox();
            break;
        }
        case 4:
        {
            clearSystemLog();
            filter(ListTeam, numOfTeam, selectOption);
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            clearSystemLog();
            titleBox();
            break;
        }
        case 5:
        {
            clearSystemLog();
            int selection;
            if (isAudioOn == true)
                selectOption.play();
            cout << "1. Them doi bong tu danh sach cho" << endl;
            cout << "2. Xoa doi bong" << endl;
            cout << "3. Them tran dau" << endl;
            cout << "4. Xoa tran dau" << endl;
            cout << "5. Chinh sua thong tin cau thu" << endl;
            cout << "6. Tro ve menu" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
                addTeam(ListTeam, numOfTeam, ListPendingTeam, pendingTeamAmount);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            case 2:
                removeTeam(ListTeam, numOfTeam, ListPendingTeam, pendingTeamAmount);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            case 3:
                addMatch(ListTeam, numOfTeam, ListMatch, numOfMatch);
                calcPoint(ListMatch, numOfMatch, ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            case 4:
                deleteMatch(ListMatch, numOfMatch);
                calcPoint(ListMatch, numOfMatch, ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            case 5:
                changMemberInfo(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            default:
                clearSystemLog();
                titleBox();
            }
            break;
        }
        case 6:
        {
            clearSystemLog();
            int selection;
            if (isAudioOn == true)
                selectOption.play();
            cout << "1. Tim kiem cau thu" << endl;
            cout << "2. Tim kiem doi bong" << endl;
            cout << "3. Tro ve menu" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
                clearSystemLog();
                searchMember(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            case 2:
                clearSystemLog();
                searchTeam(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                clearSystemLog();
                titleBox();
                break;
            }
        default:
            clearSystemLog();
            titleBox();
            break;
        }
        case 7:
        {
            clearSystemLog();
            if (savedStatus == false)
            {
                saveModified(ListTeam, numOfTeam, ListPendingTeam, pendingTeamAmount, ListMatch, numOfMatch);
                cout << "Da luu du lieu thanh cong!" << endl;
                savedStatus = true;
            }
            else
                cout << "Du lieu khong co su thay doi!" << endl;
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            clearSystemLog();
            titleBox();
            break;
        }
        case 8:
        {
            clearSystemLog();
            ::aboutUS();
            if (isAudioOn == true)
                aboutUS.play();
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            if (isAudioOn == true)
                aboutUS.stop();
            clearSystemLog();
            titleBox();
            break;
        }
        case 9:
        {
            if (savedStatus == false)
            {
                cout << "Ban chua luu du lieu, ban co muon luu khong? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    saveModified(ListTeam, numOfTeam, ListPendingTeam, pendingTeamAmount, ListMatch, numOfMatch);
                    cout << "Da luu du lieu thanh cong!" << endl;
                    savedStatus = true;
                }
            }
            break;
        }
        }
    }
    return 0;
}