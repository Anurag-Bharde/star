#include <bits/stdc++.h>
using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos) {
        return str;
    }
    return str.substr(first, (last - first + 1));
}

int main() {
    ifstream inputFile("5input.csv");

    if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line); // Skip the header line

    map<pair<string, string>, double> mp;
    unordered_map<string, double> row;
    unordered_map<string, double> col;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        char delimiter = ',';
        size_t ind = 0;
        string classes, place;
        double cnt;

        while (getline(ss, token, delimiter)) {
            if (ind == 0) {
                classes = trim(token);
            } else if (ind == 1) {
                place = trim(token);
            } else {
                cnt = stod(trim(token));
            }
            ind++;
        }

        mp[{classes, place}] = cnt;
        row[classes] += cnt;
        col[place] += cnt;
    }

    inputFile.close();

    ofstream outputFile("output5.csv");
    outputFile << "Class,WorkPlace,t-weight,d-weight" << endl;

    for (auto it : mp) {
        string rw = it.first.first;
        string cl = it.first.second;
        double val = it.second;
        double twg = (val / row[rw]) * 100;
        double dwg = (val / col[cl]) * 100;

        cout << rw << " " << cl << " " << twg << " " << dwg << endl;
        outputFile << rw << "," << cl << "," << twg << "%," << dwg << "%" << endl;
    }

    mp.clear();
    double tot = 0;

    for (auto it : row) {
        mp[{it.first, "Total"}] = it.second;
        tot += it.second;
    }

    row["Total"] = tot;
    tot = 0;

    for (auto it : col) {
        mp[{"Total", it.first}] = it.second;
        tot += it.second;
    }

    col["Total"] = tot;

    for (auto it : mp) {
        string rw = it.first.first;
        string cl = it.first.second;
        double val = it.second;
        double twg = (val / row[rw]) * 100;
        double dwg = (val / col[cl]) * 100;

        cout << rw << " " << cl << " " << twg << " " << dwg << endl;
        outputFile << rw << "," << cl << "," << twg << "%," << dwg << "%" << endl;
    }

    outputFile.close();

    return 0;
}
