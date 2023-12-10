#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> readData(const string &filename)
{
    vector<int> data;
    fstream file(filename, ios::in);

    if (!file.is_open())
    {
        cerr << "Error in opening input file: " << filename << endl;
        exit(1);
    }

    string line, value;
    int lineCount = 0;

    while (getline(file, line))
    {
        if (lineCount > 0)
        {
            stringstream ss(line);
            getline(ss, value, ',');
            data.push_back(stoi(value));
        }
        lineCount++;
    }

    file.close();
    return data;
}

float calculateCorrelationCoefficient(const vector<int> &a, const vector<int> &b)
{
    int n = a.size();
    int a_plus = 0, b_plus = 0, ab_plus = 0;

    for (int i = 0; i < n; i++)
    {
        a_plus += a[i] == 1 ? 1 : 0;
        b_plus += b[i] == 1 ? 1 : 0;
        ab_plus += (a[i] == 1 && b[i] == 1) ? 1 : 0;
    }

    if (a_plus == 0 || b_plus == 0)
    {
        return 0.0;
    }

    return static_cast<float>(ab_plus) / (a_plus * b_plus);
}

void writeCorrelationCoefficient(const string &filename, float corr_coeff)
{
    ofstream file(filename, ios::out);

    if (!file.is_open())
    {
        cerr << "Error in opening output file: " << filename << endl;
        exit(1);
    }

    file << "Pearson Correlation Coefficient"
         << "," << corr_coeff << endl;
    file.close();
}

int main()
{
    string inputFileName = "correlation_input.csv";
    string outputFileName = "correlation_output.csv";

    vector<int> a = readData(inputFileName);
    vector<int> b = readData(inputFileName);

    float corr_coeff = calculateCorrelationCoefficient(a, b);

    writeCorrelationCoefficient(outputFileName, corr_coeff);

    cout << "Correlation coefficient calculated and saved in '" << outputFileName << "'." << endl;

    return 0;
}