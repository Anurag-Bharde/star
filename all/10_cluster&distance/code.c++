#include <bits/stdc++.h>
#include <limits>
using namespace std;

// Function to calculate the Euclidean distance between two points (x1, y1) and (x2, y2)
float distance(float x1, float y1, int x2, int y2)
{
    return sqrt(((float)x2 - x1) * ((float)x2 - x1) + ((float)y2 - y1) * ((float)y2 - y1));
}

int main()
{
    string line;
    int mid_point;
    string point, x, y;
    int i = 0;
    int val1;
    int val2;
    vector<pair<int, int>> v;

    // Open the input file for reading
    fstream in("cluster_input.csv", ios::in);

    // Check if the file was opened successfully
    if (!in.is_open())
    {
        cout << "Error: Unable to open the input file 'cluster_input.csv'." << endl;
        return -1;
    }

    // Read data from the CSV file line by line
    while (getline(in, line))
    {
        stringstream str(line);

        if (i == 0)
        {
            i++;
            continue; // Skip the first line (possibly a header).
        }

        // Parse the CSV line into variables point, x, and y
        getline(str, point, ',');
        getline(str, x, ',');
        getline(str, y, ',');

        val1 = stoi(x); // Convert x to an integer
        val2 = stoi(y); // Convert y to an integer

        v.push_back({val1, val2}); // Add the pair (val1, val2) to the vector v
    }

    int n = v.size();
    int x_sum = 0, y_sum = 0;

    // Calculate the sum of x and y coordinates
    for (int i = 0; i < v.size(); i++)
    {
        int first = v[i].first;
        int second = v[i].second;

        x_sum += first;
        y_sum += second;
    }

    // Calculate the coordinates of the midpoint (average)
    float mid_x = (float)x_sum / n;
    float mid_y = (float)y_sum / n;
    cout << "Midpoint of the data: (" << mid_x << "," << mid_y << ")" << endl;

    // Open the output file for writing
    ofstream out("cluster_output.csv");

    // Write the header for the output CSV file
    out << " , p1 ,p2 ,p3 ,p4,C";
    out << "\n";

    // Calculate the distances between all pairs of points
    for (int i = 0; i < v.size(); i++)
    {
        if (i < v.size())
            out << "p" << i + 1 << ",";

        for (int j = 0; j <= i; j++)
        {
            int f_x1 = v[i].first;
            int s_y1 = v[i].second;
            int f_x2 = v[j].first;
            int s_y2 = v[j].second;

            if (f_x1 == f_x2 && s_y1 == s_y2)
            {
                out << "0"
                    << ",";
                break;
            }
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            out << dis << ",";
        }
        out << "\n";
    }

    out << "C"
        << ",";

    // Variables for finding the nearest point to the center
    pair<int, int> p;
    int nearestPoint = 0;
    float x_new;
    float y_new;
    float nearestDistance = INT_MAX;

    // Calculate the distances of each point from the calculated midpoint
    for (int i = 0; i < v.size(); i++)
    {
        int first = v[i].first;
        int second = v[i].second;

        float d = distance(mid_x, mid_y, first, second);

        cout << "Distance of p" << i + 1 << " from the center: " << d << " units." << endl;

        if (nearestDistance > d)
        {
            nearestDistance = d;
            nearestPoint = i + 1;
            x_new = first;
            y_new = second;
        }

        out << d << ",";

        if (i == v.size() - 1)
            out << "0"
                << ",";
    }

    cout << "The nearest distance from the center is: " << nearestDistance << " units." << endl;
    cout << "The nearest point from the center is: "
         << "p" << nearestPoint << endl;
    out << ",";
    out << "\n";

    // New Center Calculation
    out << " , p1 ,p2 ,p3 ,p4";
    out << "\n";

    for (int i = 0; i < v.size(); i++)
    {
        if (i < v.size())
            out << "p" << i + 1 << ",";

        for (int j = 0; j <= i; j++)
        {
            int f_x1 = v[i].first;
            int s_y1 = v[i].second;
            int f_x2 = v[j].first;
            int s_y2 = v[j].second;

            if (f_x1 == f_x2 && s_y1 == s_y2)
            {
                out << "0"
                    << ",";
                break;
            }
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            out << dis << ",";
        }
        out << "\n";
    }

    out << "p" << nearestPoint << " (New Center)"
        << ",";

    // Calculate the distances of each point from the new center
    for (int i = 0; i < v.size(); i++)
    {
        int first = v[i].first;
        int second = v[i].second;

        float d = distance(x_new, y_new, first, second);

        cout << "Distance of p" << i + 1 << " from the new center (p" << nearestPoint << "): " << d << " units." << endl;

        out << d << ",";

        if (i == v.size() - 1)
            out << "0"
                << ",";
    }

    cout << "Results have been written to 'cluster_output.csv'." << endl;
    return 0;
}