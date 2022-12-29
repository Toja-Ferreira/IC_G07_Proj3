#ifndef LANG_H
#define LANG_H

#include "../Part_I/fcm.hpp"
#include <vector>
#include <iostream>

using namespace std;

class lang
{
    private:
        /**
         * @brief FCM object to be used by this class
         */
        fcm fcmObj;

        /**
         * @brief Order of the finite-context model
         */
        int k;

        /**
         * @brief Smoothing parameter of the finite-context model
         */
        double alpha;

    public:
        lang();

        /**
         * Lang class constructor
         * @param k order of the finite-context model
         * @param alpha smoothing parameter of the finite-context model
         */
        lang(int k, double alpha);

        /**
         * @brief Function that compares a certain text file to a language and estimates the number 
         * of bits needed to compress the text file using the language
         * @param filename path of text file to be analyzed
         * @param classFilename path of the text file that contains either the language text or the language model to be compared to
         * @param typeOfComp type of comparison to be made ('F' for file, 'M' for existing model)
         * @return estimated number of bits needed to compress the text file using the language
         */
        double estimateBits(char *filename, char *classFilename, char typeOfComp);

        /**
         * @brief Auxiliary function that checks if user input is valid
         * @param userInput vector of strings containing the user input
         * @param typeOfComp type of comparison to be made ('F' for file, 'M' for existing model)
         * @return 0 if input is valid, 1 if wrong number of args, 2 if invalid order k, 3 if invalid smoothing parameter
         */
        static int validateInput(vector<string> userInput, char typeOfComp)
        {
            if (typeOfComp == 'F')
            {
                if (userInput.size() != 4)
                {
                    cout << "ERROR: Wrong number of arguments!\n"
                        << endl;

                    return 1;
                }

                if (!fcm::isInteger(userInput.at(2)) || stoi(userInput.at(2)) <= 0)
                {
                    cerr << "ERROR! Model order k must be a valid positive integer\n"
                        << endl;

                    return 2;
                }

                if (!fcm::isDecimal(userInput.at(3)) || stod(userInput.at(3)) <= 0)
                {
                    cerr << "ERROR! Smoothing parameter must be a valid positive number\n"
                        << endl;

                    return 3;
                }
            }
            else
            {
                if (userInput.size() != 2)
                {
                    cout << "ERROR: Wrong number of arguments!\n"
                        << endl;

                    return 1;
                }
            }
            return 0;
        };

        /**
         * @brief Auxiliary function that prints the menu of the program
         */
        static void printMenu()
        {
            cout << "-----------------------------------TEST LANG-----------------------------------\n"
                << "Please choose an option:\n"
                << "[1]: compare file with language file\n"
                << "[2]: compare file with existing language model\n"
                << "[q]: exit\n"
                << endl;
        };
};

#endif