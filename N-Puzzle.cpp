#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 3; // Size of the puzzle (3x3 in this case)
const int GOAL_STATE[] = {1, 2, 3, 4, 5, 6, 7, 8, 0}; // Goal state for a 3x3 puzzle

// Structure to represent a puzzle state
struct PuzzleState {
    vector<int> state;
    int emptyIndex; // Index of the empty tile (0)
    int cost; // Heuristic cost (Manhattan distance)
    
    PuzzleState(vector<int> s, int emptyIdx, int hCost) 
        : state(s), emptyIndex(emptyIdx), cost(hCost) {}

    // Comparator for priority queue to prioritize nodes with lower cost (Manhattan distance)
    bool operator>(const PuzzleState& other) const {
        return cost > other.cost; // We want the priority queue to prioritize nodes with smaller cost
    }
};

// Manhattan distance heuristic function
int getManhattanDistance(const vector<int>& state) {
    int dist = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] != 0) {
            int goalRow = (state[i] - 1) / N;
            int goalCol = (state[i] - 1) % N;
            int currentRow = i / N;
            int currentCol = i % N;
            dist += abs(currentRow - goalRow) + abs(currentCol - goalCol);
        }
    }
    return dist;
}

// Get the possible moves (up, down, left, right) from a state
vector<vector<int>> getNeighbors(const vector<int>& state, int emptyIndex) {
    vector<vector<int>> neighbors;
    int row = emptyIndex / N;
    int col = emptyIndex % N;
    
    // Directions: up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (auto dir : directions) {
        int newRow = row + dir.first;
        int newCol = col + dir.second;
        
        // Check if the new position is within bounds
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
            int newIndex = newRow * N + newCol;
            vector<int> newState = state;
            swap(newState[emptyIndex], newState[newIndex]);
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// Custom function to convert vector to string
string vectorToString(const vector<int>& state) {
    string str = "";
    for (int num : state) {
        str += to_string(num) + " ";
    }
    return str;
}

// Perform Best-First Search to find the solution
bool bestFirstSearch(vector<int> initialState) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> openList;
    unordered_set<string> visited;
    
    int emptyIndex = find(initialState.begin(), initialState.end(), 0) - initialState.begin();
    int h = getManhattanDistance(initialState);
    
    PuzzleState startState(initialState, emptyIndex, h);
    openList.push(startState);
    
    visited.insert(vectorToString(initialState)); // Convert the vector to string to store in visited set
    
    while (!openList.empty()) {
        PuzzleState currentState = openList.top();
        openList.pop();
        
        // Check if the current state is the goal state
        if (currentState.cost == 0) {
            cout << "Puzzle solved!" << endl;
            return true;
        }
        
        // Generate all possible moves (neighbors)
        vector<vector<int>> neighbors = getNeighbors(currentState.state, currentState.emptyIndex);
        
        for (auto& neighbor : neighbors) {
            string neighborStr = vectorToString(neighbor); // Convert the neighbor state to string
            
            // Skip the state if it has already been visited
            if (visited.find(neighborStr) != visited.end()) {
                continue;
            }
            
            visited.insert(neighborStr);
            int newEmptyIndex = find(neighbor.begin(), neighbor.end(), 0) - neighbor.begin();
            int newCost = getManhattanDistance(neighbor);
            
            // Create the new puzzle state and add to the open list
            PuzzleState nextState(neighbor, newEmptyIndex, newCost);
            openList.push(nextState);
        }
    }
    
    return false;
}

int main() {
    vector<int> initialState = {8, 1, 2, 0, 4, 3, 7, 6, 5}; // An initial scrambled state of the puzzle
    
    cout << "Initial state:" << endl;
    for (int i = 0; i < N * N; i++) {
        cout << initialState[i] << " ";
        if (i % N == N - 1) cout << endl;
    }

    if (!bestFirstSearch(initialState)) {
        cout << "No solution found!" << endl;
    }

    return 0;
}
