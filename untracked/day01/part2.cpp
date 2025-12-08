#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#define input "input.txt"
//#define input "test.txt"
#define output "output2.txt"
#define MAX_LEN 50
#define TOT_NUM 9
using namespace std;

string numbers[TOT_NUM] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};
unsigned long sum = 0;

int main(){
    fstream fout;
    fstream fin;

#define input "test.txt"
    fin.open(input, ios::in);
    fout.open(output, ios::out);

    if(!fout.is_open() || !fin.is_open()){
        cout << "Couldn't open files correctly.\n";
        return -1;
    }

    string line;

    while(!fin.eof()){
        getline(fin, line);

        if(line.empty()) continue;

        short first = -1;
        short last = -1;

        for(string::iterator it = line.begin(); it != line.end(); ++it){

            // first check if it's a number
            if(*it >= '0' && *it <= '9'){
                short num = *it - '0';

                if(first == -1) {
                    first = num;
                    last = num;
                } else {
                    last = num;
                }
            }

            // if not a number then check for written numbers
            for(int i = 0; i < TOT_NUM; i++){
                string number = numbers[i];
                bool uguale = true;

                string::iterator a = it, b = number.begin();
                for(; uguale && a != line.end() && b != number.end(); ++a, ++b){
                    if(*a != *b)
                        uguale = false;
                }

                if(b == number.end() && uguale){
                    if(first == -1) {
                        first = i+1;
                        last = i+1;
                    } else {
                        last = i+1;
                    }

                    break;
                }
            }

        }

        sum += (first * 10) + last;
    }

    fout << sum;
    cout << sum << endl;

    fin.close();
    fout.close();

    return 0;
}
