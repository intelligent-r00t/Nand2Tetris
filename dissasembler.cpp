#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using std::string;

// How to run the code //

//  1. Ensure that either G++ or MSVC/Clang++ is setup on your system
//  You need some C++ compiler installed on your system
//      Run g++ --version to check (use if you're on Linux)

//      g++ --version Output
//          ++ (GCC) 13.2.1 20230801
//          Copyright (C) 2023 Free Software Foundation, Inc.
//          This is free software; see the source for copying conditions.  There is NO
//          warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


//      Run clang++ --version to check (use if you're on macOS/Linux)

//      clang++ --version Output
//          clang version 17.0.6
//          Target: x86_64-pc-linux-gnu
//          Thread model: posix
//          InstalledDir: /usr/bin

// Note: If you're using Windows, then you will need to use a more cumbersome method
//       to get either G++ or Clang++ installed. Contact me if you wish to go this
//       route. I highly advise against it, but I will help if you so choose to.


//  2. Go to the directory where your files are located
//  You can check if your files are there by running 'ls' in the terminal

//  3. Run the following
//  g++ ./disassembler.cpp -o disassembler.out (this is compiling your program)
//  ./disassembler.out "sample.hack" (this is executing your program)

// Note: If you are on Windows, please use .exe rather .out for your 
//      compiled binary

//  Please use "clang++" rather than "g++" if you're using that compiler
//  ./ indicates the current directory 
//  You will need to substitute "sample.hack" for the appropriate HACK file

int main(int argc, char *argv[])
{
    string fileName = argv[1];
    std::fstream file;
    std::vector<string> Lines;

    // Check if appropriate file extension
    if (fileName.find(".hack") != std::string::npos)
    {
        // Check if file exists and open
        file.open(argv[1], std::ios::in);

        if (file.is_open())
        {
            string tp;
            while(getline(file, tp))
            { 
                Lines.push_back(tp);
            }
            file.close();

            // Vector to be used for storing HACK instructions
            std::vector<string> hackList;

            // Computation Map
            std::map<string, string> compTable = {
                {"0101010", "0"},
                {"0111111", "1"},
                {"0111010", "-1"},
                {"0001100", "D"},
                {"0110000", "A"},
                {"1110000", "M"},
                {"0001101", "!D"},
                {"0110001", "!A"},
                {"1110001", "!M"},
                {"0001111", "-D"},
                {"0110011", "-A"},
                {"1110011", "-M"},
                {"0011111", "D+1"},
                {"0110111", "A+1"},
                {"1110111", "M+1"},
                {"0001110", "D-1"},
                {"0110010", "A-1"},
                {"1110010", "M-1"},
                {"0000010", "D+A"},
                {"1000010", "D+M"},
                {"0010011", "D-A"},
                {"1010011", "D-M"},
                {"0000111", "A-D"},
                {"1000111", "M-D"},
                {"0000000", "D&A"},
                {"1000000", "D&M"},
                {"0010101", "D|A"},
                {"1010101", "D|M"}
            };

            // Destination Map
            std::map<string, string> destTable = {
                {"000", ""},
                {"001", "M="},
                {"010", "D="},
                {"011", "DM="},
                {"100", "A="},
                {"101", "AM="},
                {"110", "AD="},
                {"111", "ADM="}
            };

            // Jump Map
            std::map<string, string> jumpTable = {
                {"000", ""},
                {"001", ";JGT"},
                {"010", ";JEQ"},
                {"011", ";JGE"},
                {"100", ";JLT"},
                {"101", ";JNE"},
                {"110", ";JLE"},
                {"111", ";JMP"}
            };

            // Loop through all assembly lines in the HACK file
            for (int i = 0; i < Lines.size(); i++)
            {
                string line = Lines[i];

                // A Instruction

                    // https://www.geeksforgeeks.org/methods-to-concatenate-string-in-c-c-with-examples/
       
                    // https://www.geeksforgeeks.org/vectorpush_back-vectorpop_back-c-stl/

                // if - Check instruction op-code (the first char in the string)
                 if (line[0] == '0')
                {
                // Get the remaining substring and convert to decimal 
                // Conversion
                //      string value = line.substr(1, 15);
                //      unsigned long long binVal = stoull(value, 0, 2);
                    string value = line.substr(1, 15);
                    unsigned long long binVal = stoull(value, 0, 2);

                // Construct the appropriate HACK instruction
                    string hackInstruction = "@" + std::to_string(binVal);

                // Append to hackList
                    hackList.push_back(hackInstruction);
                }

                // C Instruction

                // https://www.javatpoint.com/post/cpp-map

                // else if - Check instruction op-code (the first char in the string)
                  else if (line[0] == '1')
                {   
                
                // Create strings from the appropriate substrings
                // cBit, dBit, jBit
                    string cBit = line.substr(3, 7);
                    string dBit = line.substr(10, 3);
                    string jBit = line.substr(13, 3);

                // Return HACK destination string from destTable using dBit
                    string dest = destTable[dBit];
                // Return HACK computation string from compTable using cBit
                    string comp = compTable[cBit];
                // Return HACK jump string from jumpTable using jBit
                    string jump = jumpTable[jBit];

                // Construct the appropriate HACK instruction
                    string hackInstruction = dest + comp + jump;

                // Append to hackList
                    hackList.push_back(hackInstruction);
                }

            }

            // Write to file
            file.open(fileName.replace(fileName.find(".hack"), 5, ".asm"), std::ios::out);

            if(file.is_open())
            {
                for (int i = 0; i < hackList.size(); i++)
                {
                    file << hackList[i] << std::endl;
                }
                file.close();
            }
        }
    }
}
