#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

// Equal Frequency Binning
vector<vector<int>> equifreq(vector<int> arr1, int m)
{
  int a = arr1.size();
  int n = a / m;
  vector<vector<int>> bins;
  for (int i = 0; i < m; i++)
  {
    vector<int> bin;
    for (int j = i * n; j < (i + 1) * n; j++)
    {
      if (j >= a)
      {
        break;
      }
      bin.push_back(arr1[j]);
    }
    bins.push_back(bin);
  }
  return bins;
}

// Equal Width Binning
vector<vector<int>> equiwidth(vector<int> arr1, int m)
{
  int a = arr1.size();

  int max_ele = INT_MIN;
  int min_ele = INT_MAX;

  for (int i = 0; i < arr1.size(); i++)
  {
    max_ele = max(max_ele, arr1[i]);
    min_ele = min(min_ele, arr1[i]);
  }

  int w = (max_ele - min_ele) / m;
  int min1 = min_ele;

  vector<int> arr;
  for (int i = 0; i < m + 1; i++)
  {
    arr.push_back(min1 + w * i);
  }

  vector<vector<int>> arri;
  for (int i = 0; i < m; i++)
  {
    vector<int> temp;
    for (int j : arr1)
    {
      if (j >= arr[i] && j <= arr[i + 1])
      {
        temp.push_back(j);
      }
    }
    arri.push_back(temp);
  }
  return arri;
}

// Read data from CSV
vector<int> readCSV(string filename)
{
  ifstream inputFile(filename);
  vector<int> data;
  string line, value;
  while (getline(inputFile, line))
  {
    stringstream ss(line);
    while (getline(ss, value, ','))
    {
      data.push_back(stoi(value));
    }
  }
  inputFile.close();
  return data;
}

// Write binning outputs to CSV
void writeCSV(string filename, vector<vector<int>> bins)
{
  ofstream outputFile(filename);
  for (int i = 0; i < bins.size(); i++)
  {
    outputFile << "Bin " << i + 1 << ",";
    for (int num : bins[i])
    {
      outputFile << num << ",";
    }
    outputFile << "\n";
  }
  outputFile.close();
}

int main()
{
  vector<int> data = readCSV("input.csv");
  int m;

  int method;
  cout << "Choose binning method: " << endl;
  cout << "1. Equal Frequency Binning" << endl;
  cout << "2. Equal Width Binning" << endl;
  cout << "\nEnter method number: ";
  cin >> method;
  cout << "\nEnter number of bins: ";
  cin >> m;

  if (method == 1)
  {
    vector<vector<int>> freqBins = equifreq(data, m);
    writeCSV("output_equifreq.csv", freqBins);
  }
  else if (method == 2)
  {
    vector<vector<int>> widthBins = equiwidth(data, m);
    writeCSV("output_equiwidth.csv", widthBins);
  }
  else
  {
    cout << "Invalid method choice." << endl;
  }

  return 0;
}