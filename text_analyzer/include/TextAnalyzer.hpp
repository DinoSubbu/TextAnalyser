/**
 * @file TextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 0.1
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

/**
 * @brief TODO
 * 
 */
class TextAnalyzer : public ITextAnalyzer
{
    public:
        /**
         * @brief 
         * 
         */
        void findSmileyPositions(std::string) override;
        
        /**
         * @brief 
         * 
         */
        void findTenMostUsedWords(std::string) override;

        void writeOutputToConsole();
        void writeOutputToTextFile();
        void writeOutputToXMLFile();
    private:
        /**
         * @brief 
         * 
         * @param input_text 
         */
        void removeExtraSpaces(std::string& input_text);
        void convertToLowerCase(std::string& input_text);
        void removePunctuations(std::string& input_text);
        void processInput(std::string& input_text);
        void tokenize(std::string input_text);

        std::vector<std::string> wordsVec{};
        std::stringstream smileyPositions{};
        std::stringstream frequentTenWords{};
        std::vector<std::string> wordsVector{};
        
};