#include <iostream>
#include <vector>

using namespace std;

struct Node {
    string key;
    int value;
    Node* next;

    // CONSTRUCTOR
    Node(string k, int v) : key(k), value(v), next(nullptr) {}
};

struct LinkedList {
    Node* head = nullptr;

    /**
     * @brief thêm một cặp (k, v) vào LinkedList.
     * 
     * Các bước thực hiện:
     * - Sử dựng node tạm thời để tìm kiếm xem key truyền vào đã tồn tại chưa,
     * nếu đã tồn tại thì update lại giá trị
     * - Nếu không thì tạo node mới và thêm vào đầu LinkedList (insertFirst)
     * 
     * @param key Khóa của node cần thêm / update
     * @param value giá trị của node cần thêm / update
     * 
     * @return true nếu thêm node mới, false nếu update node đã tồn tại
     */
    bool insert(const string& key, int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = value; // Trùng key => Update value
                cout << "Updated (" << key << ", " << value << ")\n";
                return false; // Đã tồn tại, update giá trị
            }
            temp = temp->next;
        }

        // Nếu chưa có thì thêm đầu danh sách
        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;

        cout << "Inserted (" << key << ", " << value << ")\n";
        return true; // Chèn mới
    }

    /**
     * @brief tìm kiếm giá trị của key được truyền vào.
     * 
     * Các bước thực hiện:
     * - Tạo một node tàm thời chỉ đến head, cho di chuyển sang node tiếp theo
     * - Nếu tìm thấy thì trả về giá trị đó, không thì trả về một số nào đó
     * 
     * @param key Khóa cần truyền vào để tìm giá trị tương ứng
     * 
     * @return giá trị của key đó, INT_MIN nếu không tìm thấy
     */
    int find(const string& key) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->key == key)
                return temp->value;
            temp = temp->next;
        }
        return INT_MIN;
    }

    /**
     * @brief Xóa một node dựa vào key đã truyền vào.
     * 
     * Các bước thực hiện:
     * - Tạo 2 node: temp chỉ tới head, prev để lưu node trước temp
     * - Cho di chuyển temp sang node tiếp theo và cập nhật node prev
     * - Nếu tìm thấy key thì:
     * + Nối node tiếp theo của prev là node tiếp theo của temp
     * + Xóa node temp
     * 
     * @param key Khóa của node cần xóa
     * 
     * @return true nếu xóa thành công, false nếu không tìm thấy node chưa key cần tìm
     * 
     */
    bool remove(const string& key) {
        Node* temp = head;
        Node* prev = nullptr;
        int delValue = 0;

        while (temp != nullptr) {
            if (temp->key == key) {

                // Nếu key cần xóa nằm ngay ở đầu
                if (prev == nullptr)
                    head = temp->next;
                else
                    prev->next = temp->next;

                delValue = temp->value;
                delete temp;

                //Thông báo xóa thành công
                cout << "Removed node: (" << key << ", " << delValue << ")" << endl;
                return true;
            }

            prev = temp;
            temp = temp->next;
        }

        //Nếu không tìm thấy key
        cout << "Key not found: " << key << endl;
        return false;
    }

    /**
     * Hàm in toàn bộ danh sách của LinkedList
     */
    void print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->key << ": " << temp->value << "] -> ";
            temp = temp->next;
        }
        cout << "NULL";
    }
};