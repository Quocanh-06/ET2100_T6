#include <iostream>
#include <string>

using namespace std;

// 1. Cấu trúc dữ liệu File và Node
struct File {
    string name;
    long long size; // Dùng long long để chứa được dung lượng hàng GB
    int time;       // Trật tự thời gian (Timestamp)
};

struct Node {
    File data;
    Node* next;
};

// 2. Hàm tính tổng dung lượng hiện có trong danh sách
long long getTotalSize(Node* head) {
    long long total = 0;
    while (head != nullptr) {
        total += head->data.size;
        head = head->next;
    }
    return total;
}

// 3. Hàm chèn file theo trật tự thời gian (File cũ đứng trước, file mới đứng sau)
void insertByTime(Node* &head, File f) {
    Node* newNode = new Node{f, nullptr};
    
    // Trường hợp danh sách rỗng hoặc file mới có thời gian nhỏ nhất
    if (!head || head->data.time >= f.time) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Duyệt tìm vị trí để chèn sau node 'curr'
    Node* curr = head;
    while (curr->next && curr->next->data.time < f.time) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

// 4. Hàm Backup: Xóa file nhỏ nhất cho đến khi tổng dung lượng <= 32GB
void backupToUSB(Node* &head) {
    // 32GB quy đổi ra Bytes (32 * 1024^3)
    long long limit = 32LL * 1024 * 1024 * 1024; 
    
    while (getTotalSize(head) > limit) {
        if (head == nullptr) break;

        Node *minNode = head, *minPrev = nullptr;
        Node *curr = head, *prev = nullptr;
        long long minSize = head->data.size;

        // Bước 1: Duyệt toàn bộ danh sách tìm file có size nhỏ nhất
        while (curr != nullptr) {
            if (curr->data.size < minSize) {
                minSize = curr->data.size;
                minNode = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr.next;
        }

        // Bước 2: Thực hiện xóa và "bắc cầu" con trỏ để không làm đứt mạch danh sách
        if (minPrev == nullptr) { 
            head = head->next; // Xóa thằng ngay đầu hàng
        } else {
            minPrev->next = minNode->next; // Bắc cầu qua thằng minNode
        }
        
        cout << "[Backup] Da loai bo file nho nhat: " << minNode->data.name 
             << " (" << minNode->data.size << " bytes)" << endl;
             
        delete minNode; // Giải phóng bộ nhớ cho máy
    }
}

// 5. Hàm thực thi chính
int main() {
    Node* list = nullptr;
    cout << "--- HE THONG QUAN LY FILE ET1-HUST ---" << endl;

    // Giả lập thêm file vào danh sách (Tên, Kích thước Byte, Thời gian)
    insertByTime(list, {"BaoCao_K69.pdf", 1024 * 1024 * 5, 1680000000}); // 5MB
    insertByTime(list, {"Phim_Hanh_Dong.mkv", 40000000000LL, 1680000010}); // 40GB (Nặng hơn USB)
    insertByTime(list, {"BaiTapC++.cpp", 1024 * 50, 1680000005}); // 50KB

    cout << "Tong dung luong ban dau: " << getTotalSize(list) << " bytes" << endl;
    cout << "--------------------------------------" << endl;

    // Thực hiện quá trình dọn dẹp để vừa USB 32GB
    backupToUSB(list);

    cout << "--------------------------------------" << endl;
    cout << "Tong dung luong sau khi backup: " << getTotalSize(list) << " bytes" << endl;
    cout << "Ket trang thai: SAN SANG SAO CHEP VAO USB." << endl;

    return 0;
}
