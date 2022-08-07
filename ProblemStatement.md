Please write C++ code which is able to analyse a text block covering the following requirements:

1.       Computes the start position in the text of all the smileys. Smileys are defined as the character colon plus an optional dash character and a bracket. e.g: :-] or :(

2.       Computes the top 10 used words (excluding smileys)

3.       Supports the following output formats: Console, Simple text file, XML file. Any combination of these backends can be specified through command line arguments (Console only, Text file only, Text file + XML file, Text file + XML + console, etc). Each output should contain all the above information (1 and 2 from this list). Formatting is up to the developer.Note: This last requirement is not skippable and it is expected that the solution provided is generic (e.g. allows for easy addition of future output formats).

Additional information:

·       UTF8 encoding can be assumed

·       Lines are separated by '\n'

·       Words are separated by whitespace

·       There are some edge cases that should be considered:

·       Whitespace can be '\t', multiple consecutive whitespace characters, etc

·       The text can consist of a single line without '\n' at the end. The line count should be 1 in such a case.

Desired solution should have the following:

·       Solution has to run on Linux.

·       Design with classes and clean APIs.

·       Good documentation.

·       Code quality to be comparable to production code. -- Exception handle

·       Usage of C++11/14/17 features.

·       Usage of STL and Boost features would be preferable whenever applicable, or other known open source libraries.

·       Unit tests with high coverage > 90%.

·       CMake files which covers building and adding the tests.

 