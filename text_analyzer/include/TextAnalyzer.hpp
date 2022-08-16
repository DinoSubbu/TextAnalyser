/**
 * @file    TextAnalyzer.hpp
 * @author  Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief   For a given input file, the text is analysed to find out the
                - 10 most commonly used words
                - start position of all the smileys in the text (Currently this tool supports smileys with the following pattern colon followed by an optional dash and a bracket)
            This tool can write the analysis result to the following output formats:
                - XML file
                - txt file
                - Console
            User has the full control to choose any combination of the above mentioned output formats.
 * @version 1.0
 * @date    2022-08-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ITextAnalyzer.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>
#include <map>

namespace pt = boost::property_tree;

class TextAnalyzer : public ITextAnalyzer
{
public:
    /**
     * @brief Find smiley postions from the input file
     *
     * @param file_path
     */
    void findSmileyPositions(const std::string &) override;

    /**
     * @brief Find frequently used 10 words from the input file
     *
     * @param file_path
     */
    void findTenMostUsedWords(const std::string &) override;

    /**
     * @brief Write frequent 10 words and smiley positions to the console
     *
     */
    void writeOutputToConsole() override;

    /**
     * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.txt
     *
     */
    void writeOutputToTextFile() override;

    /**
     * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.xml
     *
     */
    void writeOutputToXMLFile() override;

private:
    /**
     * @brief read the input file from the path specified and push the content to a string variable
     *
     * @param file_path
     */
    void read_string_from_file(const std::string &, std::string &) const;

    /**
     * @brief Remove extra spaces from input string and return updated string
     *
     * @param input_text
     */
    void removeExtraSpaces(std::string &input_text) const;

    /**
     * @brief Convert upper case alphabets to lower case and return updated string
     *
     * @param input_text
     */
    void convertToLowerCase(std::string &input_text) const;

    /**
     * @brief remove punctuation marks from input string and return updated string
     *
     * @param input_text
     */
    void removePunctuations(std::string &input_text) const;

    /**
     * @brief Process input string by removing uppercases, punctuations & extra spaces & tokenize to words
     *
     * @param input_text
     */
    void processInput(std::string &input_text);

    /**
     * @brief Break down the input string into words and store it into a vector of words
     *
     * @param input_text
     */
    void tokenize(const std::string &input_text);

    /**
     * @brief Insert frequently used 10 words to the xml tree
     *
     * @param input_text
     */
    void writeFrequentTenWordsToXml(pt::ptree &tree) const;

    /**
     * @brief Insert Smiley and their postion to the xml tree
     *
     * @param input_text
     */
    void writeSmileyPositionsToXml(pt::ptree &tree) const;

    /**
     * @brief Filter top 10 most frequent words from the word frequency map
     *
     * @param input_text
     */
    void filterTenEntriesFromFrequencyMap(std::unordered_map<std::string, int> &freqMap);

    std::vector<std::string> wordsVec{};
    std::stringstream smileyPositionsStream{};
    std::stringstream frequentWordsStream{};
    std::vector<std::string> wordsVector{};
    std::multimap<std::string, int> smileysWithPosition{};
};