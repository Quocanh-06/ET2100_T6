# BÀI TẬP TUẦN 6: QUẢN LÝ FILE BẰNG LINKED LIST

## 1. Phân tích sơ bộ
- **Cấu trúc:** Danh sách liên kết đơn (Singly Linked List).
- **Tiêu chí:** Sắp xếp theo trật tự thời gian (Timestamp) tăng dần.
- **Backup:** Loại bỏ các file có kích thước nhỏ nhất trước để tối ưu không gian USB $32 \text{ GB}$.

## 2. Mô tả thuộc tính và hàm
- **Node:** Lưu File (Name, Size, Time) và con trỏ `Next`.
- **Insert_By_Time:** Duyệt danh sách để chèn file vào đúng vị trí thời gian.
- **Backup_To_USB:** Tìm và xóa Node có `fileSize` nhỏ nhất cho đến khi tổng dung lượng $\le 32 \times 1024^3$ Bytes.

## 3. Mã giả giải thuật (Pseudocode)
### Thao tác: Chèn file theo thời gian
```
Hàm Insert_By_Time(List, NewFile):
    newNode = Create_Node(NewFile)
    Nếu List.head == NULL hoặc NewFile.time < List.head.data.time:
        newNode.next = List.head
        List.head = newNode
    Ngược lại:
        curr = List.head
        Trong khi (curr.next != NULL và curr.next.data.time < NewFile.time):
            curr = curr.next
        newNode.next = curr.next
        curr.next = newNode
```
