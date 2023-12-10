#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int main()
{
    // Declaring all variables
    double tmp, mini, maxi, new_mini, new_maxi;
    double sum, cnt, square_sum, mean, standard_deviation;
    // Opening file in reading mode
    ifstream in1("2input.csv");
    ifstream in2("2input.csv");
    ifstream in3("2input.csv");
    ifstream in4("2input.csv");
    int opt;
    cout << "\nEnter option: \n1.Min-Max Normalization \n2.Z-Score             Normalization\nOption : ";
    cin >> opt;
    ofstream out1("exp2_output_MinMax.csv");
    ofstream out2("exp2_output_Zscore.csv");
    switch (opt)
    {
    case 1: // Finding Min and Max
        if (!in1)
        {
            cout << "Error opening file, try again.";
            exit(0);
        }
        out1 << "Data "
             << ","
             << "Normalized Data"
             << "\n";
        in1 >> tmp;

        mini = tmp;
        maxi = tmp;
        while (in1)
        {
            if (tmp > maxi)
                maxi = tmp;
            if (tmp < mini)
                mini = tmp;
            in1 >> tmp;
        }
        // Min max Normalization
        cout << "Enter new min: ";
        cin >> new_mini;
        cout << "\nEnter new max: ";
        cin >> new_maxi;
        in2 >> tmp;
        while (in2)
        {
            double tmp2 = (((tmp -
                             mini) /
                            (maxi - mini)) *
                           (new_maxi - new_mini)) +
                          new_mini;

            out1 << tmp << "," << tmp2 << "\n";
            in2 >> tmp;
        }
        out1.close();
        break;
    case 2:
        if (!in3)
        {
            cout << "Error opening file, try again.";
            exit(0);
        }
        out2 << "Data "
             << ","

             << "Normalized Data"
             << "\n";
        in4 >> tmp;
        while (in4)
        {
            sum += tmp;
            cnt++;
            in4 >> tmp;
        }
        mean = sum / cnt; // calculate mean
        in4.clear();
        in4.seekg(0, ios::beg); // to set pointer again start of file
        in4 >> tmp;
        while (in4)
        {
            square_sum += (tmp - mean) * (tmp - mean);
            in4 >> tmp;
        }
        standard_deviation = sqrt(square_sum / cnt); // to find

        // standard deviation
        in4.clear();
        in4.seekg(0, ios::beg);
        in4 >> tmp;
        while (in4)
        {
            double tmp2 = ((tmp - mean) / standard_deviation);
            out2 << tmp << "," << tmp2 << endl;
            in4 >> tmp;
        }
        out2.close();
        break;
    default:

        cout << "Wrong Option" << endl;
        out1.close();
        out2.close();
        break;
    }
    return 0;
}