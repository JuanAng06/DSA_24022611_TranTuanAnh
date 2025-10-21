#include "BTVN_List.cpp"

using namespace std;

struct Heap
{

    List list;
    bool isMinHeap;

    Heap(int capacity, bool minHeap = true) : list(capacity), isMinHeap(minHeap) {}

    //                                      --- Các thao tác chính trong heap ---

    /**
     * So sánh 2 số trong Heap.
     * 
     * @param a Số thứ nhất
     * @param b Số thứ hai
     * @return true nếu thỏa mãn điều kiện (Phụ thuộc vào isMinHeap), ngược lại false
     */
    bool compare(int a, int b) {
        if (isMinHeap) {
            return a < b;
        }
        return a > b;
    }

    /**
     * @brief Thêm một phần tử mới vào heap.
     *
     * Hàm sẽ thêm giá trị `value` vào vị trí cuối cùng trong danh sách,
     * sau đó thực hiện thao tác `heapifyUp()` để đảm bảo tính chất của heap.
     * Nếu heap đã đầy thì thao tác sẽ thất bại.
     *
     * @param value Giá trị cần chèn vào heap.
     * @return true Nếu chèn thành công.
     * @return false Nếu heap đã đầy.
     */
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

    /**
     * @brief Lấy và xóa phần tử gốc (root) của heap.
     *
     * Hàm sẽ lấy phần tử đầu tiên (root) trong heap, thay thế nó bằng phần tử cuối,
     * sau đó gọi `heapifyDown()` để khôi phục lại tính chất heap.
     * Nếu heap rỗng, hàm trả về `INT_MIN` và in thông báo lỗi.
     *
     * @return Giá trị của phần tử gốc nếu heap không rỗng, ngược lại là `INT_MIN`.
     */
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

    /**
     * @brief Lấy giá trị phần tử gốc (root) của heap mà không xóa nó.
     *
     * @return Giá trị phần tử gốc của heap.
     */
    int getRoot() {
        return list.getFirst();
    }

    /**
     * @brief Kiểm tra xem heap có rỗng hay không.
     *
     * @return true Nếu heap rỗng.
     * @return false Nếu heap có chứa phần tử.
     */
    bool isEmpty() {
        return list.isEmpty();
    }

    /**
     * @brief Lấy số lượng phần tử hiện có trong heap.
     *
     * @return Số phần tử trong heap.
     */
    int size() {
        return list.getCount();
    }

    // ------------------------------------------------------------
    //                   Xử lý sắp xếp Heap
    // ------------------------------------------------------------

    /**
     * @brief Thực hiện thao tác "nổi lên" (heapify-up hoặc swim) cho một nút.
     *
     * Hàm này được gọi sau khi thêm phần tử mới để đảm bảo tính chất của heap.
     * Nếu phần tử con "tốt hơn" (ví dụ: nhỏ hơn trong min-heap hoặc lớn hơn trong max-heap)
     * so với cha của nó, chúng sẽ được hoán đổi.
     *
     * @param index Vị trí của phần tử cần kiểm tra và di chuyển lên.
     */
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

    /**
     * @brief Thực hiện thao tác "chìm xuống" (heapify-down hoặc sink) cho một nút.
     *
     * Hàm này được gọi sau khi xóa phần tử gốc để khôi phục lại tính chất heap.
     * Nếu phần tử cha không còn duy trì tính chất heap (ví dụ nhỏ hơn/lớn hơn con),
     * nó sẽ được hoán đổi với con "tốt hơn" cho đến khi heap hợp lệ.
     *
     * @param index Vị trí của phần tử cần kiểm tra và di chuyển xuống.
     */
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

    //                                      --- Hàm phụ trợ ---

    // Tráo 2 phần tử
    void swapElements(int &i, int &j) {
        int temp = i;
        i = j;
        j = temp;
    }

    // Lấy index của nút cha / con trái / con phải
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