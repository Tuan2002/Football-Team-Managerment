#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
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
        numOfPlayer = 11;
        point = 0;
        winMatch = 0;
        loseMatch = 0;
        drawMatch = 0;
        string fileName = "./Danh Sach Cau Thu/" + teamName + ".csv";
        // Ten file vi du "Song Lam Nghe Anh.csv"
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
        cout << "| " << left << setw(25) << teamName << "| " << setw(20) << coach << "| " << setw(14) << country << " |" << endl;
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
        {
            member[i].showMemberInfo();
        }
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
    void showMatchInfo()
    {
        cout << "| " << left << setw(20) << stadum;
        cout << "| " << left << setw(11) << time;
        cout << "| " << left << setw(20) << team1Name;
        cout << "| " << left << setw(5) << score1 << " - " << right << setw(5) << score2;
        cout << " | " << left << setw(20) << team2Name;
        cout << "|" << endl;

        // cout << setw(20) << "\t\t" << stadum << endl;
        // cout << setw(20) << "\t\t" << time << endl;
        // cout << setw(10) << left << "   " << team1Name << setw(10) << right << "\t\t" << team2Name << endl;
        // cout << setw(10) << left << "\t" << score1 << setw(15) << right << "\t\t   — \t\t " << score2 << endl;
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
    switch (choice)
    {
    case 1:
        string country;
        cout << "Nhap dia phuong can loc: ";
        fflush(stdin);
        getline(cin, country);
        for (int i = 0; i < n; i++)
        {
            if (team[i].getCountry() == country)
            {
                FIL_ARRAY[count] = i;
                count++;
            }
        }
        system("cls");
        cout << "Co (" << count << ") doi bong thuoc dia phuong: " << country << endl;
        for (int i = 0; i < count; i++)
        {
            team[FIL_ARRAY[i]].showDetail();
        }
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
    system("cls");
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
// Xem Thong tin cua 2 doi trong 1 tran dau
void showTeamInfo(footBall_Team *team, int n, string name1, string name2)
{
    system("cls");
    cout << "Thong tin doi thu nhat: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name1)
            team[i].showDetail();
    cout << "Bam phim bat ki de tiep tuc xem... ";
    fflush(stdin);
    getchar();
    system("cls");
    cout << "Thong tin doi thu hai: " << endl;
    for (int i = 0; i < n; i++)
        if (team[i].getTeamName() == name2)
            team[i].showDetail();
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
int main()
{
    system("cls");
    int numOfTeam, numOfMatch;
    footBall_Team *ListTeam = new footBall_Team[20];
    footBall_Match *ListMatch = new footBall_Match[20];
    readFile(ListTeam, numOfTeam, ListMatch, numOfMatch);
    calcPoint(ListMatch, numOfMatch, ListTeam, numOfTeam);
    int choice;
    titleBox();
    while (choice != 6)
    {
        cout << "1. Xem thong tin cac doi bong" << endl;
        cout << "2. Xem thong tin cac tran dau" << endl;
        cout << "3. Thong ke diem" << endl;
        cout << "4. Loc thong tin" << endl;
        cout << "5. Chinh sua du lieu" << endl;
        cout << "6. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            string border = "+--------------------------+---------------------+----------------+";
            cout << border << endl;
            cout << "| " << left << setw(25) << "TEN DOI"
                 << "| " << setw(20) << "HUAN LUYEN VIEN"
                 << "| " << setw(14) << "DIA PHUONG"
                 << " |" << endl;
            cout << border << endl;
            for (int i = 0; i < numOfTeam; i++)
            {
                ListTeam[i].showInfo();
            }
            cout << border << endl;
            int select;
            cout << "Chon doi bong can xem thong tin chi tiet: ";
            cin >> select;
            system("cls");
            ListTeam[select - 1].showDetail();
            cout << "Bam phim bat ki de tro ve menu chinh... ";
            fflush(stdin);
            getchar();
            system("cls");
            titleBox();
            break;
        }
        case 2:
        {
            int selection;
            system("cls");
            scoreBoard(ListMatch, numOfMatch);
            cout << "1. Xem thong tin chi tiet hai doi" << endl;
            cout << "2. Xem thong ke diem cua hai doi" << endl;
            cout << "3. Tro ve menu" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
            {
                system("cls");
                scoreBoard(ListMatch, numOfMatch);
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                showTeamInfo(ListTeam, numOfTeam, ListMatch[choice - 1].getNameTeam1(), ListMatch[choice - 1].getNameTeam2());
                cout << "Bam phim bat ki de tro ve menu chinh... ";
                fflush(stdin);
                getchar();
                system("cls");
                titleBox();
                break;
            }
            case 2:
            {
                system("cls");
                scoreBoard(ListMatch, numOfMatch);
                cout << "Chon tran dau: ";
                int choice;
                cin >> choice;
                system("cls");
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
                fflush(stdin);
                getchar();
                system("cls");
                titleBox();
                break;
            }
            case 3:
            {
                system("cls");
                titleBox();
                break;
            }
            }
            break;
        }
        case 3:
        {
            system("cls");
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
            cout << "Bam phim bat ki de tro ve menu chinh... ";
            fflush(stdin);
            getchar();
            system("cls");
            titleBox();
            break;
        }
        case 4:
        {
            system("cls");
            filTer(ListTeam, numOfTeam);
            cout << "Bam phim bat ki de tro ve menu chinh... ";
            fflush(stdin);
            getchar();
            system("cls");
            titleBox();
            break;
        }
        case 5:
        {
            system("cls");
            int selection;
            cout << "1. Them doi bong tu danh sach cho" << endl;
            cout << "2. Them tran dau" << endl;
            cout << "3. Xoa doi bong" << endl;
            cout << "4. Xoa tran dau" << endl;
            cout << "Nhap lua chon: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
                addTeam(ListTeam, numOfTeam);
                cout << "Bam phim bat ki de tro ve menu chinh... ";
                fflush(stdin);
                getchar();
                system("cls");
                titleBox();
                break;
            }
        }
        }
    }
    return 0;
}
