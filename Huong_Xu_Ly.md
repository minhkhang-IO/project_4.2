# Phân tích Luồng Hoạt Động và Hướng Xử Lý Dự Án

## 1. Phân tích hiện trạng dự án (Luồng hiện tại)

Dự án hiện tại là một chương trình quản lý "Organic Food Distribution & Batch Tracking" viết bằng ngôn ngữ C. Cấu trúc chương trình bao gồm:

- **`main.c`**: Là điểm vào của chương trình, gọi hàm `runSystem()` để khởi động hệ thống.
- **`Menu.h`**: Định nghĩa các cấu trúc dữ liệu (`Batch`, `Distribution`, `StorageType`) và khai báo các nguyên mẫu hàm. Giới hạn số lượng tối đa là 100 (`MAX_SIZE`).
- **`Menu.c`**: Chứa logic chính của ứng dụng:
  - Hàm `runSystem()`: Vòng lặp Menu chính với 2 chức năng chính là Quản lý Lô hàng (Batch Manager) và Quản lý Phân phối (Distribution Manager).
  - Hàm `processBatchManager()`: Vòng lặp Menu con cho Batch (Thêm, Hiển thị, Cập nhật, Tìm kiếm).
  - Hàm `processDistributionManager()`: Vòng lặp Menu con cho Distribution (Thêm, Theo dõi, Nhóm).
  - Các hàm I/O (`saveDataToFile`, `loadDataFromFile`): Đã có code đọc/ghi từ file `organic_data.txt`.

**Vấn đề / Thiếu sót hiện tại:**
1. **Chưa gọi hàm load/save dữ liệu thực tế**: Mặc dù trong `runSystem()` có in ra `[System] Automatically loading data...` nhưng lại *chưa gọi* hàm `loadDataFromFile(...)`. Tương tự, khi thoát (chọn 0) cũng chưa gọi hàm `saveDataToFile(...)`. Do đó dữ liệu sẽ không được lưu hay nạp.
2. **Chức năng chỉ là vỏ bọc (Mock/Placeholder)**: Các hàm thực thi như `addBatch`, `displayBatches`, `updateBatch`, `searchBatch`... hiện tại chỉ in ra dòng chữ `--> [Executing] ...` chứ chưa có logic xử lý thật sự (chưa thêm, sửa, xoá dữ liệu vào mảng).
3. **Quản lý Input**: Việc nhập liệu xen kẽ `scanf` và chuỗi có thể gây lỗi trôi lệnh.

## 2. Hướng xử lý và phát triển tiếp theo

Để hoàn thiện dự án, chúng ta cần thực hiện các công việc sau theo thứ tự:

### Bước 1: Sửa lỗi luồng Load/Save dữ liệu trong `runSystem()`
- Cập nhật hàm `runSystem()`:
  - Gọi hàm `loadDataFromFile(batches, &batchCount, orders, &orderCount);` ngay trước vòng lặp `do-while` để lấy dữ liệu cũ lên.
  - Gọi hàm `saveDataToFile(batches, batchCount, orders, orderCount);` trong phần xử lý case `0` (Exit) để lưu lại trước khi tắt.

### Bước 2: Triển khai logic cho Batch Manager (Quản lý Lô hàng)
- **`addBatch`**: Viết code yêu cầu nhập thông tin lô hàng (ID, Tên, Đơn vị, Nhiệt độ, Xuất xứ, Loại). Lưu vào mảng `batches[count]` và tăng biến đếm `*count`. Cần kiểm tra không cho phép nhập trùng `batchID`.
- **`displayBatches`**: Duyệt từ phần tử 0 đến `count - 1`, in thông tin các lô hàng ra màn hình dưới dạng bảng cho dễ nhìn.
- **`updateBatch`**: Tìm phần tử trong mảng có `batchID` trùng khớp. Nếu tìm thấy, cho phép nhập lại thông tin để ghi đè (không đổi ID).
- **`searchBatch`**: Duyệt mảng, kiểm tra xem `batchID` hoặc `productName` có chứa từ khóa không, nếu có thì in ra.
- **`searchBatchByOrigin`**: Tương tự tìm kiếm nhưng so sánh với trường `origin`.

### Bước 3: Triển khai logic cho Distribution Manager (Quản lý Phân phối)
- **`addDistribution`**: Nhập thông tin đơn phân phối (ID, Tên NCC, Nơi đến, Ngày giao) và lưu vào `orders`. Tăng biến đếm.
- **`trackDistribution`**: Tìm kiếm trong mảng `orders` dựa trên Tên nhà cung cấp (`supplierName`) hoặc Nơi đến (`destination`).
- **`groupDistributionByDestination`**: Do dữ liệu dùng mảng tĩnh, ta có thể dùng thuật toán sắp xếp (Bubble Sort / Selection Sort) để sắp xếp mảng `orders` theo 알파벳 của `destination`. Sau đó in ra, dữ liệu sẽ tự động được nhóm theo nơi đến.

### Bước 4: Cải thiện Trải nghiệm (UX) và Validation
- Viết một hàm phụ trợ để xử lý xóa bộ nhớ đệm (buffer) trước khi đọc chuỗi bằng `fgets`, tránh tình trạng bị trôi lệnh do phím `Enter` để lại sau khi dùng `scanf` nhập số.
- Đảm bảo khi số lượng vượt quá `MAX_SIZE` (100) thì sẽ hiển thị thông báo lỗi thay vì tiếp tục cho thêm dữ liệu gây crash.

---
> Bạn có thể tham khảo file này. Nếu bạn muốn, tôi có thể tiến hành viết code trực tiếp cho các bước này vào các file của bạn (ví dụ bắt đầu từ Bước 1 và Bước 2). Hãy cho tôi biết bạn muốn ưu tiên làm phần nào trước nhé!
