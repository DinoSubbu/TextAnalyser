#include "TextAnalyzer.hpp"
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <regex>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#define COUNT_MAX_USED_WORDS 10
namespace pt = boost::property_tree;

std::string read_string_from_file(std::string file_path) {
    const std::ifstream input_stream(file_path, std::ios_base::binary);

    if (input_stream.fail()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    return buffer.str();
}

void TextAnalyzer::findSmileyPositions(std::string file_path)
{
    std::regex smileyPattern(":\\(|:\\)|:-\\]|:-\\[|:\\]|:\\[|:-\\(|:-\\)");
    std::string input_text =read_string_from_file(file_path);
    smileyPositions << "Smileys and their positions :\n";

    for(auto i = std::sregex_iterator(input_text.begin(), input_text.end(), smileyPattern);
           i != std::sregex_iterator();
           ++i)
    {
        std::smatch m = *i;
        if (m[0].matched) {  
            smileyPositions<< m[0].str() << " --> " << m.position(0) << std::endl;
        }
    }
}

void TextAnalyzer::findTenMostUsedWords(std::string file_path)
{
    std::string input_text =read_string_from_file(file_path);
    processInput(input_text);

    std::unordered_map<std::string, int> frequency;
    for (std::string &word: wordsVec) {
        ++frequency[word];
    }

    auto comp = [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);  
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(comp)> wordFreq (comp);

    for (const auto &[word, freq]: frequency) {
        wordFreq.push({word, freq});
        if (wordFreq.size() > COUNT_MAX_USED_WORDS) wordFreq.pop();
    }

    while(!wordFreq.empty()) {
        wordsVector.push_back(wordFreq.top().first);
        wordFreq.pop();
    }
    reverse(wordsVector.begin(), wordsVector.end());

    frequentTenWords << "Most frequent 10 words :\n";
    int i=1;
    for(auto &word: wordsVector){
        frequentTenWords<< i << "." << word<<std::endl;
        ++i;
    }
}

void TextAnalyzer::writeOutputToConsole()
{
    std::cout << smileyPositions.str();
    std::cout << frequentTenWords.str();
}

void TextAnalyzer::writeOutputToTextFile()
{
    std::ofstream outFile;
    outFile.open("TextAnalyzerOutput.txt");
    outFile << smileyPositions.str() << frequentTenWords.str();
}

void TextAnalyzer::writeOutputToXMLFile()
{
    pt::ptree tree;
    int i = 1;
    for(auto &word: wordsVector){
        std::string temp{"TextAnalyzer.Frequent10Words."};
        temp = temp + std::to_string(i);
        tree.add(temp, word);
        ++i;
    }
    pt::write_xml("TextAnalyzerOutput.xml", tree);
}

// Removes extra spaces from input string and returns updated string
void TextAnalyzer::removeExtraSpaces(std::string& input_text) {
    auto new_end_position = std::unique(input_text.begin(), input_text.end(), [] (char left, char right) {
        return ((left == right) && (left == ' '));
    });
    input_text.erase(new_end_position, input_text.end());
    while (input_text[0] == ' ') {
        input_text.erase(0,1);
    }
}


// Converts upper case alphabets to lower case and returns updated string
void TextAnalyzer::convertToLowerCase(std::string& input_text) {
    std::for_each(input_text.begin(), input_text.end(), [] (char& alphabet) {
        alphabet = std::tolower(alphabet);
    });
}


// Breaks down the input string into words and returns a vector of words
// Reserved for future use
void TextAnalyzer::tokenize(std::string input_text) {
    std::string word = "";
    for(auto alphabet: input_text) {
        if(alphabet == ' ') {
            if(word!="") {
            wordsVec.emplace_back(word);
            word = "";
            }
        }
        else {
            word += alphabet;
        }
    }
    if(word!="")
        wordsVec.emplace_back(word);
}

// Removes punctuation marks from input string and returns updated string
void TextAnalyzer::removePunctuations(std::string& input_text) {
    auto new_end_position = std::remove_if(input_text.begin(), input_text.end(), ispunct);
    input_text.erase(new_end_position, input_text.end());
}


// Processes input string by removing uppercases, punctuations & extra spaces
void TextAnalyzer::processInput(std::string& input_text) {
    removePunctuations(input_text);
    convertToLowerCase(input_text);
    removeExtraSpaces(input_text);
    tokenize(input_text);
}