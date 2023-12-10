#include <bits/stdc++.h>
using namespace std;
float median(vector<int> a)
{
    int size = a.size();
    if (size % 2 == 1)
        return a[size / 2];
    else
        return (a[(size / 2) - 1] + a[size / 2]) / 2.0;
}
float quartile1(vector<int> v)
{
    int n = v.size();
    vector<int> first;
    for (int i = 0; i < n / 2; i++)
    {
        first.push_back(v[i]);
    }
    return median(first);
}
float quartile3(vector<int> v)
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
    return median(last);
}
int main()
{
    ifstream in("6input.csv");
    if (!in.is_open())
    {
        cout << "Couldn't open file";
        exit(0);
    }
    ofstream out("exp6_output.csv");
    int i = 0;
    string line, mark;
    vector<int> arr;
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
    out << "Minimum value: "
        << "," << arr[0] << "\n";
    out << "Quartile1 value: "
        << "," << quartile1(arr) << "\n";
    out << "Median value: "
        << "," << median(arr) << "\n";
    out << "Quartile3 value: "
        << "," << quartile3(arr) << "\n";
    out << "Maximum value: "
        << "," << arr[n - 1] << "\n";
    cout << "Minimum value is " << arr[0] << endl;
    cout << "Q1: " << quartile1(arr) << endl;
    cout << "Median: " << median(arr) << endl;
    cout << "Q3: " << quartile3(arr) << endl;
    cout << "Maximum value is " << arr[n - 1] << endl;
    return 0;
}