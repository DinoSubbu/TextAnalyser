/**
 * @file ITextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 1.0
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include<string>

/**
 * @brief   For a given input file, the text is analysed to find out the 
                - 10 most commonly used words
                - start position of all the smileys in the text (Currently this tool supports smileys with the following pattern colon followed by an optional dash and a bracket)
            This tool can write the analysis result to the following output formats:
                - XML file
                - txt file
                - Console
            User has the full control to choose any combination of the above mentioned output formats.
 * 
 */
class ITextAnalyzer
{
    public:
        /**
         * @brief Find smiley postions from the input file
         * 
         * @param file_path 
         */
        virtual void findSmileyPositions(std::string) = 0;
        
        /**
         * @brief Find frequently used 10 words from the input file
         * 
         * @param file_path 
         */
        virtual void findTenMostUsedWords(std::string) = 0;

        /**
         * @brief Write frequent 10 words and smiley positions to the console
         * 
         */
        virtual void writeOutputToConsole() = 0;

        /**
         * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.txt
         * 
         */
        virtual void writeOutputToTextFile() = 0;

        /**
         * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.xml
         * 
         */
        virtual void writeOutputToXMLFile() = 0;
};