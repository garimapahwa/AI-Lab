#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Structure to represent a point (city) with x and y coordinates
struct Point {
    double x, y;
};

// Function to calculate the Euclidean distance between two points
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Function to find the nearest neighbor of a given city
int findNearestNeighbor(const vector<Point>& cities, vector<bool>& visited, int currentCity) {
    int nearestNeighbor = -1;
    double minDistance = numeric_limits<double>::max();

    for (int i = 0; i < cities.size(); ++i) {
        if (!visited[i] && i != currentCity) {
            double dist = distance(cities[currentCity], cities[i]);
            if (dist < minDistance) {
                minDistance = dist;
                nearestNeighbor = i;
            }
        }
    }

    return nearestNeighbor;
}

// Function to solve TSP using Nearest Neighbor heuristic
vector<int> solveTSP(const vector<Point>& cities) {
    int numCities = cities.size();
    vector<bool> visited(numCities, false);
    vector<int> tour;
    
    // Start from the first city
    int currentCity = 0;
    tour.push_back(currentCity);
    visited[currentCity] = true;
    
    // Find the nearest neighbor and add it to the tour until all cities are visited
    for (int i = 1; i < numCities; ++i) {
        int nearestNeighbor = findNearestNeighbor(cities, visited, currentCity);
        tour.push_back(nearestNeighbor);
        visited[nearestNeighbor] = true;
        currentCity = nearestNeighbor;
    }
    
    // Return to the starting city to complete the tour
    tour.push_back(tour[0]);
    
    return tour;
}

int main() {
    // Example cities (you can replace these with your own data)
    vector<Point> cities = {{0, 0}, {2, 4}, {3, 1}, {5, 3}, {6, 6}};

    vector<int> tour = solveTSP(cities);

    cout << "Optimal Tour Order: ";
    for (int city : tour) {
        cout << city << " ";
    }
    
    double totalDistance = 0.0;
    for (int i = 1; i < tour.size(); ++i) {
        totalDistance += distance(cities[tour[i - 1]], cities[tour[i]]);
    }
    
    cout << "\nTotal Distance: " << totalDistance << endl;

    return 0;
}
