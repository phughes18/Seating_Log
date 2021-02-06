//Angie lab 4
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

void openFile(ifstream &inf, string &fname, vector<string> &Vec)
{
    cout << "Enter file name to open: ";
    cin >> fname;
    inf.open(fname);
    if (inf.fail())
    {
        cout << "File open failed" << endl;
        exit(1);
    }

    int i=0, lineN=1;
    string line;
    while(getline(inf, line))
    {
        Vec.push_back(line);
        cout << '[' << lineN << "] ";
        if(lineN<10)
            cout << ' ';
        cout << Vec[i] << endl;
        i++;
        lineN++;
    }
    return;
}

void opentoWrite(ofstream &out, string fname)

{
    out.open(fname);
    if (out.fail())
    {
        cout << "File open failed" << endl;
        exit(1);
    }

}


void printInfo(vector<string> &Vec)
{
    int total=0, open=0, strL = Vec[0].length();
    int lineN=1;

    for(unsigned int i=0; i<Vec.size(); i++)
    {
        cout << '[' << lineN << "] ";
        if(lineN<10)
            cout << ' ';
        lineN++;

        for(int j=0; j<strL; j++)
        {
            cout << Vec[i][j];
            if(isalpha(Vec[i][j]))
            { 
                open++;
                total++;
                if(Vec[i][j]=='X')
                    open--;
            }
        }
        cout << endl;
    }
    cout << "Total seats: " << total << endl;
    cout << "Number open: " << open << endl;
    
    return;
}


void getSeat(vector<string> &Vec)
{
    int r, row, seat = 0;
    char s;
    cout << "Enter the row number followed by the seat letter: ";
    cin >> r >> s;
    row = r -1;

    for(unsigned int i=0; i<Vec[0].length(); i++)
    {
        if(Vec[row][i]== s)
            break;
        else
            seat++;
    }
    cout << Vec[row][seat];

    if(isalpha(Vec[row][seat]))
    {
        Vec[row][seat] = 'X';
        cout << "Seat "<< r << s << " has been booked." << endl;
    }
    else if(Vec[row][seat] == 'X')
        cout << "Seat "<< r << s << " is taken. " << endl;
    else
        cout << "Not valid. ";
    return;
}

void saveto(ofstream &out, vector<string> &Vec)
{
    int strL = Vec[0].length();
    for(unsigned int i=0; i<Vec.size(); i++)
    {
        for(int j=0; j<strL; j++)
        {
            out << Vec[i][j];
        }
    out << endl;
    }
}


int main()
{
    ifstream infile;
    ofstream outfile;
    string fname;
    vector<string> Vec;
    char again = 'n';

    openFile(infile, fname, Vec);
    opentoWrite(outfile, fname);
    do
    {
        char menu;
        cout <<"- Show seating [s]" << endl
        <<"- Book a seat  [b]" << endl
        <<"- Quit         [q]";
        cin >> menu;

        switch (menu)
        {
         case 's':
             printInfo(Vec);
             break;
         case 'b':
             getSeat(Vec);
             printInfo(Vec);
             break;
         case 'q':
             break;
        }
        if(menu != 'q')
        {
            cout << "Do again? [y]es/[n]o " << endl;
            cin >> again;
        }
    }while(again!='n');

    saveto(outfile, Vec);

    infile.close();
    outfile.close();
    return 0;
}

