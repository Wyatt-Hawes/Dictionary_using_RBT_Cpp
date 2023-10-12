#include"Dictionary.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

#define MAX_LEN 300
int main(int argc, char* argv[]){
    
    if (argc != 3){
        fprintf(stderr, "Please enter 2 arguments.\n Ex: Lex <input file> <output file>\n");
        return 1;
    }
    std::ifstream input;
    input.open(argv[1]);

    std::ofstream output;
    output.open(argv[2]);

    std::string key;
    //int i = 1;
    Dictionary d;

    std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";


    int token_count, line_count;
    size_t begin, end, len;
    std::string line;
    std::string tokenBuffer;
    std::string token;

    line_count = 0;
    while( getline(input, line) )  {
      line_count++;
      len = line.length();
      
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = std::min(line.find_first_not_of(delim, 0), len);
      end   = std::min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
         //tokenBuffer += "   "+token+"\n";
         token_count++;
            for(size_t v = 0; v < token.length(); v++){
                token[v] = tolower(token[v]);
            }
            try{
                int& currVal = (d.getValue(token));
                 //std::cout << "new val\n";
                 currVal++; 
            }catch(std::invalid_argument const &){
                //std::cout << "new val\n";
                d.setValue(token, 1);
            }
        
         // get next token
         begin = std::min(line.find_first_not_of(delim, end+1), len);
         end   = std::min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
       }

      
      //output << tokenBuffer;
    }

    output << d;
    output << "\n";
    return 0;
}