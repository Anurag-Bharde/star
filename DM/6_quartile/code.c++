#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate the median of a vector
float calculateMedian(vector<int> a)
{
    int size = a.size();
    if (size % 2 == 1)
        return a[size / 2];
    else
        return (a[(size / 2) - 1] + a[size / 2]) / 2.0;
}

// Function to calculate the first quartile (Q1)
float calculateQuartile1(vector<int> v)
{
    int n = v.size();
    vector<int> first;

    for (int i = 0; i < n / 2; i++)
    {
        first.push_back(v[i]);
    }
    return calculateMedian(first);
}

// Function to calculate the third quartile (Q3)
float calculateQuartile3(vector<int> v)
{
    int n = v.size();
    vector<int> last;
    if (n % 2 == 0)
    {
        for (int i = n / 2; i < n; i++)
        {
            last.push_back(v[i]);
        }
    }
    else
    {
        for (int i = n / 2 + 1; i < n; i++)
        {
            last.push_back(v[i]);
        }
    }
    return calculateMedian(last);
}

int main()
{
    ifstream in("five_number_input.csv");
    if (!in.is_open())
    {
        cout << "Error: Unable to open the input file." << endl;
        exit(0);
    }

    ofstream out("five_number_output.csv");

    int i = 0;
    string line, mark;
    vector<int> arr;

    // Read data from the input file
    while (getline(in, line))
    {
        if (i == 0)
        {
            i++;
            continue;
        }
        stringstream str(line);

        getline(str, mark, ',');
        int x = stoi(mark);
        arr.push_back(x);
    }

    int n = arr.size();
    sort(arr.begin(), arr.end());

    // Write results to the output file and console
    out << "Minimum value: "
        << "," << arr[0] << "\n";
    out << "First Quartile (Q1) value: "
        << "," << calculateQuartile1(arr) << "\n";
    out << "Median value: "
        << "," << calculateMedian(arr) << "\n";
    out << "Third Quartile (Q3) value: "
        << "," << calculateQuartile3(arr) << "\n";
    out << "Maximum value: "
        << "," << arr[n - 1] << "\n";

    cout << "The minimum value is " << arr[0] << endl;
    cout << "The First Quartile (Q1) is " << calculateQuartile1(arr) << endl;
    cout << "The median is " << calculateMedian(arr) << endl;
    cout << "The Third Quartile (Q3) is " << calculateQuartile3(arr) << endl;
    cout << "The maximum value is " << arr[n - 1] << endl;

    return 0;
}