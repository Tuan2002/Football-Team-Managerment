#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include "SFML/Audio.hpp"
using namespace std;
class footBall_Player
{
protected:
    string name;
    string id;
    string birthDay;
    string nationaly;
    int height;
    int weight;
    string locator;

public:
    footBall_Player()
    {
        name = "";
        id = "";
        birthDay = "";
        nationaly = "";
        height = 0;
        weight = 0;
        locator = "";
    }
    footBall_Player(string name, string id, string birthDay, string nationaly, int height, int weight, string locator)
    {
        this->name = name;
        this->id = id;
        this->birthDay = birthDay;
        this->nationaly = nationaly;
        this->height = height;
        this->weight = weight;
        this->locator = locator;
    }
    void showMemberInfo()
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
    friend class footBall_Team;
};
class footBall_Team
{
protected:
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
    footBall_Team()
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
    footBall_Team(string &teamName, string &country, string &coach)
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
    void showInfo()
    {
        cout << "| " << left << setw(25) << teamName
             << "| " << setw(20) << coach
             << "| " << setw(14) << country
             << " |" << endl;
    }
    void showDetail()
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
    void showPoint()
    {
        cout << "| " << left << setw(25) << teamName;
        cout << "|   " << left << setw(4) << winMatch;
        cout << "|   " << left << setw(4) << loseMatch;
        cout << "|   " << left << setw(4) << drawMatch;
        cout << "|   " << left << setw(4) << point;
        cout << "|" << endl;
    }
    string getTeamName()
    {
        return teamName;
    }
    string getCountry()
    {
        return country;
    }
    int getPoint()
    {
        return point;
    }
    void setPoint(int point)
    {
        this->point += point;
    }
    void setWinMatch(int winMatch)
    {
        this->winMatch += winMatch;
    }
    void setLoseMatch(int loseMatch)
    {
        this->loseMatch += loseMatch;
    }
    void setDrawMatch(int drawMatch)
    {
        this->drawMatch += drawMatch;
    }
    bool isPlayerExist(string name)
    {
        for (int i = 0; i < numOfPlayer; i++)
            if (member[i].name == name)
                return true;
        return false;
    }
    footBall_Player searchPlayer(string name)
    {
        for (int i = 0; i < numOfPlayer; i++)
        {
            if (member[i].name == name)
                return member[i];
        }
        return footBall_Player();
    }
    void changeInfoPllayer()
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
        system("clear");
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
        system("clear");
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
                break;
            }
        }
    }
    footBall_Team(footBall_Team &copy)
    {
        this->teamName = copy.teamName;
        this->country = copy.country;
        this->coach = copy.coach;
        this->numOfPlayer = copy.numOfPlayer;
        this->member = new footBall_Player[numOfPlayer];
        for (int i = 0; i < numOfPlayer; i++)
            this->member[i] = copy.member[i];
    }
};
class footBall_Match
{
protected:
    string stadum;
    string time;
    string team1Name;
    string team2Name;
    int score1;
    int score2;

public:
    footBall_Match()
    {
        stadum = "";
        time = "";
        score1 = 0;
        score2 = 0;
    }
    footBall_Match(string stadum, string time, string team1_Name, string team2_Name, int score1, int score2)
    {
        this->stadum = stadum;
        this->time = time;
        this->score1 = score1;
        this->score2 = score2;
        this->team1Name = team1_Name;
        this->team2Name = team2_Name;
    }
    void showMatchInfo()
    {
        cout << "| " << left << setw(20) << stadum;
        cout << "| " << left << setw(11) << time;
        cout << "| " << left << setw(20) << team1Name;
        cout << "| " << left << setw(5) << score1 << " - " << right << setw(5) << score2;
        cout << " | " << left << setw(20) << team2Name;
        cout << "|" << endl;
    }
    string getNameTeam1()
    {
        return team1Name;
    }
    string getNameTeam2()
    {
        return team2Name;
    }
    friend void calcPoint(footBall_Match *match, int numofMatch, footBall_Team *team, int numofTeam);
};
void calcPoint(footBall_Match *match, int numofMatch, footBall_Team *team, int numofTeam)
{
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
void filTer(footBall_Team *team, int n)
{
    int FIL_ARRAY[50];
    int count = 0;
    int choice;
    cout << "1. Loc cac doi bong theo dia phuong" << endl;
    cout << "2. Loc cac doi bong theo diem" << endl;
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
                FIL_ARRAY[count] = i;
                count++;
            }
        system("clear");
        cout << "Co (" << count << ") doi bong thuoc dia phuong: " << country << endl;
        for (int i = 0; i < count; i++)
            team[FIL_ARRAY[i]].showDetail();
        break;
    case 2:
        cout << "Nhap so diem can loc: ";
        cin >> point;
        for (int i = 0; i < n; i++)
            if (team[i].getPoint() == point)
            {
                FIL_ARRAY[count] = i;
                count++;
            }
        system("cls");
        cout << "Co (" << count << ") doi bong co diem: " << point << endl;
        for (int i = 0; i < count; i++)
            team[FIL_ARRAY[i]].showDetail();
        break;
    }
}
void readFile(footBall_Team *team, int &numOfTeam, footBall_Match *match, int &numOfMatch)
{
    ifstream fin;
    fin.open("./DS Doi Bong.csv");
    int count = 0;
    fin.ignore(256, '\n');
    while (!fin.eof())
    {
        string teamName, country, coach, temp;
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
    count = 0;
    fin.ignore(256, '\n');
    while (!fin.eof())
    {
        string stadum, time, team1_Name, team2_Name, score1, score2;
        getline(fin, stadum, ';');
        getline(fin, team1_Name, ';');
        getline(fin, team2_Name, ';');
        getline(fin, time, ';');
        getline(fin, score1, ';');
        getline(fin, score2, '\n');
        match[count] = footBall_Match(stadum, time, team1_Name, team2_Name, stoi(score1), stoi(score2));
        count++;
    }
    fin.close();
    numOfMatch = count;
}
// Xem Thong tin cua 2 doi trong 1 tran dau
void showTeamInfo(footBall_Team *team, int n, string name1, string name2)
{
    system("clear");
    cout << "Thong tin doi thu nhat: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name1)
            team[i].showDetail();
    cout << "Bam phim ENTER de tiep tuc xem ... ";
    fflush(stdin);
    getchar();
    system("clear");
    cout << "Thong tin doi thu hai: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name2)
            team[i].showDetail();
}
void addTeam(footBall_Team *team, int &numOfTeam)
{
    footBall_Team *pendingTeam = new footBall_Team[20];
    string teamName, country, coach;
    int pendingTeamAmount = 0;
    ifstream fin;
    fin.open("./Doi Bong Cho.csv");
    fin.ignore(256, '\n');
    int count = 0;
    while (!fin.eof())
    {
        string teamName, country, coach, temp;
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
    system("clear");
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
    cout << "Doi bong da duoc them vao danh sach" << endl;
}
void removeTeam(footBall_Team *team, int &numOfTeam)
{
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
    for (int i = select - 1; i < numOfTeam - 1; i++)
    {
        team[i] = team[i + 1];
    }
    numOfTeam--;
    cout << "Da xoa mot doi bong thanh cong!\n";
}
void Delete_Match(footBall_Match *match, int &numOfMatch)
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
    cout << "Da xoa tran dau thanh cong !!" << endl;
}
// Phần tìm kiếm cầu thủ
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
        cout << "Khong tim thay nguoi nao co ten: " << name << endl;
    }
}
// Chinh sua thong tin cua cau thu
void ChangeInfoMember(footBall_Team *team, int numOfTeam)
{
    system("clear");
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
    team[select - 1].changeInfoPllayer();
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
    string border9 = "*      contact.footballteammanager@outlook.com      *";
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
    // Audio Configruation
    sf::SoundBuffer welc, slcOption, slcTeam, slcMatch, about;
    sf::Sound welcome, selectOption, selectTeam, selectMatch, aboutUS;
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

    // Menu Configruation

    system("clear");
    int numOfTeam, numOfMatch;
    footBall_Team *ListTeam = new footBall_Team[20];
    footBall_Match *ListMatch = new footBall_Match[20];
    readFile(ListTeam, numOfTeam, ListMatch, numOfMatch);
    calcPoint(ListMatch, numOfMatch, ListTeam, numOfTeam);
    int choice;
    welcome.play();
    titleBox();
    sleep(4);
    while (choice != 8)
    {
        cout << "1. Xem thong tin cac doi bong" << endl;
        cout << "2. Xem thong tin cac tran dau" << endl;
        cout << "3. Thong ke diem" << endl;
        cout << "4. Loc thong tin" << endl;
        cout << "5. Chinh sua du lieu" << endl;
        cout << "6. Tim kiem cau thu" << endl;
        cout << "7. Gioi thieu ve chung toi" << endl;
        cout << "8. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        selectOption.play();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("clear");
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
            selectTeam.play();
            cout << "Chon doi bong can xem thong tin chi tiet: ";
            cin >> select;
            system("clear");
            ListTeam[select - 1].showDetail();
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            system("clear");
            titleBox();
            break;
        }
        case 2:
        {
            int selection;
            system("clear");
            scoreBoard(ListMatch, numOfMatch);
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
                system("clear");
                scoreBoard(ListMatch, numOfMatch);
                selectMatch.play();
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                showTeamInfo(ListTeam, numOfTeam, ListMatch[choice - 1].getNameTeam1(), ListMatch[choice - 1].getNameTeam2());
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                system("clear");
                titleBox();
                break;
            }
            case 2:
            {
                system("clear");
                scoreBoard(ListMatch, numOfMatch);
                selectMatch.play();
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                system("clear");
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
                system("clear");
                titleBox();
                break;
            }
            case 3:
            {
                system("clear");
                titleBox();
                break;
            }
            }
            break;
        }
        case 3:
        {
            system("clear");
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
            system("clear");
            titleBox();
            break;
        }
        case 4:
        {
            system("clear");
            filTer(ListTeam, numOfTeam);
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            system("clear");
            titleBox();
            break;
        }
        case 5:
        {
            system("clear");
            int selection;
            selectOption.play();
            cout << "1. Them doi bong tu danh sach cho" << endl;
            cout << "2. Xoa doi bong" << endl;
            cout << "3. Them tran dau" << endl;
            cout << "4. Xoa tran dau" << endl;
            cout << "5. Chinh sua thong tin cau thu" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
                addTeam(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                system("clear");
                titleBox();
                break;
            case 2:
                removeTeam(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                system("clear");
                titleBox();
                break;
            case 4:
                Delete_Match(ListMatch, numOfMatch);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                system("clear");
                titleBox();
                break;
            case 5:
                ChangeInfoMember(ListTeam, numOfTeam);
                cout << "Bam ENTER de quay ve man hinh chinh...";
                fflush(stdin);
                getchar();
                system("clear");
                titleBox();
                break;
            }
            break;
        }
        case 6:
        {
            searchMember(ListTeam, numOfTeam);
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            system("clear");
            titleBox();
            break;
        }
        case 7:
        {
            system("clear");
            ::aboutUS();
            aboutUS.play();
            cout << "Bam ENTER de quay ve man hinh chinh...";
            fflush(stdin);
            getchar();
            aboutUS.stop();
            system("clear");
            titleBox();
            break;
        }
        case 8:
        {
            break;
        }
        }
    }
    return 0;
}
