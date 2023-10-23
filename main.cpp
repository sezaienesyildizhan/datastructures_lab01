#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

/* DATA STRUCTURES PROJECT GROUP:
   152120211042 Sezai Enes YILDIZHAN
   152120211053 Mehmet Ayberk GÜNEŞ
   
   Projeyi birlikte oturarak ve birlikte kaynak araştırması yaparak tamamladık.

   Geçtiğimiz yıl Programming dersinde vector ve string library'lerini kullanmayı
   öğrenmediğimizden kaynaklı olarak internetten (stackoverflow, geeksforgeeks vb.)
   yardım aldığımız kısımlar oldu.
   
   Fonksiyonları, aşamaları commentlerle açıkladık. İngilizce kullanımına özen gösterdik.
   
   Projemizi tamamlayıp github'a git kullanarak pushladık.

   Teşekkür ederiz, saygılarımızla. 
*/

// Define a struct called Blob to store information about a blob.
struct Blob {
    int pixels;     // Number of pixels in the blob
    double sumRow;  // Sum of row coordinates of pixels in the blob
    double sumCol;  // Sum of column coordinates of pixels in the blob
};

// Function to recursively search for a blob.
void recursive_searching_function(vector<vector<char> >& matrix, int row, int col, Blob& blob) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Base case: if out of bounds or not part of the blob, return.
    if (row < 0 || col < 0 || row >= rows || col >= cols || matrix[row][col] != 'x') {
        return;
    }

    matrix[row][col] = 'v'; // Mark as visited

    blob.pixels++;
    blob.sumRow += row;
    blob.sumCol += col;

    // Recursive calls to explore adjacent pixels.
    recursive_searching_function(matrix, row + 1, col, blob); // Down
    recursive_searching_function(matrix, row - 1, col, blob); // Up
    recursive_searching_function(matrix, row, col + 1, blob); // Right
    recursive_searching_function(matrix, row, col - 1, blob); // Left
}

int main() {
    string filename;

    cout << "Enter the filename: ";
    cin >> filename;

    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore(); // Ignore the newline character after cols

    // Create a matrix to store the blob data.
    vector<vector<char> > matrix(rows, vector<char>(cols));

    // Populate the matrix from the file.
    for (int i = 0; i < rows; ++i) {
        string line;
        getline(file, line);
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = line[j];
        }
    }

    file.close();

    // Display the input matrix.
    cout << "Input Matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    // Display table headers.
    cout << setw(3) << setfill('-') << '+' << setw(14) << '+' << setw(9) << '+' << setw(12) << '+' << setw(13) << '+' << endl;
    cout << setw(3) << setfill(' ') << '|' << setw(13) << " BLOB " << '|' << setw(8) << "NoOfPixels" << '|' << setw(11) << "CoM Row" << '|' << setw(12) << "CoM Column" << '|' << endl;
    cout << setw(3) << setfill('-') << '+' << setw(14) << '+' << setw(9) << '+' << setw(12) << '+' << setw(13) << '+' << endl;

    int blob_counter = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 'x') {
                Blob blob = { 0, 0.0, 0.0 };
                recursive_searching_function(matrix, i, j, blob);
                blob_counter++;

                double centerRow = blob.sumRow / blob.pixels;
                double centerCol = blob.sumCol / blob.pixels;

                // Display blob information.
                cout << '|' << setw(14) << blob_counter << '|' << setw(8) << blob.pixels << '|' << setw(11) << fixed << setprecision(2) << centerRow << '|' << setw(12) << centerCol << '|' << endl;
            }
        }
    }

    // Display table footer.
    cout << setw(3) << setfill('-') << '+' << setw(14) << '+' << setw(9) << '+' << setw(12) << '+' << setw(13) << '+' << endl;

    return 0;
}
