#include <iostream>
using namespace std;

// Function to perform DFS to solve the water jug problem
bool solve(int x, int y, int target) {
    // Base case: If we reach the target amount, return true
    if (x == target || y == target) {
        cout << "Solution found: (" << x << ", " << y << ")" << endl;
        return true;
    }

    // Recursive cases
    bool result = false;

    // Pour from jug X to jug Y
    if (x > 0 && y < target) {
        int pour = min(x, target - y);
        result |= solve(x - pour, y + pour, target);
    }

    // Pour from jug Y to jug X
    if (y > 0 && x < target) {
        int pour = min(y, target - x);
        result |= solve(x + pour, y - pour, target);
    }

    // Empty jug X
    if (x > 0) {
        result |= solve(0, y, target);
    }

    // Empty jug Y
    if (y > 0) {
        result |= solve(x, 0, target);
    }

    // Fill jug X
    if (x < target) {
        result |= solve(x + y, y, target);
    }

    // Fill jug Y
    if (y < target) {
        result |= solve(x, x + y, target);
    }

    return result;
}

int main() {
    int capacityX, capacityY, target;
    cout << "Enter the capacity of jug X: ";
    cin >> capacityX;
    cout << "Enter the capacity of jug Y: ";
    cin >> capacityY;
    cout << "Enter the target amount of water: ";
    cin >> target;

    if (!solve(0, 0, target)) {
        cout << "No solution found!" << endl;
    }

    return 0;
}
