# Các lỗi đã được sửa trong dự án

Dưới đây là danh sách chi tiết các lỗi đã được khắc phục thông qua **Bước 1** và **Bước 2**:

## 1. Lỗi ở luồng Load / Save dữ liệu (Bước 1)
- **Vấn đề**: Trong hàm `runSystem()`, hệ thống in ra thông báo `[System] Automatically loading data...` nhưng lại thiếu câu lệnh gọi hàm nạp dữ liệu. Tương tự, khi người dùng chọn thoát (`case 0`), chương trình chỉ in thông báo mà không gọi hàm lưu dữ liệu, dẫn đến mọi thao tác thêm/sửa của người dùng đều bị mất sau khi tắt app.
- **Cách sửa**: 
  - Bổ sung lệnh gọi hàm `loadDataFromFile(batches, &batchCount, orders, &orderCount);` ngay trước vòng lặp chính (do-while).
  - Bổ sung lệnh gọi hàm `saveDataToFile(batches, batchCount, orders, orderCount);` vào trong `case 0` để lưu trạng thái mảng xuống file trước khi kết thúc chương trình.

## 2. Các hàm chức năng chỉ là vỏ bọc "Placeholder" (Bước 2)
- **Vấn đề**: Toàn bộ các hàm trong phần Quản lý lô hàng (Batch Manager) như `addBatch`, `displayBatches`, `updateBatch`, `searchBatch`, `searchBatchByOrigin` hiện tại chỉ chứa mỗi lệnh `printf("\n--> [Executing] ...\n");` chứ chưa có logic xử lý thật sự để tương tác với mảng `batches`.
- **Cách sửa**: Đã triển khai code hoàn chỉnh cho các hàm này:
  - **`addBatch`**: Thêm tính năng kiểm tra mảng đầy (vượt quá `MAX_SIZE`). Xử lý kiểm tra trùng lặp `Batch ID`. Thêm logic lấy dữ liệu đầu vào.
  - **`displayBatches`**: Xây dựng lại định dạng in thông tin dưới dạng bảng bằng các chuỗi định dạng như `%-15s`, giúp danh sách hiện ra ngay ngắn, chuyên nghiệp hơn.
  - **`updateBatch`**: Áp dụng thuật toán tìm kiếm tuyến tính đúng `batchID`. Nếu tìm thấy, cấp quyền ghi đè toàn bộ các trường thông tin (trừ ID) của phần tử đó.
  - **`searchBatch` & `searchBatchByOrigin`**: Tích hợp hàm `strstr()` trong thư viện `string.h` để có thể tìm kiếm theo từ khóa một cách tương đối linh hoạt, bao gồm tìm ID, Tên sản phẩm, hoặc Xuất xứ.
  
## 3. Lỗi trôi lệnh khi nhập liệu trong C (UX bug)
- **Vấn đề**: Khi nhập các số nguyên (như chọn menu qua `scanf`) sẽ để thừa một phím `Enter` (`\n`) trong bộ nhớ đệm (buffer) của luồng nhập `stdin`. Khi gọi hàm đọc chuỗi sau đó (như Tên sản phẩm), phím `Enter` dư thừa này sẽ khiến hàm đọc chuỗi kết thúc ngay lập tức, sinh ra hiện tượng "trôi lệnh".
- **Cách sửa**: Đã bổ sung cơ chế "dọn dẹp" (clear buffer) bằng vòng lặp `while(getchar() != '\n');` trước khi thực thi hàm `fgets()` ở những vị trí rủi ro, nhằm đảm bảo tiến trình nhập liệu mượt mà, không bao giờ bị bỏ qua.
