#include<iostream>
#include<TextAnalyzer.hpp>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int argc, char** argv)
{
    TextAnalyzer textAnalyzer{};
    std::string inputFilePath;

    try
    {
        po::options_description desc{"Options"};
        desc.add_options()
        ("help,h", "Help screen")
        ("file,f", po::value<std::string>(&inputFilePath), "Input file")
        ("console", "Writes ouput to Console")
        ("text", "Writes ouput to Text file")
        ("xml", "Writes ouput to XML file");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if ( vm.count("help") || argc == 1) {
            std::cout << desc << '\n';
            return 0;
        }
        else if(vm.count("file"))
        {
            textAnalyzer.findTenMostUsedWords(inputFilePath);
            textAnalyzer.findSmileyPositions(inputFilePath);
        }

        if (vm.count("console"))
        {
            textAnalyzer.writeOutputToConsole();
        }
        if (vm.count("text"))
            textAnalyzer.writeOutputToTextFile();
        if (vm.count("xml"))
            textAnalyzer.writeOutputToXMLFile();
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
}