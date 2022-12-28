#include "../fcm.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "ERROR: Usage: ./fcmTest <filepath> <order_k> <smoothing_parameter>\n"
             << endl;
        return 1;
    }

    if (!fcm::isInteger(argv[2]) || stoi(argv[2]) <= 0)
    {
        cerr << "ERROR! Model order k must be a valid positive integer\n"
             << "USAGE: ./fcmTest <filepath> <order_k> <smoothing_parameter>\n"
             << endl;
        return 1;
    }

    if (!fcm::isDecimal(argv[3]) || stod(argv[3]) <= 0)
    {
        cerr << "ERROR! Smoothing parameter must be a valid positive number\n"
             << "USAGE: ./fcmTest <filepath> <order_k> <smoothing_parameter>\n"
             << endl;
        return 1;
    }

    cout << "-----------------------------------TEST FCM-----------------------------------\n"
         << "Order k = " << stoi(argv[2])
         << "\nSmoothing parameter alpha = " << stod(argv[3]) << "\n\n"
         << "Please choose an option:\n"
         << "[1]: analyse file and save model in memory\n"
         << "[2]: analyse file without saving model\n"
         << "[q]: exit\n"
         << endl;

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
            fcm fcm(stoi(argv[2]), stod(argv[3]));

            try
            {
                fcm.loadModel(argv[1], 'Y');
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                return 1;
            }

            return 0;
        }

        else if (op == '2')
        {
            fcm fcm(stoi(argv[2]), stod(argv[3]));

            try
            {
                fcm.loadModel(argv[1], 'N');
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                return 1;
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