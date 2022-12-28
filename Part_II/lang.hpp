#ifndef LANG_H
#define LANG_H

#include "../Part_I/fcm.hpp"
#include <vector>

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
         * @brief Function that compares a certain text file to a text file representing a language and
         * estimates the number of bits needed to compress the text file using the model generated from the language file
         * @param filename path of text file to be analyzed
         * @param languageFilename path of the text file that contains the language to be compared to
         */
        void compareToFile(char *filename, char *languageFilename);

        /**
         * @brief Function that compares a certain text file to an existing language model
         * and estimates the number of bits needed to compress the text file using the model
         * @param filename path of text file to be analyzed
         * @param modelFilename path of the text file that contains the existing model representing the language to be compared to
         */
        void compareToModel(char *filename, char *modelFilename);

        /**
         * @brief Auxiliary function that checks if user input is valid
         * @param userInput vector of strings containing the user input
         * @return 0 if input is valid, 1 if wrong number of args, 2 if invalid order k, 3 if invalid smoothing parameter
         */
        static int validateInput(vector<string> userInput)
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