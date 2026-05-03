#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include "DonHangTrongNuoc.h"
#include "DonHangQuocTe.h"

using namespace std;

// Hàm thiết lập màu sắc cho văn bản Console
// Giải thích: Sử dụng Windows API để thay đổi màu chữ và nền, giúp giao diện sinh động hơn.
void setUI(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

// Hàm vẽ khung giao diện (Fancy Frame)
// Giải thích: Sử dụng các ký tự mã ASCII mở rộng để vẽ khung hình hộp, tạo không gian làm việc chuyên nghiệp.
void drawFancyFrame(int x, int y, int w, int h, string title) {
    setUI(11); // Màu xanh Cyan cho đường viền
    setPos(x, y); cout << (char)201 << string(w, (char)205) << (char)187;
    for (int i = 1; i <= h; i++) {
        setPos(x, y + i); cout << (char)186 << string(w, ' ') << (char)186;
    }
    setPos(x, y + h + 1); cout << (char)200 << string(w, (char)205) << (char)188;
    if (!title.empty()) {
        setPos(x + (w - (int)title.length()) / 2, y);
        setUI(240); cout << " " << title << " "; 
    }
}

int main() {
    // Thiết lập bảng mã ký tự để vẽ được các đường viền khung
    system("chcp 437 > nul");
    SetConsoleTitleA("ERP LOGISTICS PRO - MINIMIGHT");
    
    // Quản lý danh sách đa hình bằng Vector con trỏ lớp cha
    // Giải thích: Đây là nơi lưu trữ tập trung mọi loại đơn hàng (Nội địa/Quốc tế).
    vector<DonHang*> ds;


    int chon;
    do {
        system("cls"); // Xóa màn hình để vẽ lại menu mới
        
        // Vẽ thanh tiêu đề trên cùng
        setUI(31); for(int i=0; i<3; i++) { setPos(0, i); cout << string(120, ' '); }
        setPos(32, 1); cout << "HE THONG QUAN LY VAN TAI QUOC TE - MINIMIGHT";

        // Vẽ các khung chức năng chính
        drawFancyFrame(15, 6, 60, 11, "BANG DIEU KHIEN TRUNG TAM");
        drawFancyFrame(80, 6, 35, 8, "BANG GIA DICH VU");
        
        // Hiển thị bảng giá tra cứu nhanh
        setUI(15);
        setPos(82, 8);  cout << "TRONG NUOC: 20k - 30k - 40k";
        setPos(82, 9);  cout << "QUOC TE   : 40k - 60k - 80k";
        setPos(82, 11); setUI(14); cout << "* Thue HQ Quoc te: +10%";

        // Danh sách các tùy chọn menu
        setUI(15);
        setPos(20, 9);  cout << "[1] THEM MOI DON HANG NOI DIA";
        setPos(20, 10); cout << "[2] THEM MOI DON HANG QUOC TE";
        setPos(20, 11); cout << "[3] TRICH XUAT BAO CAO CHI TIET";
        setPos(20, 12); cout << "[4] TONG KET TAI CHINH KY NAY";
        setUI(12); setPos(20, 14); cout << "[0] THOAT KHOI HE THONG";

        // Thanh trạng thái dưới cùng (Status Bar) có tên SV và MSSV
        setUI(252); setPos(0, 26); cout << string(120, ' ');
        setPos(5, 26); cout << "Status: ON | SV: Tran Trong Duc Huy | MSSV: 20070926";

        setUI(11); setPos(15, 20); cout << ">> LUA CHON CUA BAN: ";
        if (!(cin >> chon)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

        switch (chon) {
            case 1:
            case 2: {
                system("cls");
                drawFancyFrame(15, 4, 80, 10, chon == 1 ? "NHAP DON NOI DIA" : "NHAP DON QUOC TE");
                setUI(14); setPos(20, 12); 
                cout << (chon == 1 ? "Gia goi: 1:20k | 2:30k | 3:40k" : "Gia goi: 1:40k | 2:60k | 3:80k (+10% Thue)");
                setUI(15);

                // Kỹ thuật Đa hình: Khởi tạo lớp con nhưng quản lý bằng con trỏ lớp cha
                DonHang* dh = (chon == 1) ? (DonHang*)new DonHangTrongNuoc() : (DonHang*)new DonHangQuocTe();
                dh->nhap(); // Tự động gọi đúng hàm nhap() của lớp con tương ứng
                ds.push_back(dh);
                
                setPos(35, 15); setUI(10); cout << "DA LUU VAO DATABASE!";
                _getch(); break;
            }
            case 3: {
                system("cls");
                setUI(31); cout << string(120, ' ') << endl;
                setPos(45, 0); cout << "BAO CAO LOGISTICS CHI TIET";
                cout << "\n\n"; setUI(11);
                
                // Định dạng tiêu đề bảng báo cáo
                cout << left << setw(12) << "  MA ID" << setw(15) << "NGAY DAT" << setw(12) << "GOI" 
                     << setw(15) << "PHAN LOAI" << setw(15) << "PHI PS" << setw(15) << "TONG TIEN" << endl;
                setUI(15); cout << string(105, (char)196) << endl;

                // Vòng lặp Đa hình: Duyệt danh sách và in thông tin từng đơn hàng
                for (auto d : ds) { cout << "  "; d->inThongTin(); }
                _getch(); break;
            }
            case 4: {
                double tong = 0;
                // Tính toán tổng doanh thu dựa trên cơ chế Liên kết muộn (Late Binding)
                for (auto d : ds) tong += d->tinhTongTien(); 
                
                system("cls");
                drawFancyFrame(35, 8, 45, 5, "TONG DOANH THU");
                setPos(40, 11); setUI(15);
                cout << "DOANH THU THUC: " << fixed << setprecision(0) << tong << " VND";
                _getch(); break;
            }
        }
    } while (chon != 0);

    // Giải phóng bộ nhớ động để tránh rò rỉ bộ nhớ (Memory Leak)
    // Giải thích: Do đã có Destructor ảo nên delete con trỏ cha sẽ xóa sạch sẽ lớp con.
    for (auto d : ds) delete d; 
    return 0;
}