#include "../lang.cpp"
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    lang::printMenu();

    while (true)
    {
        cout << ">>> ";

        string s;
        getline(cin, s);
        char op = s.at(0);

        if (s.length() > 1)
        {
            cout << "Invalid option, please try again\n"
                 << endl;
            continue;
        }

        else if (op == '1')
        {
            cout << "\nINPUT: <filepath_to_text_file> <filepath_to_language_file> <order_k> <smoothing_parameter>\n"
                 << endl;

            cout << ">>> ";
            string input;
            getline(cin, input);

            // Split input into arguments
            vector<string> inputArgs;
            string buf;
            stringstream ss(input);

            while (ss >> buf)
            {
                inputArgs.push_back(buf);
            }

            // Validate arguments
            int valid = lang::validateInput(inputArgs);

            if (valid == 1 || valid == 2 || valid == 3)
            {
                lang::printMenu();
                continue;
            }

            // Perform analysis
            try
            {
                lang lang(stoi(inputArgs.at(2)), stod(inputArgs.at(3)));
                lang.compareToFile(&inputArgs.at(0)[0], &inputArgs.at(1)[0]);
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;

                lang::printMenu();
                continue;
            }

            return 0;
        }

        else if (op == '2')
        {
            cout << "\nINPUT: <filepath_to_text_file> <filepath_to_model_file> <order_k> <smoothing_parameter>\n"
                 << endl;

            cout << ">>> ";
            string input;
            getline(cin, input);

            // Split input into arguments
            vector<string> inputArgs;
            string buf;
            stringstream ss(input);

            while (ss >> buf)
            {
                inputArgs.push_back(buf);
            }

            // Validate arguments
            int valid = lang::validateInput(inputArgs);

            if (valid == 1 || valid == 2 || valid == 3)
            {
                lang::printMenu();
                continue;
            }

            // Perform analysis
            try
            {
                lang lang(stoi(inputArgs.at(2)), stod(inputArgs.at(3)));
                lang.compareToModel(&inputArgs.at(0)[0], &inputArgs.at(1)[0]);
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;

                lang::printMenu();
                continue;
            }

            return 0;
        }

        else if (op == 'q')
        {
            cout << "\nLeaving program, goodbye!\n"
                 << endl;
            return 0;
        }

        else
        {
            cout << "Invalid option, please try again\n"
                 << endl;
            continue;
        }
    }
    return 0;
}
