#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#define input "input.txt"
#define output "output1.txt"
#define MAX_LEN 50
using namespace std;

unsigned long sum = 0;

int main(){
    fstream fout;
    fstream fin;

    fout.open(output, ios::out);
    fin.open(input, ios::in);

    if(!fout.is_open()){
        cout << "couldn't open output file." << endl;
        return -1;
    }
    if(!fin.is_open()){
        cout << "couldn't open input file." << endl;
        return -1;
    }

    string line;
    while(!fin.eof()){
        getline(fin, line);

        if(line.empty()) continue;

        short first = -1;
        short last = -1;

        for(unsigned i=0; i<=line.size(); i++){
            if(line[i] <= '9' && line[i] >= '0'){
                short num = line[i] - '0';

                if(first == -1) {
                    first = num;
                    last = num;
                } else {
                    last = num;
                }
            }
        }

        sum += (first * 10) + last;
    }

    fout << sum;
    cout << endl << "Result: " << sum << endl;

    fin.close();
    fout.close();

    return 0;
}
