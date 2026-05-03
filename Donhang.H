#ifndef DONHANG_H
#define DONHANG_H

#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// Hàm neo tọa độ để vẽ giao diện 2D chuẩn xác
// Giải thích: Sử dụng API của Windows để điều khiển vị trí con trỏ trên Console, 
// giúp dữ liệu nhập/xuất hiện đúng vị trí trong khung giao diện đã thiết kế.
static void setPos(int x, int y) {
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Lớp cha trừu tượng (Abstract Class) DonHang
// Giải thích: Đây là lớp cơ sở chứa các đặc điểm chung của mọi đơn hàng. 
// Do có hàm thuần ảo nên không thể tạo đối tượng trực tiếp từ lớp này.
class DonHang {
protected:
    // Phạm vi Protected: Cho phép các lớp con truy cập trực tiếp các thuộc tính 
    // mã đơn, ngày đặt và loại gói để tính toán chi phí.
    string maDon, ngayDat;
    int loaiGoi; // 1: Basic, 2: Fast, 3: Express

public:
    // 1. Constructor mặc định (Default Constructor)
    // Giải thích: Thiết lập các giá trị ban đầu trống cho đối tượng khi mới khởi tạo.
    DonHang() : maDon(""), ngayDat(""), loaiGoi(1) {}

    // 2. Constructor có tham số đầy đủ
    // Giải thích: Cho phép truyền dữ liệu trực tiếp khi tạo mới đơn hàng (thường dùng cho dữ liệu mẫu).
    DonHang(string ma, string ngay, int goi) : maDon(ma), ngayDat(ngay), loaiGoi(goi) {}

    // 3. Constructor sao chép (Copy Constructor)
    // Giải thích: Tạo ra một bản sao mới dựa trên các thuộc tính của một đối tượng đơn hàng hiện có.
    DonHang(const DonHang &other) : maDon(other.maDon), ngayDat(other.ngayDat), loaiGoi(other.loaiGoi) {}

    // 4. Destructor ảo (Virtual Destructor)
    // Giải thích: Đảm bảo giải phóng bộ nhớ đúng cách cho lớp con khi sử dụng con trỏ lớp cha, 
    // giúp ngăn ngừa lỗi rò rỉ bộ nhớ (Memory Leak).
    virtual ~DonHang() {}

    // 5. Hệ thống Getter và Setter (Encapsulation)
    // Giải thích: Tuân thủ tính đóng gói, cho phép truy xuất và cập nhật dữ liệu một cách an toàn.
    string getMaDon() const { return maDon; }
    void setMaDon(string ma) { maDon = ma; }
    string getNgayDat() const { return ngayDat; }
    void setNgayDat(string ngay) { ngayDat = ngay; }
    int getLoaiGoi() const { return loaiGoi; }
    void setLoaiGoi(int goi) { loaiGoi = goi; }

    // Phương thức nhập đa hình (Virtual Function)
    // Giải thích: Cho phép các lớp con ghi đè để bổ sung các trường nhập liệu riêng 
    // như phí vận chuyển hay phí hải quan.
    virtual void nhap() {
        int x = 25;
        setPos(x, 6); cout << ">> MA DON (VD: VN001) : "; cin >> ws; getline(cin, maDon);
        setPos(x, 7); cout << ">> NGAY (DD/MM/YYYY) : "; getline(cin, ngayDat);
        int t;
        do {
            setPos(x, 8); cout << "                                               "; // Xóa dòng cũ
            setPos(x, 8); cout << ">> GOI (1:Basic, 2:Fast, 3:Express): ";
            if (!(cin >> t)) { cin.clear(); cin.ignore(1000, '\n'); t = 0; }
        } while (t < 1 || t > 3); // Kiểm tra tính hợp lệ của dữ liệu nhập (Validation)
        loaiGoi = t;
    }

    // Phương thức xuất thông tin đa hình
    // Giải thích: Sử dụng setw() để định dạng bảng báo cáo thẳng hàng và chuyên nghiệp.
    virtual void inThongTin() {
        string tg = (loaiGoi == 1) ? "Basic" : (loaiGoi == 2 ? "Fast" : "Express");
        cout << left << setw(12) << maDon << setw(15) << ngayDat << setw(12) << tg;
    }

    // Hàm thuần ảo để tính tổng tiền (Pure Virtual Function)
    // Giải thích: Đặt nền móng cho tính đa hình. Mỗi lớp con sẽ tự cài đặt công thức 
    // tính chi phí riêng (Nội địa/Quốc tế) để thực hiện Liên kết muộn (Late Binding).
    virtual double tinhTongTien() = 0;
};

#endif