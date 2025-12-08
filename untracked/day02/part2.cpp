#include <iostream>
#include <cstring>
#include <fstream>
//#define input "test.txt"
#define input "input.txt"
#define output "output.txt"
using namespace std;

size_t result = 0;

class Game{
    public:
        int red;
        int green;
        int blue;

        Game(int red = 0, int green = 0, int blue = 0){
            this->red = red;
            this->green = green;
            this->blue = blue;
        }

        size_t power(){
            return this->red * this->green * this->blue;
        }
};

int max(int a, int b){
    return (a>=b) ? a : b;
}

Game fewest(string analyze){
    Game game;

    while(!analyze.empty()){
        int number = stoi(analyze);
        switch(analyze[analyze.find(' ')+1]){
            case 'r':
                game.red = max(game.red, number);
                break;
            case 'b':
                game.blue = max(game.blue, number);
                break;
            case 'g':
                game.green = max(game.green, number);
                break;
        }

        size_t pos = min(analyze.find(','), analyze.find(';'));
        if(pos != string::npos)
            analyze = analyze.substr(pos+2);
        else
            break;
    }

    return game;
}

int main(){

    fstream fin, fout;
    fin.open(input, ios::in);
    fout.open(output, ios::out);
    
    string line;

    while(getline(fin, line)){
        if(line.empty()) continue;

        result += fewest(line.substr(line.find(':')+2)).power();
    }

    cout << result << endl;
    fout << result;

    fin.close();
    fout.close();

    return 0;
}
