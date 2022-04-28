#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
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
        cout << "| "<< left <<setw(25) << name;
        cout << "| "<< left <<setw(5) << id;
        cout << "| "<< left <<setw(11) << birthDay;
        cout << "| "<< left <<setw(10) << locator;
        cout << "| "<< left <<setw(3) << weight;
        cout << "| "<< left <<setw(4) << height;
        cout << "| "<< left <<setw(10) << nationaly;
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

public:
    footBall_Team()
    {
        teamName = "";
        country = "";
        coach = "";
        member = NULL;
        numOfPlayer = 0;
    }
    footBall_Team(string teamName, string country, string coach)
    {
        numOfPlayer = 11;
        string fileName = "./Danh Sach Cau Thu/" + teamName + ".csv";
        this->teamName = teamName;
        this->country = country;
        this->coach = coach;
        member = new footBall_Player[numOfPlayer];
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
        fin.close();
    }
    void showInfo()
    {
        cout << "Team Name: " << teamName << endl;
        cout << "Country: " << country << endl;
        cout << "Coach: " << coach << endl;
        for (int i = 0; i < numOfPlayer; i++)
            member[i].showMemberInfo();
    }
    string getTeamName()
    {
        return teamName;
    }
    footBall_Team(footBall_Team &copy)
    {
        this->teamName = copy.teamName;
        this->country = copy.country;
        this->coach = copy.coach;
        this->numOfPlayer = copy.numOfPlayer;
        this->member = new footBall_Player[numOfPlayer];
        for (int i = 0; i < numOfPlayer; i++)
        {
            this->member[i] = copy.member[i];
        }
    }
    void addPlayer(footBall_Player player)
    {
        member[numOfPlayer] = player;
        numOfPlayer++;
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
    void showInfo()
    {
        cout << setw(20) << "\t\t" << stadum << endl;
        cout << setw(20) << "\t\t" << time << endl;
        cout << setw(10) << left << "   " << team1Name << setw(10) << right << "\t\t" << team2Name << endl;
        cout << setw(10) << left << "\t" << score1 << setw(15) << right << "\t\t   — \t\t " << score2 << endl;
    }
    string getNameTeam1()
    {
        return team1Name;
    }
    string getNameTeam2()
    {
        return team2Name;
    }
};
void showTeamInfo(footBall_Team *team, int n, string name1, string name2)
{
    for (int i = 0; i < n; i++)
    {
        if (team[i].getTeamName() == name1)
        {
            team[i].showInfo();
        }
        if (team[i].getTeamName() == name2)
        {
            team[i].showInfo();
        }
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
        string teamName, country, coach;
        getline(fin, teamName, ';');
        getline(fin, coach, ';');
        getline(fin, country, '\n');
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
void titleBar()
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
int main()
{
    system("clear");
    int numOfTeam, numOfMatch;
    footBall_Team *ListTeam = new footBall_Team[10];
    footBall_Match *ListMatch = new footBall_Match[10];
    readFile(ListTeam, numOfTeam, ListMatch, numOfMatch);
    int choice;
    titleBar();
    while (choice != 6)
    {
        cout << "1. Xem thong tin cac doi bong" << endl;
        cout << "2. Xem thong tin cac tran dau" << endl;
        cout << "3. Thong ke diem" << endl;
        cout << "4. Loc thong tin" << endl;
        cout << "5. Sap xep cac doi bong" << endl;
        cout << "6. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name1, name2;
            cout << "Enter Team 1: ";
            cin >> name1;
            cout << "Enter Team 2: ";
            cin >> name2;
            showTeamInfo(ListTeam, numOfTeam, name1, name2);
            break;
        }
        case 2:
        {
            int selection;
            for (int i = 0; i < numOfMatch; i++)
                ListMatch[i].showInfo();
            cout << "1. Xem thong tin chi tiet hai doi" << endl;
            cout << "2. Xem thong ke diem" << endl;
            cout << "3. Back to menu" << endl;
            cout << "Enter your choice: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
            {
                system("clear");
                for (int i = 0; i < numOfMatch; i++)
                    ListMatch[i].showInfo();
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                showTeamInfo(ListTeam, numOfTeam, ListMatch[choice - 1].getNameTeam1(), ListMatch[choice - 1].getNameTeam2());
                break;
            }

                {
                default:
                    break;
                }
                break;
            }
        case 3:
        {
        }

            return 0;
        }
        }
    }
}
