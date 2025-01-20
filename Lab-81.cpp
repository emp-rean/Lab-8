#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

const short N_max = 2000;

bool read(int& n, short& count, string words[N_max])
    {
        std::ifstream in("input1.txt");
        if (!in.is_open())
        {
            std::cerr << "File not found" << endl;
            return false;
        }
        in >> n;
        count = 0;
        while(!in.eof())
        {
            in >> words[count];
            count++;
        }
        return true;
    }

void clearwords(short count, string words[N_max])
{
    for(short i = 0; i < count; i++)
        for(short j = 0; j < words[i].length(); j++)
        {
            if (!isalpha (words[i][j]))
            {
                words[i].erase(j,1);
            j--;
            }
        }
}

bool isVowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

void CountDoubleVowels(short count, string words[N_max], short CDV[N_max])
{
    for(short i = 0; i < count; i++)
    {
        short doublecounter = 0;
        short len =  words[i].length();
        for(short j = 0; j < len - 1; j++)
        {
        char c = tolower(words[i][j]);
        char c2 = tolower(words[i][j+1]);
            if (isVowel(c) && isVowel(c2))
            {
                doublecounter++;
            }
            CDV[i] = doublecounter;
        }
    }

}

void Sort(short count, short CDV[N_max], string words[N_max])
{
for(short i=0;i<count-1;i++)
    for (short j=i+1;j<count;j++)
        if (CDV[i] < CDV[j])
        {
            std::swap(CDV[i], CDV[j]);
            std::swap(words[i], words[j]);
            /*short tmp =  CDV[i];
            CDV[i] = CDV[j];
            CDV[j] = tmp;
            string tmp2 = words[i];
            words[i] = words[j];
            words[j] = tmp;*/
        }
}

void write(int n, short count, string words[N_max], short CDV[N_max])
{
    bool first = true;
    string previous = "";
    for (int i=0; i<count; i++)
    {
        if (n == 0)
            break;
        n--;
        if (first)
        {
            cout << words[i] <<  " " << CDV[i] << endl;
            first = false;
            previous = words[i];
            continue;
        }

        if (words[i] != previous)
        {
            previous = words[i];
            cout << words[i] <<  " " << CDV[i] << endl;
        }
    }
}

int main()
{
    int n;
    short count;
    int doublecounter = 0;
    string words[N_max];
    short CDV[N_max];
    if (!read(n, count, words))
        return -1;
    clearwords(count, words);
    CountDoubleVowels(count, words, CDV);
    Sort(count, CDV, words);
    write(n, count, words, CDV);
    return 0;
}
