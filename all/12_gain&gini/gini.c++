#include <bits/stdc++.h>
using namespace std;

// Global variables to store data and results
vector<string> sub_classes;                  // Subclasses for analysis
map<string, int> mainClass;                  // Count of main class values (e.g., "Yes" and "No")
map<string, unordered_set<string>> dist_val; // Distinct values for each subclass
map<string, int> dist_val_count;             // Count of distinct values
map<string, map<string, int>> val_count;     // Count of values for each subclass

// Variables to keep track of minimum Gini index and selected root
double minGini = DBL_MAX;
string root = "null";

// Output file stream
ofstream fw("gini_output.csv", ios::out);

// Function to calculate the Gini index and select the root
void calculateGini(string subClass, double mainC_gini)
{
    double totR = mainClass["Yes"] + mainClass["No"]; // Total count of main class values

    double ent = 0; // Initialize Gini entropy

    // Calculate Gini index for the given subclass
    for (auto dv : dist_val[subClass])
    {
        double tR = dist_val_count[dv];         // Total count for the distinct value
        double pR = val_count[subClass]["Yes"]; // Count of "Yes" in the subclass
        double nR = val_count[subClass]["No"];  // Count of "No" in the subclass

        ent += (tR / totR) * (1 - (pR / tR) * (pR / tR) - (nR / tR) * (nR / tR));
    }

    double gini = ent; // Final Gini index

    // Output the Gini index for the subclass
    cout << fixed << setprecision(4); // Set precision to 4 decimal places
    cout << "Gini Index ( " << subClass << "| playGame ) : " << gini << "\n\n";
    fw << fixed << setprecision(4); // Set precision to 4 decimal places in the output file
    fw << "Gini Index ( " << subClass << "| playGame )," << gini << "\n";

    // Check if the current Gini index is the minimum
    if (gini < minGini)
    {
        minGini = gini;
        root = subClass; // Update the root with the minimum Gini index
    }
}

int main()
{
    // Open and read the input file
    ifstream file("gain_input.csv");
    string line;

    if (!file.is_open())
    {
        cerr << "Error in opening the input file." << endl;
        return -1;
    }

    int j = 0;                      // Line counter
    string main_class = "playgame"; // Main class attribute name

    while (getline(file, line))
    {
        stringstream str(line);

        string day, outlook, temp, humidity, wind, playGame;
        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playGame, ',');

        if (j == 0)
        {
            j++;
            sub_classes.push_back(day);
            sub_classes.push_back(outlook);
            sub_classes.push_back(temp);
            sub_classes.push_back(humidity);
            sub_classes.push_back(wind);
            continue;
        }

        // Store data for calculations
        dist_val["day"].insert(day);
        dist_val["outlook"].insert(outlook);
        dist_val["temp"].insert(temp);
        dist_val["humidity"].insert(humidity);
        dist_val["wind"].insert(wind);

        mainClass[playGame]++; // Update the count for the main class value

        dist_val_count[day]++; // Update the count for the distinct values
        dist_val_count[outlook]++;
        dist_val_count[temp]++;
        dist_val_count[humidity]++;
        dist_val_count[wind]++;

        val_count[day][playGame]++; // Update the count for values in the subclasses
        val_count[outlook][playGame]++;
        val_count[temp][playGame]++;
        val_count[humidity][playGame]++;
        val_count[wind][playGame]++;
    }

    // Calculate Gini index for the main class
    double posR = mainClass["Yes"];
    double negR = mainClass["No"];
    double totR = posR + negR;

    double mainC_gini = 1 - ((posR / totR) * (posR / totR) + (negR / totR) * (negR / totR));

    // Output the Gini index for the main class
    cout << fixed << setprecision(4); // Set precision to 4 decimal places
    cout << "Main Class Gini Index : " << mainC_gini << "\n";

    // Calculate and output the Gini index for each subclass
    for (int i = 1; i < 5; i++)
    {
        calculateGini(sub_classes[i], mainC_gini);
    }

    // Output the selected root with the minimum Gini index
    cout << "The selected root for splitting is: " << root << " (Minimum Gini Index)"
         << "\n";
    fw << fixed << setprecision(4); // Set precision to 4 decimal places in the output file
    fw << "The selected root for splitting is: " << root << " (Minimum Gini Index)"
       << "\n";

    return 0;
}