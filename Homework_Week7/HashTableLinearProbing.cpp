#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct HashTableLinearProbing {

    int size;
    vector<string> keys;
    vector<int> values;

    /**
     * Hàm tính toán hash.
     * @param key Khóa cần truyền vào
     * @return giá trị hash của key
     */
    int hashFunction(const string &key) {
        int hash = 0; //Ban đầu: Hash = 0
        for (char c : key) {
            hash = (hash * 31 + c) % size; //Chọn 31 vì là số nguyên tố nhỏ, tránh va chạm nhiều
        }
        return hash;
    }

    //CONSTRUCTOR - Giả sử bảng băm có kích cỡ mặc định là 10
    HashTableLinearProbing(int s = 10) {
        size = s;
        keys.resize(size, "");
        values.resize(size, 0);
    }

    /**
     * Chèn một cặp (k, v) vào Hash Table (Bảng băm) hiện tại.
     * @param key khóa của cặp
     * @param value giá trị của cặp
     * @return true nếu chèn thành công, false nếu bảng băm đã đầy
     */
    bool insert(const string &key, int value) {

        cout << "insert(" << key << ", " << value << "): ";

        //Dùng công thức băm để tính index
        int index = hashFunction(key);
        int startIndex = index;

        //Cho index chạy một vòng
        while (!keys[index].empty() && keys[index] != key) {
            index = (index + 1) % size;

            //Nếu index trùng với điểm bắt đầu => Báo đầy
            if (index == startIndex) {
                cout << "FAILED - The hash table is full!" << endl;
                return false;
            }
        }

        //Chèn cặp (k, v) vào nếu keys[index] trống hoặc keys[index] trùng với key cần chèn
        //Lưu ý: Cặp (k ,v) mới sẽ ghi đè cặp (k, v) cũ nếu trùng key
        keys[index] = key;
        values[index] = value;
        cout << "OK" << endl;
        return true;
    }

    /**
     * Tìm kiếm giá trị tương ứng với key đưa ra.
     * @param key khóa muốn tìm giá trị của nó
     * @return giá trị (value) tương ứng với key, INT_MIN nếu không tìm thấy
     */
    int search(const string &key) {

        cout << "search(" << key << "): ";

        //Chọn index bằng hàm băm
        int index = hashFunction(key);
        int startIndex = index;

        //Cho index chạy một vòng bắt đầu từ index bắt đầu - StartIndex
        while (!keys[index].empty()) {

            //Tìm thấy => Trả giá trị tương ứng
            if (keys[index] == key) {
                cout << values[index] << " - OK" << endl;
                return values[index];
            }

            //Dịch sang cặp (k,v) tiếp theo
            index = (index + 1) % size;

            //Nếu trùng với điểm bắt đầu => Break
            if (index == startIndex) {
                break;
            }
        }

        //Nếu không tìm được => Trả INT_MIN
        cout << "FAILED - Cannot find the value!" << endl;
        return INT_MIN;
    }

    /**
     * Hàm in bảng băm hiện tại.
     */
    void display() {
        for (int i = 0; i < size; i++) {
            if (keys[i].empty())
                cout << i << ": [Empty]" << endl;
            else
                cout << i << ": " << keys[i] << " -> " << values[i] << endl;
        }
    }
};

// === Ví dụ chạy thử ===
int main() {
    HashTableLinearProbing ht(5);
    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("grape", 30);
    ht.insert("orange", 40);

    ht.display();

    return 0;
}