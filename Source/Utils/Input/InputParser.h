//
// Created by Jury Verrigni on 13/07/2017.
// https://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//

#ifndef WATERBOT_INPUTPARSER_H
#define WATERBOT_INPUTPARSER_H

#include <string>
#include <vector>

class InputParser{
    public:
        InputParser (int &ArgC, char **ArgV){
            for (int i=1; i < ArgC; ++i)
                this->Tokens.push_back(std::string(ArgV[i]));
        }

        const std::string& GetArgumentAsString(const std::string &Argument) const{
            std::vector<std::string>::const_iterator Iterator;
            Iterator =  std::find(this->Tokens.begin(), this->Tokens.end(), Argument);
            if (Iterator != this->Tokens.end() && ++Iterator != this->Tokens.end()){
                return *Iterator;
            }
            static const std::string EmptyString("");
            return EmptyString;
        }

        bool ArgumentExists(const std::string &Argument) const{
            return std::find(this->Tokens.begin(), this->Tokens.end(), Argument)
                   != this->Tokens.end();
        }
    private:
        std::vector <std::string> Tokens;
};
#endif //WATERBOT_INPUTPARSER_H
