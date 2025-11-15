#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <functional>

namespace AJimpa
{
    // BCL : Basic Command Line
    class BCL
    {
    private:
        // Command map linking user commands to functions
        std::map<std::string, std::function<void(const std::vector<std::string> &)>> commands;
        std::string input;
        bool LineEnable = false;

        // Function to split user input into command and arguments
        std::vector<std::string> parseInput(const std::string &inputdata)
        {
            std::vector<std::string> tokens;
            std::istringstream iss(inputdata);
            std::string token;
            while (iss >> token)
            {
                tokens.push_back(token);
            }
            return tokens;
        }

        void addMath(const std::vector<std::string> &args)
        {
            if (args.size() < 3)
            {
                std::cout << "Usage: add <num1> <num2>" << std::endl;
                return;
            }
            int num1 = std::stoi(args[1]);
            int num2 = std::stoi(args[2]);
            std::cout << "Result: " << num1 + num2 << std::endl;
        }

    public:
        BCL()
        {
            LineEnable = true;
            //AddCommand("add" , BCL::addMath);
        }
        ~BCL()
        {
            LineEnable = false;
        }

        void AddCommand(std::string Name, std::function<void(const std::vector<std::string> &)> Function)
        {
            commands[Name] = Function;
        }

        void Run()
        {
            std::cout << "Welcome to the custom command shell! Type 'exit' to quit." << std::endl;

            // Main loop to keep the application running
            while (true)
            {
                std::cout << "> "; // Command prompt

                // Get input from the user
                std::getline(std::cin, input);

                if (LineEnable == false)
                {
                    std::cout << "Force Exiting the shell..." << std::endl;
                    break;
                }

                // If user types 'exit', break the loop and exit
                if (input == "exit" || input == "quit")
                {
                    std::cout << "Exiting the shell..." << std::endl;
                    break;
                }

                // Parse the input into command and arguments
                std::vector<std::string> tokens = parseInput(input);

                if (tokens.empty())
                {
                    continue; // If no command entered, continue to the next iteration
                }

                // The first token is the command
                std::string command = tokens[0];

                // Find and execute the corresponding command function
                auto it = commands.find(command);
                if (it != commands.end())
                {
                    it->second(tokens); // Execute the command function with arguments
                }
                else
                {
                    std::cout << "Unknown command: " << command << std::endl;
                }
            }
        }
    };

}
