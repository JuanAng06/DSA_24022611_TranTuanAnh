#include "BTVN_List.cpp"

using namespace std;

struct Heap
{

    List list;
    bool isMinHeap;

    Heap(int capacity, bool minHeap = true) : list(capacity), isMinHeap(minHeap) {}

    //                                      --- Các thao tác chính trong heap ---

    // So sánh 2 số
    bool compare(int a, int b) {
        if (isMinHeap) {
            return a < b;
        }
        return a > b;
    }

    // Chèn giá trị
    bool insert(int value) {
        cout << "insert(" << value << "): ";

        // Nếu heap đầy
        if (list.isFull())
        {
            cout << "FAILED - The heap is full!" << endl;
            return false;
        }

        list.addLast(value);
        heapifyUp(list.getCount() - 1);

        cout << "OK!" << endl;
        return true;
    }

    //Lấy phần tử đầu và xóa nút đó
    int extractRoot() {

        //Nếu heap rỗng
        if (list.isEmpty()) {
            cout << "FAILED - The heap is empty!" << endl;
            return INT_MIN;
        }

        //Thực hiện thao tác lấy giá trị và heapifyDown
        int result = list.getFirst();

        swapElements(list.data[0], list.data[list.getCount() - 1]);
        list.deleteLast();

        //Phục hồi tính chất heap
        if (!list.isEmpty()) {
            heapifyDown(0);
        }

        cout << "OK - Extracted value: " << result << endl;
        return result;
    }

    // Lấy phần tử đầu
    int getRoot() {
        return list.getFirst();
    }

    // Kiểm tra xem heap có rỗng không
    bool isEmpty() {
        return list.isEmpty();
    }

    int size() {
        return list.getCount();
    }

    //                                      --- Xử lý sắp xếp ---

    // Swim (Nổi lên)
    void heapifyUp(int index)
    {
        while (index > 0) {

            //Tìm cha của nút con
            int parentTemp = parent(index);

            //Đổi vị trí cha với con và cập nhật lại index
            if (compare(list.data[index], list.data[parentTemp])) {
                swapElements(list.data[index], list.data[parentTemp]);
                index = parentTemp;
            }

            else {
                break; // Không cần swapElements nữa => Heapify xong
            }
        }
    }

    // Sink (Chìm xuống)
    void heapifyDown(int index) {
        while (true) {

            // Lấy index nút con bên trái và phải, đặt cha là index hiện tại
            int leftTemp = left(index);
            int rightTemp = right(index);
            int best = index;

            // Chọn con "tốt hơn" (nhỏ hơn hoặc lớn hơn tùy loại heap)
            if (leftTemp < list.getCount() && compare(list.data[leftTemp], list.data[best])) {
                best = leftTemp;
            }

            if (rightTemp < list.getCount() && compare(list.data[rightTemp], list.data[best])) {
                best = rightTemp;
            }

            // Nếu không còn cần hoán đổi => Dừng
            if (best == index) {
                break;
            }

            // Nếu cần hoán đổi => swapElements và tiếp tục từ vị trí mới
            swapElements(list.data[index], list.data[best]);
            index = best;
        }
}

    // Tráo 2 vị trí cho nhau
    void swapElements(int &i, int &j) {
        int temp = i;
        i = j;
        j = temp;
    }

    //                                      --- Hàm phụ trợ ---
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    //                                      --- Hàm in heap ---
    void printHeap() {
        cout << "Heap: ";
        for (int i = 0; i < list.getCount(); i++) {
            cout << list.data[i] << " ";
        }
        cout << endl;
    }
};

// === MAIN TEST ===
// int main() {
//     cout << "=== TEST MIN HEAP ===" << endl;
//     Heap minHeap(10, true);  // true = MinHeap

//     minHeap.insert(5);
//     minHeap.insert(3);
//     minHeap.insert(8);
//     minHeap.insert(1);
//     minHeap.insert(6);

//     minHeap.printHeap();

//     cout << "\nExtracting elements from MinHeap:\n";
//     while (!minHeap.isEmpty()) {
//         cout << "Extracted: " << minHeap.extractRoot() << endl;
//         minHeap.printHeap();
//     }

//     cout << "\n=== TEST MAX HEAP ===" << endl;
//     Heap maxHeap(10, false); // false = MaxHeap

//     maxHeap.insert(5);
//     maxHeap.insert(3);
//     maxHeap.insert(8);
//     maxHeap.insert(1);
//     maxHeap.insert(6);

//     maxHeap.printHeap();

//     cout << "\nExtracting elements from MaxHeap:\n";
//     while (!maxHeap.isEmpty()) {
//         cout << "Extracted: " << maxHeap.extractRoot() << endl;
//         maxHeap.printHeap();
//     }

//     return 0;
// }