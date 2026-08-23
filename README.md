# Hệ Thống Quản Lý Bãi Xe Thông Minh (Smart Parking System)

Dự án ứng dụng quản lý bãi giữ xe thông minh viết bằng ngôn ngữ **C++**, thể hiện tư duy **Lập trình Hướng đối tượng (OOP)** nâng cao, kết hợp xử lý **Toán tử Bitwise** để tối ưu hóa việc quản lý thẻ VIP và mã hóa thẻ từ.
## Đặc Điểm & Tính Năng Nổi Bật

### 1. Lập trình Hướng đối tượng (OOP)
* **Kế thừa & Đóng gói (Inheritance & Encapsulation):**
  * Lớp `ChuXe` đóng gói thông tin khách hàng (`ho_ten`, `so_dien_thoai`).
  * Lớp cơ sở `PhuongTien` chứa thông tin dùng chung, được kế thừa bởi hai lớp con `XeMay` và `XeOTo`.
* **Đa hình (Polymorphism):**
  * Sử dụng `std::vector<PhuongTien*>` chứa con trỏ kiểu lớp cha để quản lý chung mọi loại phương tiện trong bãi.
  * Tự động tính toán giá tiền gửi xe riêng biệt cho từng loại xe thông qua cơ chế Ghi đè phương thức (`override` / `virtual`).
* **Quản lý bộ nhớ Heap an toàn:**
  * Khai báo Destructor ảo (`virtual ~PhuongTien()`) giúp dọn dẹp sạch sẽ bộ nhớ động khi thoát chương trình, chống rò rỉ bộ nhớ (Memory Leak).

### 2. Xử lý kĩ thuật Bitwise
* **Bật & Kiểm tra quyền VIP (`Bitwise OR / AND`):**
  * Dùng toán tử `|=` để đăng ký thẻ VIP.
  * Dùng toán tử `&` kết hợp Bitmask (`vip_mask = 2`) để xác định khách hàng VIP và tự động giảm **20%** tổng tiền gửi xe.
* **Mã hóa & Giải mã PIN thẻ từ (`Bitwise XOR`):**
  * Mã hóa 2 chiều mật mã PIN bằng toán tử `^` với `secret_key = 12`.

## Bảng Giá Dịch Vụ Bãi Xe

| Loại Phương Tiện | Quy Định Chỗ Ngồi | Đơn Giá / Giờ |
| :--- | :--- | :--- |
| **Xe Máy** | All | 10.000 VNĐ |
| **Xe Ô tô** | $\le$ 5 chỗ | 30.000 VNĐ |
| **Xe Ô tô** | $>$ 5 chỗ | 50.000 VNĐ |

>  **Chính sách VIP:** Giảm giá 20% trên tổng tiền gốc cho thẻ có tích hợp VIP.

## Hướng Dẫn Biên Dịch & Chạy Chương Trình

### Yêu cầu
* Trình biên dịch C++ (GCC/G++, Clang, MSVC) hỗ trợ chuẩn **C++11** trở lên.

### Các bước thực hiện

1. **Clone dự án về máy:**
   ```bash
   git clone [https://github.com/username_cua_ban/smart-parking-system.git](https://github.com/username_cua_ban/smart-parking-system.git)
   cd smart-parking-system
