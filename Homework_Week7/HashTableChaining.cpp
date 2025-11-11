#include <iostream>
#include <vector>
#include <string>

#include "BTVN_LinkedList.cpp"

using namespace std;

struct HashTableChaining {

    int size;
    vector<LinkedList> table;

    /**
     * @brief Hàm tính hash của một key.
     * 
     * Hash của một key có công thức là: (hash * 31 + c) % size, trong đó:
     * - hash: Hash hiện tại
     * - c: Giá trị ASCII của chữ cái đang tính
     * - size: Kích cỡ bảng
     * Chọn số 31 vì nó là số nguyên tố => Giảm Collision
     * 
     * @return hash của key đó
     */
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

    //CONSTRUCTOR MẶC ĐỊNH (Giả sử có 10 ô trống)
    HashTableChaining(int s = 10) {
        size = s;
        table.resize(size);
    }

    /**
     * @brief Thêm một cặp (k,v) vào bảng băm.
     * 
     * Tính hash (index) của key muốn thêm vào, sau đó gọi insert từ LinkedList
     * 
     * @return true nếu cặp (k, v) đó không trùng key, false nếu update cặp (k, v) trùng key
     */
    bool insert(const string& key, int value) {
        int index = hashFunction(key);
        return table[index].insert(key, value);
    }

    /**
     * @brief Xóa một cặp (k,v) trong bảng băm.
     * 
     * Tính hash (index) của key muốn xóa, sau đó gọi remove từ LinkedList
     * 
     * @return true nếu xóa thành công, false nếu không tìm thấy key
     */
    bool remove(const string& key) {
        int index = hashFunction(key);
        return table[index].remove(key);
    }

    /**
     * @brief Tìm kiếm value tương ứng với key truyền vào.
     * 
     * Tính hash (index) của key truyền vào, 
     * sau đó tìm giá trị của key bằng hàm find trong LinkedList
     * 
     * @return giá trị của key đó, INT_MIN nếu không tìm thấy key
     */
    int search(const string& key) {
        int index = hashFunction(key);
        return table[index].find(key);
    }

    /**
     * Hàm in bảng băm hiện tại.
     */
    void print() {
        cout << "\n=== Hash Table (Separate Chaining) ===\n";
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            table[i].print();
            cout << endl;
        }
    }

};

// TEST //
int main() {
    HashTableChaining ht(5);

    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("grape", 30);
    ht.insert("orange", 40);
    ht.insert("banana", 50); // cập nhật value

    ht.print();

    cout << "\nTìm 'apple': ";
    int val = ht.search("apple");
    if (val) cout << val << endl;
    else cout << "Không tìm thấy\n";

    ht.remove("grape");
    ht.print();

    return 0;
}