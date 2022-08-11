Text Analyser Tool
    For a given input file, the text is analysed to find out the 
        - 10 most commonly used words
        - start position of all the smileys in the text (Currently this tool supports smileys with the following pattern colon followed by an optional dash and a bracket)
    This tool can write the analysis result to the following formats:
        - XML file
        - txt file
        - Console
    User has the full control to choose any combination of the above mentioned output formats.

Usage examples:
    ./TextAnalyzerTool -f "/home/dino/Documents/Job/CodingTask/BMW/input_data/data1.txt" --xml --console --text
    ./TextAnalyzerTool -f "/home/dino/Documents/Job/CodingTask/BMW/input_data/data1.txt" --xml --text
    ./TextAnalyzerTool -f "/home/dino/Documents/Job/CodingTask/BMW/input_data/data1.txt" --text
    ./TextAnalyzerTool -f "/home/dino/Documents/Job/CodingTask/BMW/input_data/data1.txt" --console

Explanation for Command Line Arguments:
    -f "file_path" --> Use this parameter to specify the input file to analyse. It is a mandatory parameter
    --xml --> Use this parameter to write the analysis output to TextAnalyzerOutput.xml file. This file will be located in the same path as that of the executable. This is an optional argument.
    --text --> Use this parameter to write the analysis output to TextAnalyzerOutput.txt file. This file will be located in the same path as that of the executable. This is an optional argument.
    --console --> Use this parameter to print the analysis output to the console. This is an optional argument.