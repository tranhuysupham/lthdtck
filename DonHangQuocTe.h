#ifndef DONHANGQUOCTE_H
#define DONHANGQUOCTE_H

#include "DonHang.h"

// Lớp DonHangQuocTe kế thừa từ lớp DonHang
// Giải thích: Thực hiện tính kế thừa (Inheritance) để tái sử dụng các thuộc tính chung 
// và bổ sung các đặc tính riêng biệt cho đơn hàng xuyên biên giới.
class DonHangQuocTe : public DonHang {
private:
    // Thuộc tính riêng biệt của đơn hàng quốc tế
    // Giải thích: Phí hải quan là biến số đặc thù, chỉ áp dụng cho loại hình vận chuyển này.
    double phiHaiQuan;

public:
    // 1. Constructor mặc định
    // Giải thích: Gọi Constructor lớp cha và khởi tạo phí hải quan bằng 0.
    DonHangQuocTe() : DonHang(), phiHaiQuan(0) {}

    // 2. Constructor có tham số đầy đủ
    // Giải thích: Chuyển tiếp các thông tin chung lên lớp cha và gán giá trị cho phí hải quan.
    DonHangQuocTe(string ma, string ngay, int loai, double phi) 
        : DonHang(ma, ngay, loai), phiHaiQuan(phi) {}

    // 3. Constructor sao chép
    // Giải thích: Sao chép toàn bộ dữ liệu từ một đối tượng quốc tế khác sang đối tượng mới.
    DonHangQuocTe(const DonHangQuocTe &other) 
        : DonHang(other), phiHaiQuan(other.phiHaiQuan) {}

    // Hệ thống Getter/Setter cho phí hải quan
    // Giải thích: Đảm bảo tính đóng gói bằng cách truy xuất thuộc tính private thông qua hàm công khai.
    double getPhiHaiQuan() const { return phiHaiQuan; }
    void setPhiHaiQuan(double phi) { phiHaiQuan = phi; }

    // Phương thức nhập (Ghi đè - Override)
    // Giải thích: Gọi hàm nhap() của lớp cha để lấy thông tin cơ bản, sau đó bổ sung phần nhập phí hải quan.
    void nhap() override {
        DonHang::nhap();
        setPos(25, 9); cout << ">> PHI HAI QUAN (VND)   : "; cin >> phiHaiQuan;
    }

    // Phương thức in thông tin (Ghi đè - Override)
    // Giải thích: Kết hợp thông tin từ lớp cha và định dạng thêm các cột phân loại, phí phát sinh và tổng tiền.
    void inThongTin() override {
        DonHang::inThongTin();
        cout << left << setw(15) << "Quoc te" << setw(15) << fixed << setprecision(0) << phiHaiQuan
             << setw(15) << tinhTongTien() << " VND" << endl;
    }

    // Phương thức tính tổng tiền (Hiện thực hóa hàm thuần ảo)
    // Giải thích: Định nghĩa công thức tính phí riêng cho quốc tế bao gồm giá gói dịch vụ và thuế hải quan 10%.
    // Đây là ví dụ điển hình của tính đa hình khi chạy chương trình.
    double tinhTongTien() override {
        // Xác định đơn giá dựa trên loại gói dịch vụ (Basic/Fast/Express)
        double giaGoi = (loaiGoi == 1) ? 40000 : (loaiGoi == 2 ? 60000 : 80000);
        // Công thức: Giá gói + (Phí hải quan * 1.1) (Cộng thêm 10% thuế phí)
        return giaGoi + (phiHaiQuan * 1.1); 
    }
};

#endif