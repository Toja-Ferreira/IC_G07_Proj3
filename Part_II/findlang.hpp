#ifndef FINDLANG_H
#define FINDLANG_H

#include "lang.cpp"

using namespace std;

class findlang
{
    private:
        /**
         * @brief Lang object to be used by this class
         */
        lang langObj;

    public:
        findlang();

        /**
         * findlang class constructor
         * @param k order of the finite-context model to be used by the lang object
         * @param alpha smoothing parameter of the finite-context model to be used by the lang object
         */
        findlang(int k, double alpha);

        /**
         * @brief Function that compares a certain text file to a set of languages and estimates the
         * language that best representes the text file
         * @param filename path of text file to be analyzed
         * @param languages vector of strings containing the paths of the text files that contain the languages/models to be compared to
         * @param typeOfComp type of comparison to be made ('F' for language files, 'M' for model files)
         * @return string containing the name of the language file that best represents the text file
         */
        string estimateLanguage(char *filename, vector<string> languages, char typeOfComp);
};

#endif