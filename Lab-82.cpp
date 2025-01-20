/* Дана строка, содержащая английский текст. Если в тексте есть слово, в котоpом есть две одинаковые гласные буквы,
то удалить из слов текста согласные, в противном случае пpодублиpовать в словах, содеpжащих не менее 3-х гласных, гласные буквы.
Полученные слова вывести в алфавитном поpядке. */
#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // Для tolower

using std::cin;
using std::cout;
using std::endl;
using std::string;

const short N_max = 2000;

bool read(int& n, short& count, string words[N_max])
{
    std::ifstream in("input2.txt");
    if (!in.is_open())
    {
        std::cerr << "File not found" << endl;
        return false;
    }
    in >> n;
    count = 0;
    while(in >> words[count]) // Проверяем успешность чтения
    {
        count++;
        if (count >= N_max) {
            break; // Добавим защиту от переполнения массива
        }
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

bool IsVowel(char a)
{
    a = tolower(a);
    return a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y';
}

bool IsConsonant(char a)
{
    a = tolower(a);
    return a == 'b' || a == 'c' || a == 'd' || a == 'f' || a == 'g' || a == 'h' || a == 'j' || a == 'k' || a == 'l' || a == 'm' || a == 'n' || a == 'p' || a == 'q' || a == 'r' || a == 's' || a == 't' || a == 'v' || a == 'w' || a == 'x' || a == 'z';
}

bool IsEqualVovels(short count, string words[N_max])
{
    for (short i = 0; i < count; i++)
    {
        short LenWord = words[i].length();
        for (short j = 0; j < LenWord; j++)
        {
            if (IsVowel(words[i][j]))
            {
                for (short k = j + 1; k < LenWord; k++)
                {
                    if (IsVowel(words[i][k]) && words[i][j] == words[i][k]) 
                    {
                        return true; 
                    }
                }
            }
        }
    }
    return false;
}

void DestroyAllConsonants (short count, string words[N_max])
{
    for(short i = 0; i < count; i++)
        for(short j = 0; j < words[i].length(); j++)
        {
            if (IsConsonant(words[i][j]))
            {
                words[i].erase(j,1);
            j--;
            }
        }
}

string DuplicateVowels(string word)
{
    string result = "";
    for (char ch : word) {
        result += ch;
        if (IsVowel(ch)) {
            result += ch;
        }
    }
    return result;
}


void LessThanThreeVowels(short count, string words[N_max])
{
    for(short i = 0; i < count; i++)
    {
        short VovelCount = 0;
        for(short j = 0; j < words[i].length(); j++)
        {
            if (IsVowel(words[i][j]))
                VovelCount++;
        }
        if (VovelCount < 3)
        {
            words[i] = DuplicateVowels(words[i]);
        }
    }
}

void write(int n, short count, string words[N_max])
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
            cout << words[i] << endl;
            first = false;
            previous = words[i];
            continue;
        }

        if (words[i] != previous)
        {
            previous = words[i];
            cout << words[i] << endl;
        }
    }
}

int main()
{
    int n;
    short count;
    string words[N_max];
    if (!read(n, count, words))
        return -1;
    clearwords(count, words);
    if (IsEqualVovels(count, words))
        DestroyAllConsonants (count, words);
    else
        LessThanThreeVowels(count, words);
    write(n, count, words);
}