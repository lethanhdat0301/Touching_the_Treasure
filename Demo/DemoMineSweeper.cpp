#include <bits/stdc++.h>

using namespace std;

char a[9][9];

int main() {
    srand(time(0));

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            a[i][j] = '-';
        }
    }

    set<pair<int, int>> positions;
    while(positions.size() < 10) {
        int row = rand() % 9;
        int col = rand() % 9;
        positions.insert({row,col});
    }

    for(const auto& pos: positions){
        cout << pos.first << " " << pos.second << endl;
    }

    cout << "  ";
    for(int i = 0; i < 9; i++) {
        cout << i << " ";
    }
    cout << endl;

    for(int i = 0; i < 9; i++) {
        cout << i << " ";
        for(int j = 0; j < 9; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }



    bool check = true;

    while(check){
        int m,n;
        cout << "Nhap vao: ";
        cin >> m >> n;

        for(const auto& pos: positions){
        if(pos.first == m && pos.second == n) check= false;
        }

        if(check == false) {
            cout <<"You lose!" << endl;
        } else {
            int count = 0;

            int rowOffset[] = {-1, -1, -1, 0, 1, 1, 1, 0};
            int colOffset[] = {-1, 0, 1, 1, 1, 0, -1, -1};

             for (int k = 0; k < 8; k++) {
                int newRow = m + rowOffset[k];
                int newCol = n + colOffset[k];
                for(const auto& pos: positions){
                    if(pos.first == newRow && pos.second == newCol) count++;
                }
             }

            a[m][n] = '0' + count;
        }

        //Update
        cout << "  ";
        for(int i = 0; i < 9; i++) {
            cout << i << " ";
        }
        cout << endl;

        for(int i = 0; i < 9; i++) {
            cout << i << " ";
            for(int j = 0; j < 9; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }


    }



    return 0;
}


/*#include <bits/stdc++.h>

using namespace std;

const int SIZE = 9;
char a[SIZE][SIZE];

// Hàm đếm số lượng bom xung quanh vị trí (row, col)
int countBomb(int row, int col, char bom) {
    int count = 0;
    int rowOffset[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int colOffset[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int k = 0; k < 8; k++) {
        int newRow = row + rowOffset[k];
        int newCol = col + colOffset[k];

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
            if (a[newRow][newCol] == bom) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    srand(time(0));

    // Khởi tạo mảng với giá trị '-'
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            a[i][j] = '-';
        }
    }

    // Đặt bom tại các vị trí ngẫu nhiên
    set<pair<int, int>> positions;
    while(positions.size() < 10) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        positions.insert({row, col});
    }

    // Gán giá trị bom vào các vị trí ngẫu nhiên
    for(const auto& pos: positions){
        a[pos.first][pos.second] = 'b';
    }

    // In mảng ra màn hình
    cout << "  ";
    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < SIZE; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // Nhập vị trí người dùng muốn kiểm tra
    int m, n;
    cout << "Nhap vao vi tri (m, n): ";
    cin >> m >> n;

    // Kiểm tra nếu vị trí đó có bom không
    if(positions.find({m, n}) != positions.end()) {
        cout << "You lose!" << endl;
    } else {
        // Đếm số bom xung quanh vị trí nhập
        a[m][n] = '0' + countBomb(m, n, 'b');
        cout << "Number of bombs around (" << m << ", " << n << "): " << a[m][n] << endl;
    }

    // In lại mảng sau khi cập nhật
    cout << "Updated board:" << endl;
    cout << "  ";
    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < SIZE; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}*/
