#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdarg>
#define test_input "test.txt"
#define input "input.txt"
#define output "output.txt"

class Answers{
    public:
        std::string first;
        size_t second;

        /*
        void print(char const* data = "", ...){
            std::cout << this->first << this-> second << std::endl;
            
            if(std::strcmp(data, "") != 0){
                std::ofstream out;
                out.open(data);
                out << this->first << this->second << std::endl;
                out.close();
            }
        }
        */
};

class Number{
public:
    size_t start;
    size_t end;
    int value;
};

using Text = std::vector<std::string>;
using List = std::vector<std::vector<Number>>;

// stores input in a vector made of input's lines
Text parse(char const *data){
    Text doc;
    std::fstream in;
    in.open(data, std::ios::in);
    std::string line;
    while(std::getline(in, line)){
        doc.push_back(line);
    }
    in.close();
    return doc;
}

// stores all the numbers from the input in a vector with position information
List list_numbers(Text doc){
    List list;

    for(long unsigned int row=0; row < doc.size(); ++row){
        std::vector<Number> line;

        for(long unsigned int col=0; col < doc[row].size(); ++col){
            if(std::isdigit(doc[row][col])){
                size_t end;
                int value = std::stoi(doc[row].substr(col), &end);
                line.push_back({col, end, value});
                col = end;
            }
        }

        list.push_back(line);
    }
    return list;
}

size_t sum_part_numbers(Text doc, List list){
    size_t result = 0;

    auto isspecial = [&doc](size_t row, size_t col){
        if(row < 0 || col < 0)
            return false;
        if(row >= doc.size() || col >= doc.at(row).size())
            return false;
        return !(std::isdigit(doc[row][col]) && doc[row][col] != '.');
    };

    for(long unsigned int row = 0; row < list.size(); ++row){
        for(long unsigned int i = 0; i < list.at(row).size(); ++i){
            bool to_sum = false;
            for(long unsigned int j = row-1; j <= row+1 && !to_sum; ++j){
                for(long unsigned int range = list[row][i].start - 1; range <= list[row][i].start + 1 && !to_sum; range++){
                    to_sum = isspecial(range, j);
                }
            }
            if(to_sum)
                result += list[row][i].value;
        }
    }

    return result;
}

namespace part1{
    size_t solve(char const *data){
        Text doc = parse(data);
        List list = list_numbers(doc);
        return sum_part_numbers(doc, list);
    }
}

int main(){

    std::vector<Answers> answers;
    answers.push_back({"Result part 1 test: ", part1::solve(test_input)});
    answers.push_back({"Result part 1     : ", part1::solve(input)});

    std::ofstream out;
    out.open(output);

    for(Answers an : answers){
        std::cout << an.first << an.second << std::endl;
        out << an.first << an.second << std::endl;
    }

    return 0;
}
