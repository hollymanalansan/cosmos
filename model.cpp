#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Coord {
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc)); // Push the starting coordinate onto the stack
    maze[sr][sc] = 'X'; // Mark the starting position as visited

    while (!coordStack.empty()) {
        Coord current = coordStack.top(); // Get the current coordinate
        coordStack.pop(); // Remove it from the stack

        int r = current.r();
        int c = current.c();

        // Check if we've reached the ending coordinate
        if (r == er && c == ec)
            return true;

        // Check each direction: NORTH, WEST, SOUTH, EAST
        if (maze[r - 1][c] == '.') { // Move NORTH
            coordStack.push(Coord(r - 1, c)); // Push the new coordinate onto the stack
            maze[r - 1][c] = 'X'; // Mark the new position as visited
        }
        if (maze[r][c - 1] == '.') { // Move WEST
            coordStack.push(Coord(r, c - 1)); // Push the new coordinate onto the stack
            maze[r][c - 1] = 'X'; // Mark the new position as visited
        }
        if (maze[r + 1][c] == '.') { // Move SOUTH
            coordStack.push(Coord(r + 1, c)); // Push the new coordinate onto the stack
            maze[r + 1][c] = 'X'; // Mark the new position as visited
        }
        if (maze[r][c + 1] == '.') { // Move EAST
            coordStack.push(Coord(r, c + 1)); // Push the new coordinate onto the stack
            maze[r][c + 1] = 'X'; // Mark the new position as visited
        }
    }

    // If the loop finishes without finding a path
    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XXXXX.X.XX",
        "X...X.X..X",
        "X.X...X..X",
        "X.XXX.XXXX",
        "XXX....X.X",
        "X.XX.XXX.X",
        "X....X...X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 6, 5, 1, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

    return 0;
}

