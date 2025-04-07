#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Spreadsheet {
private:
    vector<vector<int>> grid;

    // Helper function to get cell value from grid
    int getCellValue(const string& cell) {
        int row = stoi(cell.substr(1)) - 1;  // Extract row index
        int col = cell[0] - 'A';  // Convert column letter to index
        return grid[row][col];  // Get value from grid
    }

public:
    Spreadsheet(int rows) : grid(rows, vector<int>(26, 0)) {}
    
    void setCell(const string& cell, int value) {
        int row = stoi(cell.substr(1)) - 1;
        int col = cell[0] - 'A';
        grid[row][col] = value;
    }
    
    void resetCell(const string& cell) {
        int row = stoi(cell.substr(1)) - 1;
        int col = cell[0] - 'A';
        grid[row][col] = 0;
    }

    int getValue(const string& formula) {
        if (formula[0] == '=') {
            stringstream ss(formula.substr(1));
            int sum = 0;
            string token;
            char op = '+';  // Default to addition

            while (getline(ss, token, '+')) {  // Split by '+'
                int value;
                if (isalpha(token[0])) {  // If it's a cell reference
                    value = getCellValue(token);
                } else {  // If it's a number
                    value = stoi(token);
                }
                sum += value;
            }
            return sum;
        }
        return stoi(formula);
    }
};

int main() {
    Spreadsheet spreadsheet(3);  
    
    cout << spreadsheet.getValue("=5+7") << "\n";  // 12
    spreadsheet.setCell("A1", 10);
    cout << spreadsheet.getValue("=A1+6") << "\n";  // 16
    spreadsheet.setCell("B2", 15);
    cout << spreadsheet.getValue("=A1+B2") << "\n";  // 25
    spreadsheet.resetCell("A1");
    cout << spreadsheet.getValue("=A1+B2") << "\n";  // 15
    
    return 0;
}
