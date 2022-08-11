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
        void findSmileyPositions(const std::string&) override;
        void findTenMostUsedWords(const std::string&) override;
        void writeOutputToConsole() override;
        void writeOutputToTextFile() override;
        void writeOutputToXMLFile() override;

    private:
        void read_string_from_file(const std::string&, std::string&) const;
        void removeExtraSpaces(std::string& input_text) const;
        void convertToLowerCase(std::string& input_text) const;
        void removePunctuations(std::string& input_text) const;
        void processInput(std::string& input_text);
        void tokenize(const std::string& input_text);

        std::vector<std::string> wordsVec{};
        std::stringstream smileyPositions{};
        std::stringstream frequentTenWords{};
        std::vector<std::string> wordsVector{};
        std::multimap<std::string, int> smileysWithPosition{};
        
};