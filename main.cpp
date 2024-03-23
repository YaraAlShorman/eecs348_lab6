/*
Yara Al-Shorman
3041373
EECS 348 - Lab 6
This program performs a number of matrix operations on 2D arrays
by defining a number of functions
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// required functions
// function to read matrix size and 2 matrices from input file
int*** read_matrices(ifstream& file, int& N) {
    // read input matrix size (N)
    file >> N;
    // 
    int*** matrices = new int**[2];
    for (int i = 0; i < 2; i++) {
        matrices[i] = new int*[N];
        for (int j = 0; j < N; j++) {
            matrices[i][j] = new int[N];
            for (int k = 0; k < N; k++) {
                file >> matrices[i][j][k];
            }
        }
    }
    return matrices;
}

// function to print 2D NxN matrix
void print_matrix(int** A, const int & N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << A[i][j] << " ";
        }
        cout << endl;
    }

}

// function to add 2 matrices (A+B)
int** add_matrices(int** A, int** B, const int & N) {
    int** C = new int*[N];
    for (int i = 0; i < N; i++) {
        C[i] = new int[N];
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// function to multiply 2 matrices (A*B)
int** mult_matrices(int** A, int** B, const int & N) {
    int** C = new int*[N];
    for (int i = 0; i < N; i++) {
        C[i] = new int[N];
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;

}

// function to subtract 2 matrices (B-A)
int** sub_matrices(int** A, int** B, const int & N) {
    int** C = new int*[N];
    for (int i = 0; i < N; i++) {
        C[i] = new int[N];
        for (int j = 0; j < N; j++) {
            C[i][j] = B[i][j] - A[i][j];
        }
    }
    return C;
}

// function to update value in matrix
void update(int** A, int x, int row, int col) {
    A[row][col] = x;
}

// function to find max value in matrix
int max_value(int** A, const int & N) {
    int max = A[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] > max) max = A[i][j];
        }
    }
    return max;
}

// function to find transpose of matrix
int** transpose(int** A, const int & N) {
    int** C = new int*[N];
    for (int i = 0; i < N; i++) {
        C[i] = new int[N];
        for (int j = 0; j < N; j++) {
            C[i][j] = A[j][i];
        }
    }
    return C;
}

// lastly, function to deallocate arrays to prevent memory leaks
void deallocate_matrix(int** A, const int & N) {
    for (int i = 0; i < N; i++){
        delete[] A[i];
    }
    delete[] A;
}


int main() {
    string file_name;  // variable to hold filename
    int N;  // variable to hold input matrix size

    cout << "Enter filename: " << endl;
    cin >> file_name;
    ifstream file(file_name);
    
    if (!file.is_open()) {
        cerr << "Unable to open file: " << file_name << endl;
        return 1;
    }
    
    int*** matrices = read_matrices(file, N);
    
    file.close();

    int** A = matrices[0];
    int** B = matrices[1];
    
    // print A
    cout << "Matrix A" << endl;
    print_matrix(A, N);

    cout << endl;
    
    // print B
    cout << "Matrix B" << endl;
    print_matrix(B, N);
    
    cout << endl;

    // add A, B
    cout << "Result of A+B" << endl;
    int** C_add = add_matrices(A, B, N);
    print_matrix(C_add, N);
    
    cout << endl;
    
    // multiply A, B
    cout << "Result of A*B" << endl;
    int** C_mult = mult_matrices(A, B, N);
    print_matrix(C_mult, N);
    
    cout << endl;
    
    // subtract A, B
    cout << "Result of B-A" << endl;
    int** C_sub = sub_matrices(A, B, N);
    print_matrix(C_sub, N);
    
    cout << endl;

    // update A
    cout << "Updating A[2][1] to equal 0" << endl;
    update(A, 0, 2, 1);
    print_matrix(A, N);
    
    cout << endl;
    
    // get max value in B
    cout << "Finding max value in B" << endl;
    int max_val = max_value(B, N);
    cout << "Max value in matrix B is " << max_val << endl;
    
    cout << endl;
    
    // transpose A
    cout << "Result of transpose(A)" << endl;
    int** C_tr = transpose(A, N);
    print_matrix(C_tr, N);
    
    cout << endl;
    
    // cleaning up
    deallocate_matrix(A, N);
    deallocate_matrix(B, N);
    deallocate_matrix(C_add, N);
    deallocate_matrix(C_mult, N);
    deallocate_matrix(C_sub, N);
    deallocate_matrix(C_tr, N);
    
    return 0;
}
