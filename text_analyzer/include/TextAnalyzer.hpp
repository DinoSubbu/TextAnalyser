/**
 * @file TextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 1.0
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "ITextAnalyzer.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <map>

class TextAnalyzer : public ITextAnalyzer
{
    public:
        void findSmileyPositions(std::string) override;
        void findTenMostUsedWords(std::string) override;
        void writeOutputToConsole();
        void writeOutputToTextFile();
        void writeOutputToXMLFile();

    private:
        void removeExtraSpaces(std::string& input_text);
        void convertToLowerCase(std::string& input_text);
        void removePunctuations(std::string& input_text);
        void processInput(std::string& input_text);
        void tokenize(std::string input_text);

        std::vector<std::string> wordsVec{};
        std::stringstream smileyPositions{};
        std::stringstream frequentTenWords{};
        std::vector<std::string> wordsVector{};
        std::multimap<std::string, int> smileysWithPosition{};
        
};