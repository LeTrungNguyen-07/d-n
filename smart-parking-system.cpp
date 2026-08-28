#include <iostream>
#include <vector>
using namespace std;
class ChuXe { 
    private: 
        string ho_ten;
        string so_dien_thoai;
    public: 
        ChuXe(){};
        ChuXe(string ht, string sdt): ho_ten(ht), so_dien_thoai(sdt){};
        string getHoTen() {
            return ho_ten;
        }
        void setHoTen(string ht) {
             ho_ten = ht; 
        }
        string getSoDienThoai() {
            return so_dien_thoai;
        }
        void setSoDienThoai(string sdt) {
            so_dien_thoai = sdt;
        }
        void InThongTin() {
            cout << "Chủ xe: " << ho_ten << ", Số điện thoại: " << so_dien_thoai << endl;
        }
};
class PhuongTien {
    protected: 
    string bien_so;
    int gio_gui;
    ChuXe chu_xe;
    public:
    PhuongTien(string bs,int gg, ChuXe cx): bien_so(bs), gio_gui(gg),chu_xe(cx){};
        virtual ~PhuongTien() {}
        virtual void xuatThongTin() {
            cout << bien_so << " Giờ gửi " << gio_gui << endl;
            chu_xe.InThongTin();
        }
        virtual long long tinhTienGui() {
            return 0;
        }
    };
class XeMay : public PhuongTien {
    public:
    XeMay(string bs,int gg, ChuXe cx) : PhuongTien(bs,gg,cx){}
    long long tinhTienGui() override {
        return (long long) gio_gui*10000;
    }
};
class XeOTo : public PhuongTien {
    private: 
    int so_cho_ngoi;
    public:
    XeOTo(string bs,int gg, ChuXe cx,int so_cho) : PhuongTien(bs,gg,cx), so_cho_ngoi(so_cho){}
    long long tinhTienGui() override {
        if (so_cho_ngoi <= 5) {
            return (long long)gio_gui*30000;
        }
        else {
            return (long long)gio_gui*50000;
        }
    }
};
const int vip_mask = 2; // 0010
const int secret_key = 12; // 1110
void batTheVip(int &ma_the) {             // bật vip 
    ma_the |= vip_mask;
}
bool kiemTheVip(int ma_the) {             // kiểm tra vip
    return (ma_the & vip_mask) != 0;  
}
int maHoaPin(int pin) {                   // mã hoá và giải mã pin 
    return pin ^ secret_key;
}
int main() {
    vector<PhuongTien*> bai_xe;
    vector<int> danh_sach_ma_the;
    int lua_chon = 0;

    do {
        cout << " ---- Hệ Thống Bãi Xe Thông Minh ----- " << endl;
        cout << " 1. Thêm xe máy vào bãi. " << endl;
        cout << " 2. Thêm xe OTo vào bãi. " << endl;
        cout << " 3. In danh sách xe và tính tổng doanh thu. " << endl;
        cout << " 4. Demo mã hoá pin thẻ từ (bitwise XOR). " << endl;
        cout << " 5. Thoát chương trình. " << endl;
        cout << " Nhập lựa chọn (1-5): " << endl;
        cin >> lua_chon;
        switch (lua_chon) {
            case 1: {
                string bs, ten, sdt;
                int gg, ma_the, la_vip;

                cin.ignore();
                cout << " Nhập biển số: "; getline(cin, bs);
                cout << " Nhập tên chủ xe: "; getline(cin, ten);
                cout << " Nhập số điện thoại chủ xe: "; getline(cin,sdt);
                cout << " Nhập số giờ gửi: "; cin >> gg;
                cout << " Nhập mã thẻ giữ xe: "; cin >> ma_the;
                cout << " Thẻ có đăng ký VIP không? (1. Có, 0. Không)"; cin >> la_vip;
                if (la_vip == 1) {
                    batTheVip(ma_the);
                }
                ChuXe cx(ten,sdt);
                bai_xe.push_back(new XeMay(bs,gg,cx));
                danh_sach_ma_the.push_back(ma_the);
                cout << " Đã thêm Xe Máy vào bãi xe thành công " << endl;
                break;    
            }
            case 2: {
                string bs, ten, sdt;
                int gg, cho_ngoi, ma_the, la_vip;

                cin.ignore();
                cout << " Nhập biển số xe: "; getline(cin,bs);
                cout << " Nhập tên chủ xe: "; getline(cin,ten);
                cout << " Nhập số điện thoại: "; getline(cin,sdt);

                cout << " Nhập số giờ gửi: "; cin >> gg;
                cout << " Nhập số chỗ ngồi: "; cin >> cho_ngoi;          
                cout << " Nhập mã thẻ giữ xe: "; cin >> ma_the;
                cout << " Thẻ có đăng ký VIP không? "; cin >> la_vip;

                if (la_vip == 1) {
                    batTheVip(ma_the);
                }
                ChuXe cx(ten,sdt);
                bai_xe.push_back(new XeOTo(bs,gg,cx,cho_ngoi));
                danh_sach_ma_the.push_back(ma_the);
                cout << " Đã thêm Xe OTo vào bãi xe. " << endl;
                break;
            }
            case 3: {
                if (bai_xe.empty()) {
                    cout << " Bãi xe đang trống. " << endl;
                    break;
                }
                cout << " --- Danh Sách Xe Trong Bãi --- " << endl;            
                long long tong_doanh_thu = 0;
                int index = 0;
        // Duyệt qua bãi xe (Tính Đa hình)
                for (PhuongTien* pt : bai_xe) {
                pt->xuatThongTin();
                long long tien_goc = pt->tinhTienGui();
                long long tien_thuc_te = tien_goc; 
        // Kiểm tra quyền VIP bằng toán tử &
                if (kiemTheVip(danh_sach_ma_the[index])) {
                cout << " đã xác thực thẻ VIP " << endl;
                tien_thuc_te = tien_goc*80/100;
            } else {
                cout << " đã xác thực thẻ thường " << endl;
            }
                cout << " Tiền gửi gốc: " << tien_goc << endl;
                cout << " Tiền phải trả: " << tien_thuc_te << endl;
                cout << " ------------------------ " << endl;    
                tong_doanh_thu += tien_thuc_te; 
                index++;
            }
            cout << " Tổng doanh thu: " << tong_doanh_thu << endl;
            break;
        }
        case 4: {
        // demo mã hoá mã pin thẻ từ (XOR ^)
            int pin;
            cout << " Nhập mã pin: ";
            cin >> pin;
            int pin_da_ma_hoa = maHoaPin(pin);
            int pin_giai_ma = maHoaPin(pin_da_ma_hoa);

            cout << " Mã pin gốc: " << pin << endl;
            cout << " Mã pin đã mã hoá: " << pin_da_ma_hoa << endl;
            cout << " Mã pin đã được giải mã: " << pin_giai_ma << endl;
            break;
        }
        
        case 5:
            cout << " Đang dọn dẹp bộ nhớ Heap và thoát chương trình. " << endl;
            break;
            
        default:
            cout << " Lựa chọn không hợp lệ, vui lòng nhập lại. " << endl;
    }
} while (lua_chon != 5);
    // Dọn dẹp bộ nhớ Heap
for(PhuongTien* pt : bai_xe) {
    delete pt;
}
bai_xe.clear();
cout << " Cảm ơn bạn đã sử dụng phần mềm! " << endl;
return 0;
}
