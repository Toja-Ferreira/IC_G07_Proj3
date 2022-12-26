#include "fcm.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;

#define ALPHABET_SIZE 27

fcm::fcm(int k, double alpha)
{
    this->k = k;
    this->alpha = alpha;
}

void fcm::estimateFileEntropy(char *filename, char toSave)
{
    // Open text file to be analysed
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        cerr << "\nERROR: Could not open file: " << filename << "\n" << endl;
        return;
    }

    cout << "-----------------------------------------------------------------------------" << endl; 
    cout << "Analysing file: " << filename << "\n" << endl;   

    // Initialize model in the form of <context, <next char, count>>
    map<string, map<char, int>> model;

    // Initialize context according to order k
    string context = "";
    char nextChar;
    for (int i = 0; i < this->k; i++)
    {
        fcm::readChar(ifs, &nextChar);
        context += nextChar;
    }

    // Read text file and load model with data for each context of order k
    while (!ifs.eof() && ifs.good())
    {
        fcm::readChar(ifs, &nextChar);

        // If context does not exists in model
        if(model.count(context) == 0)
        {
            model[context][nextChar] = 1;
        }
        else
        {
            // If next char does not exists in model for given context
            if(model[context].count(nextChar) == 0)
            {
                model[context][nextChar] = 1;
            }
            else
            {
                model[context][nextChar]++;
            }
        }

        // Update context by removing its first char and appending next char
        context = context.substr(1, this->k - 1) + nextChar;
    }
    ifs.close();

    // Save model in memory, if requested
    if (toSave == 'Y' || toSave == 'y')
    {
        saveModel(model, filename);
    }

    // Estimate entropy of text according to model
    double entropy = calculateModelEntropy(model);

    cout << "Entropy of " << filename << " is " << entropy << endl;
    cout << "-----------------------------------------------------------------------------" << endl; 
}
    
double fcm::calculateModelEntropy(map<string, map<char, int>> model)
{
    // Calculate entropy of model
    double entropy = 0;
    
    for (auto context : model)
    {
        // Calculate total number of nextChars in this context
        int totalChars = accumulate(context.second.begin(), context.second.end(), 0, [](int sum, pair<char, int> nextChar)
        {
            return sum + nextChar.second;
        });

        // Calculate entropy of this context
        double contextEntropy = 0;
        for (auto nextChar : context.second)
        {
            // Calculate entropy of nextChar and add it to context entropy
            double prob = (double) (nextChar.second + this->alpha) / (totalChars + this->alpha * ALPHABET_SIZE);
            contextEntropy += prob * log2(prob);
        }

        // Add context entropy to total entropy
        entropy += contextEntropy * totalChars;
    }

    // Normalize entropy
    entropy = abs(entropy / accumulate(model.begin(), model.end(), 0, [](int sum, pair<string, map<char, int>> context)
    {
        return sum + accumulate(context.second.begin(), context.second.end(), 0, [](int sum, pair<char, int> nextChar)
        {
            return sum + nextChar.second;
        });
    }));

    return entropy;
}


void fcm::saveModel(map<string, map<char, int>> model, char *filename)
{
    // Open text file to save model
    string newFileName = filename;
    newFileName = "./models/model_" + newFileName + ".txt";

    ofstream outfile;
    outfile.open(newFileName, ofstream::trunc);

    // Write parameters to file in the form <order k>,<alpha>
    outfile << this->k << ',' << this->alpha;

    // Write model to file in the form <context>:   <next char>-<count>
    for (auto context : model)
    {
        outfile << '\n' << context.first << ':';

        for (auto nextChar : context.second)
        {
            outfile << '\t' << nextChar.first << '-' << nextChar.second;
        }
    }
    outfile.close();

    cout << "Model has been saved in: " << newFileName << "\n" << endl;
}
