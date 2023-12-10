#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string line, word;
    ifstream file("13input.csv");
    string day, outlook, three, four, five, six;
    map<string, double> parent;
    map<string, map<string, map<string, double>>> child;
    int count = 0;
    vector<string> title;
    if (file.is_open())
    {
        int i = 0;
        while (file >> line)
        {
            stringstream str(line);
            if (i == 0)
            {
                string heading;
                while (getline(str, heading, ','))
                {
                    title.push_back(heading);
                }
                i++;
                continue;
            }
            vector<string> columns;
            while (getline(str, day, ','))
            {
                columns.push_back(day);
            }
            int n = columns.size();
            parent[columns[n - 1]]++;
            for (int i = 1; i < n - 1; i++)
            {

                child[title[i]][columns[i]][columns[n - 1]]++;
            }
            count++;
        }
        vector<string> resultclass;
        for (auto it : parent)
        {
            resultclass.push_back(it.first);
        }
        vector<double> output(resultclass.size(), 1);
        for (auto it : child)
        {
            string input;
        again:
            cout << "Enter " << it.first << " condition \n";
            cin >> input;
            auto curr = child[it.first].find(input);
            if (curr == child[it.first].end())
            {
                cout << "no match\n";
                goto again;
            }
            for (int i = 0; i < resultclass.size(); i++)
            {
                cout << child[it.first][input][resultclass[i]] << " / " <<

                    parent[resultclass[i]] << endl;

                double val = child[it.first][input][resultclass[i]] /

                             parent[resultclass[i]];
                output[i] *= val;
                cout << output[i] << endl;
            }
        }
        for (int i = 0; i < resultclass.size(); i++)
        {
            output[i] *= parent[resultclass[i]] / count;
        }
        double sum = accumulate(output.begin(), output.end(), 0.0f);
        cout << "sum " << sum << endl;
        cout << "output---------" << endl;
        for (int i = 0; i < resultclass.size(); i++)
        {
            cout << resultclass[i] << " " << output[i] << endl;
            cout << "Percentage " << (output[i] / sum) * 100 << endl;
        }
    }

    else
    {
        cout << "Could not open the file\n";
    }
    return 0;
}