#include <iostream>
#include <fstream>
#include <cstring>
//#define input "test.txt"
#define input "input.txt"
#define output "output.txt"
#define GAME_NUM 5
using namespace std;

class Game {
    public:
        int red;
        int green;
        int blue;

        Game(int red = 0, int green = 0, int blue = 0){
            this->red = red;
            this->green = green;
            this->blue = blue;
        }
};

size_t min(size_t a, size_t b){
    return (a<=b) ? a : b;
}

Game perfect = { 12, 13, 14 };

bool is_possible(string analyze){
    int number = stoi(analyze);
    bool possibile = true;
    switch(analyze[analyze.find(' ')+1]){
        case 'r':
            possibile = number <= perfect.red;
            break;
        case 'b':
            possibile = number <= perfect.blue;
            break;
        case 'g':
            possibile = number <= perfect.green;
            break;
        default:
            possibile = false;
            break;
    }

    size_t next = min(analyze.find(','), analyze.find(';'));
    if(next != string::npos)
        return possibile && is_possible(analyze.substr(next+2));
    else
        return possibile;
}

unsigned long count = 0;

int main(){

    fstream fin;
    fstream fout;

    fin.open(input, ios::in);
    fout.open(output, ios::out);

    string line;

    while(getline(fin, line)){
        if(line.empty()) continue;

        unsigned game_number = stoi(line.substr(line.find(' ')));

        line = line.substr(line.find(':')+2);
        if(is_possible(line))
            count += game_number;
    }

    fout << count;
    cout << count << endl;

    fout.close();
    fin.close();

    return 0;
}
