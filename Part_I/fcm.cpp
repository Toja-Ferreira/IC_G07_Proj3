#include "fcm.hpp"
#include <iostream>
#include <string>
#include <numeric>

using namespace std;

#define ALPHABET_SIZE 27

fcm::fcm()
{
}

fcm::fcm(int k, double alpha)
{
    this->k = k;
    this->alpha = alpha;
}

void fcm::loadModel(char *filename, char toSave, map<string, map<char, int>> *emptyModel)
{
    // Open text file to be analysed
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        throw invalid_argument("\nERROR: Could not open file: " + string(filename) + "\nCheck if the file exists and the path is correct\n");
    }

    // Check if file is empty
    if (ifs.peek() == ifstream::traits_type::eof())
    {
        throw invalid_argument("\nERROR: " + string(filename) + " is an empty file! \nPlease use a valid text file\n");
    }

    // Get name of file without path
    size_t lastSlash = string(filename).find_last_of("/\\");

    if (lastSlash != string::npos)
    {
        filename = filename + lastSlash + 1;
    }

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Analysing file: " << filename << "\n"
         << endl;

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
        if (model.count(context) == 0)
        {
            model[context][nextChar] = 1;
        }
        else
        {
            // If next char does not exists in model for given context (ignoring EOF)
            if (model[context].count(nextChar) == 0)
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

    // Remove all appearances of EOF from model
    for (auto &context : model)
    {
        context.second.erase(EOF);
    }

    // Save model in empty model structure
    if (emptyModel)
    {
        *emptyModel = model;
    }
    else
    {
        // Save model in memory, if requested by user
        if (toSave == 'Y' || toSave == 'y')
        {
            saveModel(filename, model);
        }

        // Estimate entropy of text according to model
        double entropy = calculateModelEntropy(model);

        cout << "Estimated entropy of " << filename << " is " << entropy << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
    }
}

void fcm::saveModel(char *filename, map<string, map<char, int>> model)
{
    // Open text file to write model in
    string newFileName = "./models/modelOrder" + to_string(this->k) + "_" + string(filename) + ".txt";

    ofstream outfile;
    outfile.open(newFileName, ofstream::trunc);

    // Write parameters to file in the form <order k>,<alpha>
    outfile << this->k << ',' << this->alpha;

    // Write model to file in the form <context>:   <next char>-<count>
    for (auto context : model)
    {
        outfile << '\n'
                << context.first << ':';

        for (auto nextChar : context.second)
        {
            outfile << '\t' << nextChar.first << '-' << nextChar.second;
        }
    }
    outfile.close();

    cout << "Model has been saved in: " << newFileName << "\n"
         << endl;
}

void fcm::readModel(char *filename, map<string, map<char, int>> &model)
{
    // Open text file to be read
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        throw invalid_argument("\nERROR: Could not open file: " + string(filename) + "\nCheck if the file exists and the path is correct\n");
    }

    // Check if file is empty
    if (ifs.peek() == ifstream::traits_type::eof())
    {
        throw invalid_argument("\nERROR: " + string(filename) + " is an empty file! \nPlease use a valid text file\n");
    }

    // Try to read information from text file, will fail if its not in the correct format (not a model file)
    string line;
    getline(ifs, line);

    try
    {
        this->k = stoi(line.substr(0, line.find(',')));
        this->alpha = stod(line.substr(line.find(',') + 1));

        // Read model from file
        while (!ifs.eof() && ifs.good())
        {
            getline(ifs, line);

            // Read context from line
            string context = line.substr(0, line.find(':'));

            // Read nextChars and counts from line
            map<char, int> nextChars;
            line = line.substr(line.find(':') + 1);
            while (line.find('\t') != string::npos)
            {
                string nextChar = line.substr(line.find('\t') + 1, line.find('-') - line.find('\t') - 1);
                int count = stoi(line.substr(line.find('-') + 1, line.find('\t') - line.find('-') - 1));

                nextChars[nextChar[0]] = count;

                line = line.substr(line.find('\t') + 1);
            }

            // Save context and nextChars in model
            model[context] = nextChars;
        }
        ifs.close();
    }
    catch (const exception &e)
    {
        throw invalid_argument("\nERROR: The information in " + string(filename) + " is not correctly formatted! \nPlease use a valid text file\n");
    }
}

double fcm::calculateModelEntropy(map<string, map<char, int>> model)
{
    // Calculate entropy of model
    double entropy = 0;

    for (auto context : model)
    {
        // Calculate total number of nextChars in this context
        int totalChars = accumulate(context.second.begin(), context.second.end(), 0, [](int sum, pair<char, int> nextChar)
                                    { return sum + nextChar.second; });

        // Calculate entropy of this context
        double contextEntropy = 0;
        for (auto nextChar : context.second)
        {
            // Calculate entropy of nextChar and add it to context entropy
            double prob = (double)(nextChar.second + this->alpha) / (totalChars + this->alpha * ALPHABET_SIZE);
            contextEntropy += prob * log2(prob);
        }

        // Add context entropy to total entropy
        entropy += contextEntropy * totalChars;
    }

    // Obtain the final total entropy
    entropy = -(entropy / accumulate(model.begin(), model.end(), 0, [](int sum, pair<string, map<char, int>> context)
                                     { return sum + accumulate(context.second.begin(), context.second.end(), 0, [](int sum, pair<char, int> nextChar)
                                                               { return sum + nextChar.second; }); }));

    return entropy;
}
