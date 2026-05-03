#ifndef DONHANGTRONGNUOC_H
#define DONHANGTRONGNUOC_H

#include "DonHang.h"

// Lớp DonHangTrongNuoc kế thừa công khai từ lớp DonHang
// Giải thích: Sử dụng tính kế thừa để nhận các thuộc tính chung (Mã đơn, Ngày, Gói) 
// và mở rộng thêm các đặc tính riêng cho vận chuyển nội địa.
class DonHangTrongNuoc : public DonHang {
private:
    // Thuộc tính đặc thù của đơn hàng trong nước
    // Giải thích: Phí vận chuyển liên tỉnh là thành phần chi phí riêng chỉ có ở đơn hàng nội địa.
    double phiVanChuyen;

public:
    // 1. Constructor mặc định
    // Giải thích: Gọi constructor lớp cha và khởi tạo phí vận chuyển về giá trị 0.
    DonHangTrongNuoc() : DonHang(), phiVanChuyen(0) {}

    // 2. Constructor có tham số đầy đủ
    // Giải thích: Chuyển tiếp dữ liệu chung lên lớp cha thông qua danh sách khởi tạo và gán phí vận chuyển.
    DonHangTrongNuoc(string ma, string ngay, int loai, double phi) 
        : DonHang(ma, ngay, loai), phiVanChuyen(phi) {}

    // 3. Constructor sao chép (Copy Constructor)
    // Giải thích: Khởi tạo một đơn hàng nội địa mới dựa trên dữ liệu của một đơn hàng nội địa có sẵn.
    DonHangTrongNuoc(const DonHangTrongNuoc &other) 
        : DonHang(other), phiVanChuyen(other.phiVanChuyen) {}

    // Hệ thống Getter và Setter riêng cho phí vận chuyển
    // Giải thích: Bảo đảm tính đóng gói (Encapsulation), kiểm soát quyền truy cập vào biến phiVanChuyen.
    double getPhiVanChuyen() const { return phiVanChuyen; }
    void setPhiVanChuyen(double phi) { phiVanChuyen = phi; }

    // Phương thức nhập (Ghi đè - Override)
    // Giải thích: Tái sử dụng hàm nhập của lớp cha và bổ sung thêm phần nhập phí ship nội địa tại tọa độ chuẩn.
    void nhap() override {
        DonHang::nhap();
        setPos(25, 9); cout << ">> PHI SHIP NOI DIA (VND): "; cin >> phiVanChuyen;
    }

    // Phương thức in thông tin (Ghi đè - Override)
    // Giải thích: Gọi hàm in của lớp cha và định dạng thêm cột phân loại "Trong nuoc" cùng chi phí chi tiết.
    void inThongTin() override {
        DonHang::inThongTin();
        cout << left << setw(15) << "Trong nuoc" << setw(15) << fixed << setprecision(0) << phiVanChuyen
             << setw(15) << tinhTongTien() << " VND" << endl;
    }

    // Phương thức tính tổng tiền (Thực hiện tính Đa hình)
    // Giải thích: Cài đặt công thức tính tiền riêng: Tổng = Giá gói dịch vụ nội địa + Phí ship.
    // Đây là minh chứng cho việc lớp con tự định nghĩa hành vi mà lớp cha (DonHang) đã yêu cầu.
    double tinhTongTien() override {
        // Xác định giá gói dựa trên mã gói (1: 20k, 2: 30k, 3: 40k)
        double giaGoi = (loaiGoi == 1) ? 20000 : (loaiGoi == 2 ? 30000 : 40000);
        return giaGoi + phiVanChuyen;
    }
};

#endif