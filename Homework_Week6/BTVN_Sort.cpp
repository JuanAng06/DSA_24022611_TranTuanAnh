#include <iostream>

using namespace std;

/**
 * Tráo đổi 2 giá trị.
 * 
 * @param a giá trị cần tráo
 * @param b giá trị cần tráo
 */
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * Sắp xếp mảng theo kiểu Selection Sort: (Độ phức tạp tính toán: O(n^2))
 * - Đặt giá trị đầu chưa sort là giá trị nhỏ nhất
 * - Duyệt hết bên phải, nếu giá trị đang duyệt nhỏ hơn giá trị ban đầu thì đặt giá trị đó min
 * - Tráo giá trị nhỏ nhất với giá trị đầu chưa sort
 * 
 * @param arr mảng cần sắp xếp
 * @param n kích cỡ mảng
 */
void selectionSort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int currIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[currIndex]) {
                currIndex = j;
            }
        }
        swap(arr[i], arr[currIndex]);
    }
}

/**
 * Sắp xếp mảng theo kiểu Bubble Sort (Độ phức tạp tính toán: O(n^2))
 * - So sánh 2 giá trị cạnh nhau, nếu bên trái > bên phải => Swap
 * - Giá trị trong đoạn chưa sắp xếp sẽ là giá trị lớn nhất sau mỗi lần lặp
 * - Tiếp tục làm như vậy cho đến khi cả mảng đã được sắp xếp
 * 
 * @param arr mảng cần sắp xếp
 * @param n kích cỡ mảng
 */
void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/**
 * Sắp xếp mảng theo kiểu Insertion Sort (Độ phức tạp tính toán: O(n^2) nếu tệ nhất, O(n) nếu tốt nhất)
 * - Coi phần tử đầu đã được sắp xếp
 * - Bắt đầu so từ phần tử thứ 2, nếu arr thứ 2 < arr thứ 1 => Dịch chuyển + chèn key
 * - Đến phần tử thứ 3, so sánh với arr 2, rồi sau đó arr 1
 * - Tương tự cho đến khi được sắp xếp hoàn toàn
 * 
 * @param arr mảng cần sắp xpees
 * @param n kích cỡ mảng
 */
void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


// Hàm trộn hai mảng con đã được sắp xếp
void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Số phần tử mảng trái
    int n2 = right - mid;     // Số phần tử mảng phải

    // Tạo mảng tạm
    int* L = new int[n1];
    int* R = new int[n2];

    // Sao chép dữ liệu vào mảng tạm
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Trộn 2 mảng tạm vào mảng chính
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Sao chép phần còn lại (nếu có)
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Giải phóng bộ nhớ tạm
    delete[] L;
    delete[] R;
}

// Hàm Merge Sort chính
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Gọi đệ quy cho 2 nửa
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Trộn hai nửa đã sắp xếp
        merge(arr, left, mid, right);
    }
}

// Hàm partition (phân hoạch)
// Trả về vị trí chính xác của pivot sau khi phân hoạch
int partition(int *arr, int low, int high) {
    int pivot = arr[high];   // Chọn pivot là phần tử cuối
    int i = low - 1;         // Vị trí nhỏ hơn pivot

    for (int j = low; j < high; j++) {
        // Nếu phần tử hiện tại nhỏ hơn pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Đưa pivot vào đúng vị trí
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Hàm quicksort (đệ quy)
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        // Tìm vị trí phân hoạch
        int pi = partition(arr, low, high);

        // Gọi đệ quy cho 2 nửa
        quickSort(arr, low, pi - 1);   // Bên trái pivot
        quickSort(arr, pi + 1, high);  // Bên phải pivot
    }
}

// TEST FUNCTION

/**
 * In mảng (chưa và đã sắp xếp).
 * 
 * @param arr mảng cần in
 * @param n kích cỡ mảng
 */
void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr1[] = {64, 25, 12, 22, 11};
    int arr2[] = {64, 25, 12, 22, 11};
    int arr3[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Mang ban dau: ";
    printArray(arr1, n);

    selectionSort(arr1, n);
    cout << "Sau Selection Sort: ";
    printArray(arr1, n);

    bubbleSort(arr2, n);
    cout << "Sau Bubble Sort: ";
    printArray(arr2, n);

    insertionSort(arr3, n);
    cout << "Sau Insertion Sort: ";
    printArray(arr3, n);

    return 0;
}