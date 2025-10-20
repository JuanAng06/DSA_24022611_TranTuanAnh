#include "BTVN_heap.cpp"

struct PriorityQueue {

    Heap* heap; // Linh hoạt giữa việc tự tạo heap / dùng heap có sẵn
    bool owned;  // Để biết có nên delete hay không

    // Tự tạo heap bên trong
    PriorityQueue(int capacity, bool isMinHeap = false)
        : heap(new Heap(capacity, isMinHeap)), owned(true) {}

    // Dùng heap có sẵn
    PriorityQueue(Heap& existingHeap)
        : heap(&existingHeap), owned(false) {}

    ~PriorityQueue() {
        if (owned) delete heap; // chỉ xóa nếu tự tạo
    }

    bool insert(int value) {
        return heap->insert(value);
    }

    int pop() {
        return heap->extractRoot();
    }

    bool isEmpty() {
        return heap->isEmpty();
    }

    int top() {
        return heap->getRoot();
    }

    int size() {
        return heap->size();
    }

};

// --- MAIN TEST ---
int main() {
    cout << "===== TEST PRIORITY QUEUE =====" << endl;

    // Tạo heap gốc (false = topHeap)
    Heap baseHeap(10, false);  
    PriorityQueue pq(baseHeap);

    // -------------------------------
    cout << "\n[1] Test insert()" << endl;
    pq.insert(10);
    pq.insert(30);
    pq.insert(20);
    pq.insert(50);
    pq.insert(40);

    cout << "\nHeap sau khi insert: " << endl;
    pq.heap->printHeap();

    // -------------------------------
    cout << "\n[2] Test top()" << endl;
    cout << "top element (getRoot): " << pq.top() << endl;

    // -------------------------------
    cout << "\n[3] Test size()" << endl;
    cout << "Current size: " << pq.size() << endl;

    // -------------------------------
    cout << "\n[4] Test isEmpty()" << endl;
    cout << (pq.isEmpty() ? "Queue is empty" : "Queue is NOT empty") << endl;

    // -------------------------------
    cout << "\n[5] Test pop()" << endl;
    cout << "Deleted top: " << pq.pop() << endl;
    pq.heap->printHeap();

    cout << "\nDeleted top: " << pq.pop() << endl;
    pq.heap->printHeap();

    // -------------------------------
    cout << "\n[6] Test lại top(), size(), isEmpty() sau khi xóa" << endl;
    cout << "top element: " << pq.top() << endl;
    cout << "Current size: " << pq.size() << endl;
    cout << (pq.isEmpty() ? "Queue is empty" : "Queue is NOT empty") << endl;

    // -------------------------------
    cout << "\n[7] Test pop() đến khi rỗng" << endl;
    while (!pq.isEmpty()) {
        pq.pop();
    }
    cout << (pq.isEmpty() ? "Queue is empty" : "Queue is NOT empty") << endl;

    cout << "\n[8] Test pop() khi rỗng (trường hợp lỗi)" << endl;
    pq.pop(); // Gọi xóa khi rỗng để xem xử lý lỗi

    cout << "\n===== TEST COMPLETED =====" << endl;
    return 0;
}