#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void calculateMinMax(ifstream &inputFile, double &minValue, double &maxValue)
{
    double currentValue;
    inputFile >> currentValue;
    while (inputFile)
    {
        if (currentValue > maxValue)
            maxValue = currentValue;
        if (currentValue < minValue)
            minValue = currentValue;
        inputFile >> currentValue;
    }
}

void MinMax(ifstream &inputFile, ofstream &outputFile, double oldMin, double oldMax, double newMin, double newMax)
{
    outputFile << "Original Data,"
               << "Normalized Data"
               << "\n";

    double currentValue;
    inputFile >> currentValue;
    while (inputFile)
    {
        double previousValue = currentValue;
        currentValue = (((currentValue - oldMin) / (oldMax - oldMin)) * (newMax - newMin)) + newMin;
        outputFile << previousValue << "," << currentValue << "\n";
        inputFile >> currentValue;
    }
}

void zscore(ifstream &inputFile, ofstream &outputFile)
{
    double sum = 0.0, count = 0.0, squareSum = 0.0, mean, standardDeviation;
    double currentValue;

    while (inputFile)
    {
        sum += currentValue;
        count++;
        inputFile >> currentValue;
    }
    mean = sum / count;

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    while (inputFile)
    {
        squareSum += (currentValue - mean) * (currentValue - mean);
        inputFile >> currentValue;
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    standardDeviation = sqrt(squareSum / count);

 
    outputFile << "Original Data,"
               << "Normalized Data"
               << "\n";

    while (inputFile)
    {
        double prev = currentValue;
        currentValue = (currentValue - mean) / standardDeviation;
        outputFile << prev << "," << currentValue << endl;
        inputFile >> currentValue;
    }
}

int main()
{
    double currentValue, minValue, maxValue, newMinValue, newMaxValue;
    double sum, count, squareSum, mean, standardDeviation;

    ifstream inputFileMinMax("input_MinMax.csv");
    ifstream inputFileMinMax_2("input_MinMax.csv");
    ifstream inputFileZScore("input_Zscore.csv");

    int option;
    cout << "\nEnter an option: \n1. Min-Max Normalization \n2. Z-Score Normalization\nOption: ";
    cin >> option;

    ofstream outputFileMinMax("output_MinMax.csv", ios::app);
    ofstream outputFileZScore("output_ZScore.csv", ios::app);

    switch (option)
    {
    case 1: 
        if (!inputFileMinMax)
        {
            cout << "Error opening file, please try again.";
            exit(0);
        }
        calculateMinMax(inputFileMinMax, minValue, maxValue);
        cout << "Enter new minimum value: ";
        cin >> newMinValue;
        cout << "\nEnter new maximum value: ";
        cin >> newMaxValue;
        MinMax(inputFileMinMax_2, outputFileMinMax, minValue, maxValue, newMinValue, newMaxValue);
        break;

    case 2:
        if (!inputFileZScore)
        {
            cout << "Error opening file, please try again.";
            exit(0);
        }
        zscore(inputFileZScore, outputFileZScore);
        break;

    default:
        cout << "Invalid option";
    }

    return 0;
}