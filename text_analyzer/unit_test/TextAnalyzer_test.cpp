#include <gtest/gtest.h>
#include "TextAnalyzer.hpp"
#include <fstream>

std::string CWD = "/home/dino/Documents/Job/CodingTask/BMW/text_analyzer/unit_test/test_data/";

bool compareOutput(std::string actualResultPath,std::string expectedOutput)
{
	std::string actualOutputString;
	std::string buffer;
	std::ifstream of(actualResultPath);
	while (std::getline(of, buffer))
    	actualOutputString += (buffer + '\n');
	if(actualOutputString.compare(expectedOutput) == 0)
		return true;
	return false;
}

const std::string outputTxtFilePath = ".//TextAnalyzerOutput.txt";

TEST(TextAnalyzerTests, InputFileWithLessThan10Words) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\n:) --> 22\nMost frequent 10 words :\n1.cxx\n2.executable\n3.linking\n"};
	std::string inputFilePath = CWD + "InputFileWithLessThan10Words.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithMoreThan10Words) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\n:) --> 22\n:) --> 47\n:) --> 72\n:) --> 97\nMost frequent 10 words :\n1.cxx\n2.executable\n3.linking\n"};
	std::string inputFilePath = CWD + "InputFileWithMoreThan10Words.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, EmptyInputFile) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\nMost frequent 10 words :\n"};
    std::string inputFilePath = CWD + "EmptyInputFile.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithOnlyText) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\nMost frequent 10 words :\n1.linking\n2.cxx\n3.executable\n"};
    std::string inputFilePath = CWD + "InputFileWithOnlyText.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithOnlySmileys) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\n:) --> 0\n:-[ --> 2\n:( --> 6\nMost frequent 10 words :\n"};
    std::string inputFilePath = CWD + "InputFileWithOnlySmileys.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithUnsupportedSmileys) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\n:) --> 5\n:-) --> 12\nMost frequent 10 words :\n"};
    std::string inputFilePath = CWD + "InputFileWithUnsupportedSmileys.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithPunctuations) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\nMost frequent 10 words :\n1.cxx\n2.executable\n3.linking\n4.running\n"};
    std::string inputFilePath = CWD + "InputFileWithPunctuations.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithExtraSpaces) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"Smileys and their positions :\nMost frequent 10 words :\n1.cxx\n2.executable\n3.linking\n"};
    std::string inputFilePath = CWD + "InputFileWithExtraSpaces.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToTextFile();
	ASSERT_TRUE(compareOutput(outputTxtFilePath, expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithExtraSpaces_writeToXML) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<TextAnalyzer>\n	<Frequent10Words>\n		<1>cxx</1>\n		<2>executable</2>\n		<3>linking</3>\n	</Frequent10Words>\n</TextAnalyzer>\n"};
    std::string inputFilePath = CWD + "InputFileWithExtraSpaces.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToXMLFile();
	ASSERT_TRUE(compareOutput(".//TextAnalyzerOutput.xml", expectedOutput));
}

TEST(TextAnalyzerTests, InputFileWithRepeatedSmileys_writeToXML) {
	TextAnalyzer textAnalyzer{};
	const std::string expectedOutput = {"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<TextAnalyzer>\n	<SmileyPosition>\n		<:(>6, 9</:(>\n		<:)>0</:)>\n		<:-[>2</:-[>\n	</SmileyPosition>\n</TextAnalyzer>\n"};
    std::string inputFilePath = CWD + "InputFileWithRepeatedSmileys.txt";
    textAnalyzer.findTenMostUsedWords(inputFilePath);
	textAnalyzer.findSmileyPositions(inputFilePath);
	textAnalyzer.writeOutputToXMLFile();
	ASSERT_TRUE(compareOutput(".//TextAnalyzerOutput.xml", expectedOutput));
}

TEST(TextAnalyzerTests, InputFileNotFoundFor10MostUsedWords_shouldThrow) {
	TextAnalyzer textAnalyzer{};
    EXPECT_THROW(textAnalyzer.findTenMostUsedWords(".//dummy.txt"), std::runtime_error);
}

TEST(TextAnalyzerTests, InputFileNotFoundForSmileyPositions_shouldThrow) {
	TextAnalyzer textAnalyzer{};
    EXPECT_THROW(textAnalyzer.findSmileyPositions(".//dummy.txt"), std::runtime_error);
}

TEST(TextAnalyzerTests, callWriteToOutputDirectly_shouldNotThrow) {
	TextAnalyzer textAnalyzer{};
    EXPECT_NO_THROW(textAnalyzer.writeOutputToTextFile());
	EXPECT_NO_THROW(textAnalyzer.writeOutputToConsole());
	EXPECT_NO_THROW(textAnalyzer.writeOutputToXMLFile());
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}