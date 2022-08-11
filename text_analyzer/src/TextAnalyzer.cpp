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

/**
 * @brief read the input file from the path specified and push the content to a string variable
 * 
 * @param file_path 
 */
void TextAnalyzer::read_string_from_file(const std::string& file_path, std::string& outputString) const {
    const std::ifstream input_stream(file_path, std::ios_base::binary);

    if (input_stream.fail()) {
        std::cout<<"Please check the input file. Exiting with an exception"<<std::endl;
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    outputString = buffer.str();
}

/**
 * @brief Find smiley postions from the input file
 * 
 * @param file_path 
 */
void TextAnalyzer::findSmileyPositions(const std::string& file_path)
{
    std::regex smileyRegexPattern(":\\(|:\\)|:-\\]|:-\\[|:\\]|:\\[|:-\\(|:-\\)");
    std::string input_text{};
    read_string_from_file(file_path, input_text);
    smileyPositions << "Smileys and their positions :\n";

    for(auto i = std::sregex_iterator(input_text.begin(), input_text.end(), smileyRegexPattern);
           i != std::sregex_iterator();
           ++i)
    {
        std::smatch m = *i;
        if (m[0].matched) {  
            smileyPositions<< m[0].str() << " --> " << m.position(0) << std::endl;
            smileysWithPosition.emplace(m[0].str(), m.position(0));
        }
    }
}

/**
 * @brief Find frequently used 10 words from the input file
 * 
 * @param file_path 
 */
void TextAnalyzer::findTenMostUsedWords(const std::string& file_path)
{
    std::string input_text{};
    read_string_from_file(file_path, input_text);
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

/**
 * @brief Write frequent 10 words and smiley positions to the console
 * 
 */
void TextAnalyzer::writeOutputToConsole()
{
    std::cout << smileyPositions.str();
    std::cout << frequentTenWords.str();
}

/**
 * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.txt
 * 
 */
void TextAnalyzer::writeOutputToTextFile()
{
    std::ofstream outFile;
    outFile.open("TextAnalyzerOutput.txt");
    outFile << smileyPositions.str() << frequentTenWords.str();
    outFile.close();
}

/**
 * @brief Write frequent 10 words and smiley positions to TextAnalyzerOutput.xml
 * 
 */
void TextAnalyzer::writeOutputToXMLFile()
{
    pt::ptree tree;
    int i = 1;
    for(auto &word: wordsVector){
        std::string tagToAdd{"TextAnalyzer.Frequent10Words."};
        tagToAdd = tagToAdd + std::to_string(i);
        tree.add(tagToAdd, word);
        ++i;
    }
    for(const auto &smileyWithPosition: smileysWithPosition){
        std::string tag{"TextAnalyzer.SmileyPosition."};
        tag = tag + smileyWithPosition.first;
        auto existingValue = tree.get_optional<std::string>(tag);
        if (existingValue.has_value())
        {
            std::string valueToInsert{existingValue.value()};
            valueToInsert.append(", " + std::to_string(smileyWithPosition.second));
            tree.put(tag, valueToInsert);
        }
        else
        {
            tree.add(tag, std::to_string(smileyWithPosition.second));
        }
    }
    pt::xml_writer_settings<std::string> settings('\t', 1);
    pt::write_xml("TextAnalyzerOutput.xml", tree, std::locale(), settings);
}

/**
 * @brief Remove extra spaces from input string and return updated string
 * 
 * @param input_text 
 */
void TextAnalyzer::removeExtraSpaces(std::string& input_text) const {
    auto new_end_position = std::unique(input_text.begin(), input_text.end(), [] (char left, char right) {
        return ((left == right) && (left == ' '));
    });
    input_text.erase(new_end_position, input_text.end());
    while (input_text[0] == ' ') {
        input_text.erase(0,1);
    }
}


/**
 * @brief Convert upper case alphabets to lower case and return updated string
 * 
 * @param input_text 
 */
void TextAnalyzer::convertToLowerCase(std::string& input_text) const {
    std::for_each(input_text.begin(), input_text.end(), [] (char& alphabet) {
        alphabet = std::tolower(alphabet);
    });
}


/**
 * @brief Break down the input string into words and store it into a vector of words
 * 
 * @param input_text 
 */
void TextAnalyzer::tokenize(const std::string& input_text) {
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

/**
 * @brief remove punctuation marks from input string and return updated string
 * 
 * @param input_text 
 */
void TextAnalyzer::removePunctuations(std::string& input_text) const {
    auto new_end_position = std::remove_if(input_text.begin(), input_text.end(), ispunct);
    input_text.erase(new_end_position, input_text.end());
}


/**
 * @brief Process input string by removing uppercases, punctuations & extra spaces & tokenize to words
 * 
 * @param input_text 
 */
void TextAnalyzer::processInput(std::string& input_text) {
    removePunctuations(input_text);
    convertToLowerCase(input_text);
    removeExtraSpaces(input_text);
    tokenize(input_text);
}