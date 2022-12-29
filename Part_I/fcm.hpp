#ifndef FCM_H
#define FCM_H

#include <map>
#include <fstream>
#include <math.h>

using namespace std;

class fcm
{
    private:
        /**
         * @brief Order of the finite-context model
         */
        int k;

        /**
         * @brief Smoothing parameter of the finite-context model
         */
        double alpha;

    public:
        fcm();

        /**
         * FCM class constructor
         * @param k order of the finite-context model
         * @param alfa smoothing parameter of the finite-context model
         */
        fcm(int k, double alfa);

        /**
         * @brief Function that creates a finite-context model from a given text file, saves it in memory and estimates the Shannon entropy of the text based on this model
         * @param filename path of text file to be analyzed
         * @param toSave flag that indicates if the model should be saved in memory ('Y'/'N')
         * @param emptyModel optional pointer to empty model data structure, required if user wants to return the model to use in other methods (default NULL)
         */
        void loadModel(char *filename, char toSave, map<string, map<char, int>> *emptyModel = 0);

        /**
         * @brief Function that saves a finite-context model with information of a given text in a .txt file in memory
         * @param filename path of text file from which the model was generated
         * @param model finite-context model with the information obtained from the text file
         */
        void saveModel(char *filename, map<string, map<char, int>> model);

        /**
         * @brief Function that loads an empty model structure with information of an existing model saved in a .txt file in memory
         * @param filename path of text file where the model is stored
         * @param model reference to empty model data structure where the read information will be stored
         * @param orderM reference to variable where order of the model will be stored
         * @param alphaM reference to variable where smoothing parameter of the model will be stored
         */
        void readModel(char *filename, map<string, map<char, int>> &model, int &orderM, double &alphaM);

        /**
         * @brief Function that calculates the entropy of a given finite-context model
         * @param model finite-context model with information obtained from a text file
         * @return Entropy of the given model
         */
        double calculateModelEntropy(map<string, map<char, int>> model);

        /**
         * @brief Auxiliary function that reads the next character of a file, ignoring new lines and tabs
         * @param ifs reference to input file stream
         * @param c pointer to where character to be read will be stored
         */
        static void readChar(ifstream &ifs, char *c)
        {
            char nextChar;
            do
            {
                ifs.get(nextChar);

                if (nextChar != '\n' && nextChar != '\t')
                {
                    *c = nextChar;
                    break;
                }

                if (ifs.eof())
                {
                    *c = EOF;
                    break;
                }

            } while (!ifs.eof() && ifs.good());
        }

        /**
         * Auxiliary function to check if given string is valid integer
         * @param s string to validate
         * @return True if s is valid integer, otherwise False
         */
        static bool isInteger(const string &s)
        {
            if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            {
                return false;
            }

            char *p;
            strtol(s.c_str(), &p, 10);

            return (*p == 0);
        }

        /**
         * Auxiliary function to check if given string is valid float/double
         * @param s string to validate
         * @return True if s is valid float/double, otherwise False
         */
        static bool isDecimal(const string &s)
        {
            if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            {
                return false;
            }

            char *p;
            strtod(s.c_str(), &p);

            return (*p == 0);
        }
};

#endif