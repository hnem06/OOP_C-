#include <bits/stdc++.h>
#include <windows.h>
#include <stdexcept>

using namespace std;

void S(float s) { Sleep((int)(s * 1000)); }

namespace Exceptions
{
    class AuthenticationFailedException : public runtime_error
    {
    public:
        AuthenticationFailedException(const string &msg) : runtime_error(msg) {}
    };
    class RoomNotAvailableException : public runtime_error
    {
    public:
        RoomNotAvailableException(const string &msg) : runtime_error(msg) {}
    };
    class InvalidCustomerInfoException : public runtime_error
    {
    public:
        InvalidCustomerInfoException(const string &msg) : runtime_error(msg) {}
    };
}

string formatTien(long long tien)
{
    string result = to_string(tien);

    for (int i = result.size() - 3; i > 0; i -= 3)
    {
        result.insert(i, ",");
    }
    return result;
}

string GetRole(int role)
{
    if (role == 1)
        return "Le tan";
    return "Quan li";
}

class DateTime
{
    int day, month, year, hour, minute;

public:
    DateTime() : day(1), month(1), year(2024), hour(0), minute(0) {}
    DateTime(int d, int m, int y, int h = 0, int min = 0)
        : day(d), month(m), year(y), hour(h), minute(min) {}
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setHour(int h) { hour = h; }
    void setMinute(int m) { minute = m; }
    int soNgay(const DateTime &other) const
    {
        return abs((year * 365 + month * 30 + day) - (other.year * 365 + other.month * 30 + other.day));
    }
    void hienThi() const
    {
        cout << (day < 10 ? "0" : "") << day << "/" << (month < 10 ? "0" : "") << month << "/" << year;
        // if (hour != 0 || minute != 0)
        //     cout << " " << (hour < 10 ? "0" : "") << hour << ":" << (minute < 10 ? "0" : "") << minute;
    }
    string toString() const
    {
        return (day < 10 ? "0" : "") + to_string(day) + "/" + (month < 10 ? "0" : "") + to_string(month) + "/" + to_string(year);
    }
};

class Pawn
{
protected:
    string id;

public:
    Pawn() : id("") {}
    Pawn(const string &id) : id(id) {}
    string getID() const { return id; }
    void setID(const string &newId) { id = newId; }
    virtual void hienThi() const = 0;
};

class TaiKhoan : public Pawn
{
    string password, fullName;
    int role; // 1 = Le tan, 2 = Quan li
public:
    TaiKhoan() : Pawn(), role(1) {}
    TaiKhoan(const string &user, const string &pass, int r = 1, const string &name = "Unknown")
        : Pawn(user), password(pass), fullName(name), role(r) {}

    string getUsername() const { return id; }
    string getPassword() const { return password; }
    int getRole() const { return role; }
    string getFullName() const { return fullName; }

    void setUsername(const string &user) { setID(user); }
    void setPassword(const string &pass) { password = pass; }
    void setRole(int r) { role = r; }
    void setFullName(const string &name) { fullName = name; }

    void hienThi() const override
    {
        cout << "Username: " << id << " | Vai tro: " << GetRole(role) << " | Ho ten: " << fullName << endl;
    }
};

class KhachHang : public Pawn
{
    string hoTen, soDienThoai;
    int namSinh;

public:
    KhachHang() : Pawn(), namSinh(0) {}
    KhachHang(const string &ma, const string &ten, const string &sdt, int ns)
        : Pawn(ma), hoTen(ten), soDienThoai(sdt), namSinh(ns) {}

    string getMaKhach() const { return id; }
    string getHoTen() const { return hoTen; }
    string getSoDienThoai() const { return soDienThoai; }
    int getNamSinh() const { return namSinh; }
    void setMaKhach(const string &ma) { setID(ma); }
    void setHoTen(const string &ten) { hoTen = ten; }
    void setSoDienThoai(const string &sdt) { soDienThoai = sdt; }
    void setNamSinh(int ns) { namSinh = ns; }
    void hienThi() const override
    {
        cout << "Ma khach: " << id << " | Ho ten: " << hoTen << " | SDT: " << soDienThoai << " | Nam sinh: " << namSinh << endl;
    }
};

class Phong : public Pawn
{
    string loaiPhong, trangThai;
    int giaPhong;

public:
    Phong() : Pawn(), giaPhong(0) {}
    Phong(const string &ma, const string &loai, int gia, const string &trangthai)
        : Pawn(ma), loaiPhong(loai), trangThai(trangthai), giaPhong(gia) {}

    string getMaPhong() const { return getID(); }
    string getLoaiPhong() const { return loaiPhong; }
    int getGiaPhong() const { return giaPhong; }
    string getTrangThai() const { return trangThai; }

    void setMaPhong(const string &ma) { setID(ma); }
    void setLoaiPhong(const string &loai) { loaiPhong = loai; }
    void setGiaPhong(int gia) { giaPhong = gia; }
    void setTrangThai(const string &trangthai) { trangThai = trangthai; }
    void hienThi() const override
    {
        cout << "Ma phong: " << id << " | Loai: " << loaiPhong << " | Gia: " << formatTien(giaPhong) << " | Trang thai: " << trangThai << endl;
    }
};

class Booking : public Pawn
{
    string maKhach, maPhong;
    DateTime checkIn, checkOutDuKien;

public:
    Booking() : Pawn() {}
    Booking(const string &mb, const string &mk, const string &mp, const DateTime &ci, const DateTime &co) : Pawn(mb), maKhach(mk), maPhong(mp), checkIn(ci), checkOutDuKien(co) {}

    string getMaBooking() const { return getID(); }
    string getMaKhach() const { return maKhach; }
    string getMaPhong() const { return maPhong; }
    DateTime getCheckIn() const { return checkIn; }
    DateTime getCheckOutDuKien() const { return checkOutDuKien; }
    void setMaBooking(const string &mb) { setID(mb); }
    void setMaKhach(const string &mk) { maKhach = mk; }
    void setMaPhong(const string &mp) { maPhong = mp; }
    void setCheckIn(const DateTime &ci) { checkIn = ci; }
    void setCheckOutDuKien(const DateTime &co) { checkOutDuKien = co; }
    void hienThi() const override
    {
        cout << "Ma booking: " << getID() << " | Ma khach: " << maKhach << " | Ma phong: " << maPhong << " | Check-in: ";
        checkIn.hienThi();
        cout << " | Check-out: ";
        checkOutDuKien.hienThi();
        cout << endl;
    }
};

class LichSuDatPhong
{
    string maKhach, maPhong, nguoiCheckout;
    DateTime ngayDen, ngayDi;
    double tongTien;

public:
    LichSuDatPhong() : tongTien(0) {}
    LichSuDatPhong(const string &mk, const string &mp, const DateTime &nd, const DateTime &ndi, double tien, const string &nguoi = "")
        : maKhach(mk), maPhong(mp), nguoiCheckout(nguoi), ngayDen(nd), ngayDi(ndi), tongTien(tien) {}
    string getID() const { return maKhach + "_" + maPhong + "_" + to_string(ngayDen.getYear()) + "_" + to_string(ngayDen.getMonth()) + "_" + to_string(ngayDen.getDay()); }
    string getMaKhach() const { return maKhach; }
    string getMaPhong() const { return maPhong; }
    DateTime getNgayDen() const { return ngayDen; }
    DateTime getNgayDi() const { return ngayDi; }
    double getTongTien() const { return tongTien; }
    string getNguoiCheckout() const { return nguoiCheckout; }
    void setMaKhach(const string &mk) { maKhach = mk; }
    void setMaPhong(const string &mp) { maPhong = mp; }
    void setNgayDen(const DateTime &nd) { ngayDen = nd; }
    void setNgayDi(const DateTime &ndi) { ngayDi = ndi; }
    void setTongTien(double tien) { tongTien = tien; }
    void setNguoiCheckout(const string &nguoi) { nguoiCheckout = nguoi; }
    void hienThi() const
    {
        cout << "Ma khach: " << maKhach << " | Ma phong: " << maPhong << " | Ngay den: ";
        ngayDen.hienThi();
        cout << " | Ngay di: ";
        ngayDi.hienThi();
        cout << " | Tong tien: " << formatTien((long long)tongTien);
        if (!nguoiCheckout.empty())
        {
            cout << " | Nguoi checkout: " << nguoiCheckout;
        }
        cout << endl;
    }
};

template <class T>
class QuanLy
{
    vector<T> danhSach;

public:
    void Them(const T &item) { danhSach.push_back(item); }
    void Xoa(const string &id)
    {
        danhSach.erase(remove_if(danhSach.begin(), danhSach.end(), [&id](const T &item)
                                 { return item.getID() == id; }),
                       danhSach.end());
    }
    int TimKiem(const string &id)
    {
        for (int i = 0; i < danhSach.size(); i++)
            if (danhSach[i].getID() == id)
                return (int)i;
        return -1;
    }
    void HienThiDanhSach() const
    {
        if (danhSach.empty())
        {
            cout << "[!] Danh sach trong.\n";
            return;
        }
        for (const auto &item : danhSach)
        {
            item.hienThi();
        }
    }
    vector<T> &GetDanhSach() { return danhSach; }
    const vector<T> &GetDanhSach() const { return danhSach; }
    T &GetAt(int index) { return danhSach[index]; }
    const T &GetAt(int index) const { return danhSach[index]; }
    int GetSize() const { return danhSach.size(); }
    bool IsEmpty() const { return danhSach.empty(); }
};

QuanLy<TaiKhoan> ListAccount;
QuanLy<Phong> ListPhong;
QuanLy<KhachHang> ListKhachHang;
QuanLy<Booking> ListBooking;
QuanLy<LichSuDatPhong> ListLichSu;

TaiKhoan LoginedInAccount;
int SoLuongLichSuBanDau = 0;
int SoLuongBookingBanDau = 0;

void Init_Data();
void LaunchSystem();
void CheckLogin();
void ShowMenu();
void QuanLiNhanVien();
void QuanLiKhachHang();
void QuanLiPhong();
void DatPhong();
void TraPhong();
void BaoCaoLichSu();
void ChotCa();

int main()
{
    Init_Data();
    LaunchSystem();
    return 0;
}

void pause()
{
    cout << "\nNhan phim bat ky de quay lai...";
    cin.get();
}
void showFail(const string &msg)
{
    cout << "[FAIL] " << msg << "\n";
    pause();
}
void showSuccess(const string &msg)
{
    cout << "[SUCCESS] " << msg << "\n";
    pause();
}
void headMenu(const string &title)
{
    system("cls");
    cout << "============================ " << title << " ============================\n";
}

string getTrangThai(int choice)
{
    if (choice == 1)
        return "Trong";
    if (choice == 2)
        return "Dang co khach";
    if (choice == 3)
        return "Dang don dep";
    return "";
}

string getLoaiPhong(int choice)
{
    if (choice == 1)
        return "Don";
    if (choice == 2)
        return "Doi";
    return "VIP";
}

bool parseDate(const string &dateStr, int &day, int &month, int &year)
{
    if (dateStr.length() < 8 || dateStr.length() > 10)
        return false;
    int pos1 = dateStr.find('/'), pos2 = dateStr.find('/', pos1 + 1);
    if (pos1 == string::npos || pos2 == string::npos)
        return false;
    try
    {
        day = stoi(dateStr.substr(0, pos1));
        month = stoi(dateStr.substr(pos1 + 1, pos2 - pos1 - 1));
        year = stoi(dateStr.substr(pos2 + 1));
        return day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100;
    }
    catch (...)
    {
        return false;
    }
}

bool isValidPhoneNum(const string &phone)
{
    return phone.length() == 10 && phone[0] == '0' &&
           all_of(phone.begin(), phone.end(), ::isdigit);
}

bool isValidCCCD(const string &ma)
{
    if (ma.empty() || ma.length() < 9)
        return false;
    return all_of(ma.begin(), ma.end(), ::isalnum);
}

DateTime GetCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return DateTime(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, 0, 0);
}

DateTime GetDateTime(const string &message)
{
    string dateStr;
    cout << message;
    getline(cin, dateStr);
    int d, m, y;
    while (!parseDate(dateStr, d, m, y))
    {
        showFail("Vui long nhap theo dinh dang DD/MM/YYYY");
        cout << message;
        getline(cin, dateStr);
    }
    return DateTime(d, m, y, 0, 0);
}

void LoadUser()
{
    ifstream fin("accounts.txt");
    if (!fin.is_open())
        return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string usr, pw, fname, r;
        getline(ss, usr, '|');
        getline(ss, pw, '|');
        getline(ss, r, '|');
        getline(ss, fname, '|');
        ListAccount.Them(TaiKhoan(usr, pw, stoi(r), fname));
    }
    fin.close();
}

void SaveAccounts()
{
    ofstream fout("accounts.txt");
    if (!fout.is_open())
        return;
    for (const auto &acc : ListAccount.GetDanhSach())
        fout << acc.getUsername() << "|" << acc.getPassword() << "|"
             << acc.getRole() << "|" << acc.getFullName() << "\n";
    fout.close();
}

void SavePhong()
{
    ofstream fout("phong.txt");
    if (!fout.is_open())
        return;
    for (const auto &p : ListPhong.GetDanhSach())
        fout << p.getMaPhong() << "|" << p.getLoaiPhong() << "|"
             << p.getGiaPhong() << "|" << p.getTrangThai() << "\n";
    fout.close();
}

void LoadPhong()
{
    ifstream fin("phong.txt");
    if (!fin.is_open())
        return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string ma, loai, trangThai, token;
        getline(ss, ma, '|');
        getline(ss, loai, '|');
        getline(ss, token, '|');
        getline(ss, trangThai, '|');
        ListPhong.Them(Phong(ma, loai, stod(token), trangThai));
    }
    fin.close();
}

void SaveKhachHang()
{
    ofstream fout("khachhang.txt");
    if (!fout.is_open())
        return;
    for (const auto &kh : ListKhachHang.GetDanhSach())
        fout << kh.getMaKhach() << "|" << kh.getHoTen() << "|"
             << kh.getSoDienThoai() << "|" << kh.getNamSinh() << "\n";
    fout.close();
}

void LoadKhachHang()
{
    ifstream fin("khachhang.txt");
    if (!fin.is_open())
        return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string ma, ten, sdt, token;
        getline(ss, ma, '|');
        getline(ss, ten, '|');
        getline(ss, sdt, '|');
        getline(ss, token, '|');
        ListKhachHang.Them(KhachHang(ma, ten, sdt, stoi(token)));
    }
    fin.close();
}

void SaveBooking()
{
    ofstream fout("booking.txt");
    if (!fout.is_open())
        return;
    for (const auto &b : ListBooking.GetDanhSach())
    {
        DateTime ci = b.getCheckIn(), co = b.getCheckOutDuKien();
        fout << b.getMaBooking() << "|" << b.getMaKhach() << "|" << b.getMaPhong() << "|"
             << ci.getDay() << "," << ci.getMonth() << "," << ci.getYear() << "|"
             << co.getDay() << "," << co.getMonth() << "," << co.getYear() << "\n";
    }
    fout.close();
}

void LoadBooking()
{
    ifstream fin("booking.txt");
    if (!fin.is_open())
        return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string maBooking, maKhach, maPhong, ciStr, coStr;
        getline(ss, maBooking, '|');
        getline(ss, maKhach, '|');
        getline(ss, maPhong, '|');
        getline(ss, ciStr, '|');
        getline(ss, coStr, '|');

        auto parseDateTime = [](const string &s)
        {
            stringstream ss(s);
            string token;
            int d, m, y;
            getline(ss, token, ',');
            d = stoi(token);
            getline(ss, token, ',');
            m = stoi(token);
            getline(ss, token, ',');
            y = stoi(token);
            return DateTime(d, m, y, 0, 0);
        };

        ListBooking.Them(Booking(maBooking, maKhach, maPhong,
                                 parseDateTime(ciStr), parseDateTime(coStr)));
    }
    fin.close();
}

void SaveLichSu()
{
    ofstream fout("lichsu.txt");
    if (!fout.is_open())
        return;
    for (const auto &ls : ListLichSu.GetDanhSach())
    {
        DateTime nd = ls.getNgayDen(), ndi = ls.getNgayDi();
        fout << ls.getMaKhach() << "|" << ls.getMaPhong() << "|"
             << nd.getDay() << "," << nd.getMonth() << "," << nd.getYear() << ","
             << nd.getHour() << "," << nd.getMinute() << "|"
             << ndi.getDay() << "," << ndi.getMonth() << "," << ndi.getYear() << ","
             << ndi.getHour() << "," << ndi.getMinute() << "|"
             << ls.getTongTien() << "|" << ls.getNguoiCheckout() << "\n";
    }
    fout.close();
}

void LoadLichSu()
{
    ifstream fin("lichsu.txt");
    if (!fin.is_open())
        return;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string maKhach, maPhong, ndStr, ndiStr, tienStr, nguoiCheckout;
        getline(ss, maKhach, '|');
        getline(ss, maPhong, '|');
        getline(ss, ndStr, '|');
        getline(ss, ndiStr, '|');
        getline(ss, tienStr, '|');
        getline(ss, nguoiCheckout, '|');

        auto parseDateTime = [](const string &s)
        {
            stringstream ss(s);
            string token;
            int d, m, y, h, min;
            getline(ss, token, ',');
            d = stoi(token);
            getline(ss, token, ',');
            m = stoi(token);
            getline(ss, token, ',');
            y = stoi(token);
            getline(ss, token, ',');
            h = stoi(token);
            getline(ss, token, ',');
            min = stoi(token);
            return DateTime(d, m, y, h, min);
        };

        ListLichSu.Them(LichSuDatPhong(maKhach, maPhong,
                                       parseDateTime(ndStr), parseDateTime(ndiStr),
                                       stod(tienStr), nguoiCheckout));
    }
    fin.close();
}

void Init_Data()
{
    system("cls");
    cout << "Khoi tao du lieu he thong...\n";
    LoadUser();
    LoadPhong();
    LoadKhachHang();
    LoadBooking();
    LoadLichSu();
    S(0.75);
    cout << "[SUCCESS] Tai du lieu thanh cong.\n";
    S(2);
}

void CheckLogin()
{
    const int MAX_REQUEST = 3;
    int request_cnt = 0;

    while (request_cnt < MAX_REQUEST)
    {
        system("cls");
        string user, pass;
        cout << "============================ LOGIN PAGE ============================\n";
        cout << "[!] Con lai " << (MAX_REQUEST - request_cnt) << " lan thu.\n";
        cout << "Ten dang nhap: ";
        cin >> user;
        cout << "Mat khau: ";
        cin >> pass;
        S(0.5);
        cout << "Dang kiem tra thong tin dang nhap...\n";
        // S(1);

        for (const auto &acc : ListAccount.GetDanhSach())
        {
            if (acc.getUsername() == user && acc.getPassword() == pass)
            {
                cout << "[SUCCESS] Dang nhap thanh cong!\n";
                LoginedInAccount = acc;
                SoLuongLichSuBanDau = ListLichSu.GetSize();
                SoLuongBookingBanDau = ListBooking.GetSize();
                S(1);
                return;
            }
        }

        request_cnt++;
        cout << "[!] Dang nhap that bai! Vui long kiem tra lai ten dang nhap hoac mat khau.\n";
        if (request_cnt < MAX_REQUEST)
            cout << "Ban con " << (MAX_REQUEST - request_cnt) << " lan thu.\n";
        S(2);
    }

    throw Exceptions::AuthenticationFailedException("Dang nhap sai qua 3 lan. He thong se dong!");
}

void ShowMenu()
{
    system("cls");
    int role = LoginedInAccount.getRole();
    string fname = LoginedInAccount.getFullName();

    vector<tuple<string, int, int>> Menu = {
        {"Quan Li Le Tan", 2, 0},
        {"Quan Li Khach Hang", 1, 1},
        {"Quan Li Phong", 1, 2},
        {"Dat Phong (Check-in)", 1, 5},
        {"Tra Phong (Check-out)", 1, 6},
        {"Bao Cao & Lich Su", 1, 7},
        {"Chot Ca", 1, 3}};

    cout << "Xin chao, " << GetRole(role) << " " << fname << ".\n";
    cout << "============================ MAIN MENU ============================\n";

    vector<int> saveCase;
    int optionNumber = 1;

    for (const auto &option : Menu)
    {
        if (role >= get<1>(option))
        {
            cout << optionNumber << ". " << get<0>(option) << "\n";
            saveCase.push_back(get<2>(option));
            optionNumber++;
        }
    }

    cout << "Vui long chon chuc nang: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > (int)saveCase.size())
    {
        showFail("Lua chon khong hop le.");
        ShowMenu();
        return;
    }

    int funcIndex = saveCase[choice - 1];
    switch (funcIndex)
    {
    case 0:
        QuanLiNhanVien();
        break;
    case 1:
        QuanLiKhachHang();
        break;
    case 2:
        QuanLiPhong();
        break;
    case 3:
        ChotCa();
        break;
    case 5:
        DatPhong();
        break;
    case 6:
        TraPhong();
        break;
    case 7:
        BaoCaoLichSu();
        break;
    }

    // S(0.5);
    ShowMenu();
}

void LaunchSystem()
{
    try
    {
        CheckLogin();
        ShowMenu();
    }
    catch (const Exceptions::AuthenticationFailedException &e)
    {
        system("cls");
        cerr << "[!] " << e.what() << endl;
        exit(1);
    }
}

void HienThiDanhSachNhanVien()
{
    headMenu("DANH SACH LE TAN");
    if (ListAccount.IsEmpty())
    {
        cout << "[!] Danh sach le tan trong.\n";
    }
    else
    {
        cout << setw(5) << "STT" << setw(20) << "Ten dang nhap" << setw(15) << "Vai tro"
             << setw(30) << "Ho ten" << "\n"
             << string(70, '-') << "\n";
        for (int i = 0; i < ListAccount.GetSize(); i++)
        {
            const auto &acc = ListAccount.GetAt(i);
            cout << setw(5) << (i + 1) << setw(20) << acc.getUsername()
                 << setw(15) << GetRole(acc.getRole())
                 << setw(30) << acc.getFullName() << "\n";
        }
    }
    pause();
}

void ThemNhanVien()
{
    headMenu("THEM LE TAN");

    string username, password, fullname;
    int role;
    // cin.ignore();
    cout << "Ten dang nhap: ";
    getline(cin, username);
    if (username.empty())
    {
        showFail("Ten dang nhap khong duoc de trong!");
        return;
    }

    if (ListAccount.TimKiem(username) != -1)
    {
        showFail("Ten dang nhap da ton tai!");
        return;
    }

    cout << "Mat khau: ";
    getline(cin, password);
    if (password.empty())
    {
        showFail("Mat khau khong duoc de trong!");
        return;
    }

    cout << "Vai tro (1.Le tan, 2.Quan li): ";
    if (!(cin >> role) || (role != 1 && role != 2))
    {
        showFail("Vai tro khong hop le!");
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();

    cout << "Ho ten: ";
    getline(cin, fullname);
    if (fullname.empty())
    {
        showFail("Ho ten khong duoc de trong!");
        return;
    }

    ListAccount.Them(TaiKhoan(username, password, role, fullname));
    SaveAccounts();
    showSuccess("Them le tan thanh cong!");
}

void CapNhatNhanVien()
{
    headMenu("CAP NHAT LE TAN");

    string username;
    cout << "Nhap ten dang nhap can cap nhat: ";
    getline(cin, username);
    if (username.empty())
    {
        showFail("Ten dang nhap khong duoc de trong!");
        return;
    }

    int index = ListAccount.TimKiem(username);
    if (index == -1)
    {
        showFail("Khong tim thay le tan voi ten dang nhap: " + username);
        return;
    }

    if (ListAccount.GetAt(index).getUsername() == LoginedInAccount.getUsername())
    {
        showFail("Ban khong the cap nhat tai khoan dang dang nhap!");
        return;
    }

    while (true)
    {
        headMenu("CAP NHAT LE TAN");

        const auto &acc = ListAccount.GetAt(index);
        cout << "Ten dang nhap: " << acc.getUsername() << "\n";
        cout << "Mat khau: " << acc.getPassword() << "\n";
        cout << "Chuc vu: " << GetRole(acc.getRole()) << "\n";
        cout << "Ho ten: " << acc.getFullName() << "\n\n";
        cout << "1. Cap nhat username\n";
        cout << "2. Cap nhat password\n";
        cout << "3. Cap nhat chuc vu\n";
        cout << "4. Cap nhat ten\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";

        int choice;
        cin >> choice;
        cin.ignore();

        string newUsername = acc.getUsername();
        string newPassword = acc.getPassword();
        int newRole = acc.getRole();
        string newFullname = acc.getFullName();

        string usernameInput, passwordInput, roleInput, fullnameInput;
        int inputRole;

        switch (choice)
        {
        case 1:
            cout << "Username hien tai: " << newUsername << "\nUsername moi: ";
            getline(cin, usernameInput);
            if (usernameInput.empty())
            {
                showFail("Username khong duoc de trong!");
                S(1);
                break;
            }
            if (ListAccount.TimKiem(usernameInput) != -1 && usernameInput != newUsername)
            {
                showFail("Username da ton tai!");
                break;
            }
            newUsername = usernameInput;
            ListAccount.GetAt(index) = TaiKhoan(newUsername, newPassword, newRole, newFullname);
            index = ListAccount.TimKiem(newUsername);
            showSuccess("Cap nhat username thanh cong!");
            return;
            // break;
        case 2:
            cout << "Nhap mat khau moi: ";
            getline(cin, passwordInput);
            if (passwordInput.empty())
            {
                showFail("Mat khau khong duoc de trong!");
                S(1);
                break;
            }
            ListAccount.GetAt(index) = TaiKhoan(newUsername, passwordInput, newRole, newFullname);
            showSuccess("Cap nhat password thanh cong!");
            return;
            // break;
        case 3:
            cout << "Chuc vu hien tai: " << GetRole(newRole) << "\n";
            cout << "Chuc vu moi (1 = Le tan, 2 = Quan li): ";
            getline(cin, roleInput);
            if (roleInput.empty())
            {
                cout << "[!] Huy cap nhat.\n";
                S(1);
                break;
            }
            try
            {
                inputRole = stoi(roleInput);
                if (inputRole == 1 || inputRole == 2)
                {
                    ListAccount.GetAt(index) = TaiKhoan(newUsername, newPassword, inputRole, newFullname);
                    showSuccess("Cap nhat chuc vu thanh cong!");
                    return;
                }
                else
                {
                    showFail("Vai tro khong hop le!");
                }
            }
            catch (...)
            {
                showFail("Gia tri khong hop le!");
            }
            break;
        case 4:
            cout << "Ho ten hien tai: " << newFullname << "\nHo ten moi: ";
            getline(cin, fullnameInput);
            if (fullnameInput.empty())
            {
                cout << "[!] Huy cap nhat.\n";
                S(1);
                break;
            }
            ListAccount.GetAt(index) = TaiKhoan(newUsername, newPassword, newRole, fullnameInput);
            showSuccess("Cap nhat ho ten thanh cong!");
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
        SaveAccounts();
    }
}

void XoaNhanVien()
{
    headMenu("XOA LE TAN");

    string username;
    cout << "Nhap ten dang nhap can xoa: ";
    getline(cin, username);
    if (username.empty())
    {
        showFail("Ten dang nhap khong duoc de trong!");
        return;
    }

    int index = ListAccount.TimKiem(username);
    if (index == -1)
    {
        showFail("Khong tim thay le tan voi ten dang nhap: " + username);
        pause();
        return;
    }

    if (ListAccount.GetAt(index).getUsername() == LoginedInAccount.getUsername())
    {
        showFail("Ban khong the xoa tai khoan dang dang nhap!");
        pause();
        return;
    }

    const auto &acc = ListAccount.GetAt(index);
    cout << "\nThong tin le tan se bi xoa:\n";
    cout << "Ten dang nhap: " << acc.getUsername() << "\n";
    cout << "Vai tro: " << GetRole(acc.getRole()) << "\n";
    cout << "Ho ten: " << acc.getFullName() << "\n\n";

    cout << "Ban co chac chan muon xoa? (y/n): ";
    string confirmStr;
    getline(cin, confirmStr);
    if (confirmStr.empty() || (tolower(confirmStr[0]) != 'y' && tolower(confirmStr[0]) != 'n'))
    {
        showFail("Lua chon khong hop le!");
        return;
    }

    if (tolower(confirmStr[0]) == 'y')
    {
        ListAccount.Xoa(username);
        SaveAccounts();
        showSuccess("Xoa le tan thanh cong!");
    }
    else
    {
        cout << "\n[!] Huy thao tac xoa.\n";
        S(2);
    }
}

void TimKiemNhanVien()
{
    headMenu("TIM KIEM LE TAN");

    string key;
    cout << "Nhap ten dang nhap hoac ho ten can tim: ";
    getline(cin, key);
    if (key.empty())
    {
        showFail("Tu khoa tim kiem khong duoc de trong!");
        return;
    }

    vector<int> list;
    for (int i = 0; i < ListAccount.GetSize(); i++)
    {
        const auto &acc = ListAccount.GetAt(i);
        if (acc.getUsername().find(key) != string::npos ||
            acc.getFullName().find(key) != string::npos)
        {
            list.push_back(i);
        }
    }

    if (list.empty())
    {
        cout << "[!] Khong tim thay le tan nao.\n";
    }
    else
    {
        cout << "\nKet qua tim kiem:\n";
        cout << setw(5) << "STT" << setw(20) << "Ten dang nhap" << setw(15) << "Vai tro"
             << setw(30) << "Ho ten" << "\n"
             << string(70, '-') << "\n";
        for (int i = 0; i < (int)list.size(); i++)
        {
            const auto &acc = ListAccount.GetAt(list[i]);
            cout << setw(5) << (i + 1) << setw(20) << acc.getUsername()
                 << setw(15) << GetRole(acc.getRole())
                 << setw(30) << acc.getFullName() << "\n";
        }
    }
    pause();
}

void QuanLiNhanVien()
{
    while (true)
    {
        headMenu("QUAN LI LE TAN");
        cout << "1. Hien thi danh sach le tan\n";
        cout << "2. Them le tan moi\n";
        cout << "3. Cap nhat thong tin le tan\n";
        cout << "4. Xoa le tan\n";
        cout << "5. Tim kiem le tan\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "\nVui long chon chuc nang: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            HienThiDanhSachNhanVien();
            break;
        case 2:
            ThemNhanVien();
            break;
        case 3:
            CapNhatNhanVien();
            break;
        case 4:
            XoaNhanVien();
            break;
        case 5:
            TimKiemNhanVien();
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void QuanLiKhachHang()
{
    while (true)
    {
        headMenu("QUAN LI KHACH HANG");
        cout << "1. Hien thi danh sach khach hang\n";
        cout << "2. Cap nhat thong tin khach hang\n";
        cout << "3. Tim kiem khach hang\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string ten, sdt, ma, key;
        int namSinh, index;
        bool found;
        const KhachHang *khPtr = nullptr;

        switch (choice)
        {
        case 1:
        {
            headMenu("DANH SACH KHACH HANG");
            if (ListKhachHang.IsEmpty())
            {
                cout << "[!] Danh sach khach hang trong.\n";
            }
            else
            {
                cout << setw(5) << "STT" << setw(20) << "Ma khach hang" << setw(30) << "Ho ten"
                     << setw(15) << "So dien thoai" << setw(10) << "Nam sinh" << "\n";
                cout << string(90, '-') << "\n";
                for (int i = 0; i < ListKhachHang.GetSize(); i++)
                {
                    const auto &kh = ListKhachHang.GetAt(i);
                    cout << setw(5) << (i + 1) << setw(20) << kh.getMaKhach()
                         << setw(30) << kh.getHoTen() << setw(15) << kh.getSoDienThoai()
                         << setw(10) << kh.getNamSinh() << "\n";
                }
            }
            pause();
            break;
        }
        case 2:
            headMenu("CAP NHAT THONG TIN KHACH HANG");

            if (ListKhachHang.IsEmpty())
            {
                cout << "[!] Danh sach khach hang trong.\n";
                pause();
                break;
            }

            cout << "Nhap ma khach hang: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma khach hang khong duoc de trong!");
                break;
            }
            index = ListKhachHang.TimKiem(ma);
            if (index == -1)
            {
                showFail("Khong tim thay khach hang!");
                break;
            }
            khPtr = &ListKhachHang.GetAt(index);
            cout << "Thong tin hien tai:\n";
            khPtr->hienThi();
            cout << "\nNhap thong tin moi:\n";
            cout << "Ho ten: ";
            getline(cin, ten);
            if (ten.empty())
            {
                showFail("Ho ten khong duoc de trong!");
                break;
            }
            cout << "So dien thoai: ";
            getline(cin, sdt);
            if (sdt.empty())
            {
                showFail("So dien thoai khong duoc de trong!");
                break;
            }
            if (!isValidPhoneNum(sdt))
            {
                showFail("So dien thoai khong hop le!");
                break;
            }
            cout << "Nam sinh: ";
            if (!(cin >> namSinh) || namSinh < 1900 || namSinh > 2024)
            {
                showFail("Nam sinh khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            ListKhachHang.GetAt(index).setHoTen(ten);
            ListKhachHang.GetAt(index).setSoDienThoai(sdt);
            ListKhachHang.GetAt(index).setNamSinh(namSinh);
            SaveKhachHang();
            showSuccess("Cap nhat thanh cong!");

            break;
        case 3:
            headMenu("TIM KIEM KHACH HANG");
            if (ListKhachHang.IsEmpty())
            {
                cout << "[!] Danh sach khach hang trong.\n";
                pause();
                break;
            }
            cout << "Nhap ma khach hang hoac ten: ";
            getline(cin, key);
            if (key.empty())
            {
                showFail("Tu khoa tim kiem khong duoc de trong!");
                break;
            }
            found = false;
            for (int i = 0; i < ListKhachHang.GetSize(); i++)
            {
                const auto &kh = ListKhachHang.GetAt(i);
                if (kh.getMaKhach().find(key) != string::npos ||
                    kh.getHoTen().find(key) != string::npos)
                {
                    if (!found)
                    {
                        cout << setw(5) << "ID" << setw(20) << "Ma khach hang" << setw(30) << "Ho ten"
                             << setw(15) << "So dien thoai" << setw(10) << "Nam sinh" << "\n";
                        cout << string(90, '-') << "\n";
                    }
                    cout << setw(5) << (i + 1) << setw(20) << kh.getMaKhach()
                         << setw(30) << kh.getHoTen() << setw(15) << kh.getSoDienThoai()
                         << setw(10) << kh.getNamSinh() << "\n";
                    found = true;
                }
            }
            if (!found)
            {
                cout << "[!] Khong tim thay khach hang nao!\n";
            }
            pause();
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void MenuCapNhatPhong()
{
    while (true)
    {
        headMenu("CAP NHAT PHONG");
        cout << "1. Cap nhat trang thai phong\n";
        cout << "2. Cap nhat gia phong\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string ma, trangThai;
        int index, trangThaiChoice;
        double gia;

        switch (choice)
        {
        case 1:
            headMenu("CAP NHAT TRANG THAI PHONG");
            cout << "Nhap ma phong: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma phong khong duoc de trong!");
                break;
            }
            index = ListPhong.TimKiem(ma);
            if (index == -1)
            {
                showFail("Khong tim thay phong!");
                break;
            }
            cout << "Trang thai hien tai: " << ListPhong.GetAt(index).getTrangThai() << "\n";
            cout << "Trang thai moi:\n";
            cout << "1. Trong\n";
            cout << "2. Dang co khach\n";
            cout << "3. Dang don dep\n";
            cout << "Chon trang thai: ";
            if (!(cin >> trangThaiChoice) || trangThaiChoice < 1 || trangThaiChoice > 3)
            {
                showFail("Lua chon trang thai khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            trangThai = getTrangThai(trangThaiChoice);
            if (trangThai.empty())
            {
                showFail("Lua chon khong hop le!");
                break;
            }
            ListPhong.GetAt(index).setTrangThai(trangThai);
            SavePhong();
            showSuccess("Cap nhat thanh cong!");
            break;
        case 2:
            headMenu("CAP NHAT GIA PHONG");
            cout << "Nhap ma phong: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma phong khong duoc de trong!");
                break;
            }
            index = ListPhong.TimKiem(ma);
            if (index == -1)
            {
                showFail("Khong tim thay phong!");
                break;
            }
            cout << "Gia hien tai: " << formatTien(ListPhong.GetAt(index).getGiaPhong()) << " VND\n";
            cout << "Gia moi: ";
            if (!(cin >> gia) || gia <= 0)
            {
                showFail("Gia phong khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            ListPhong.GetAt(index).setGiaPhong(gia);
            SavePhong();
            showSuccess("Cap nhat thanh cong!");
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void MenuTimKiemPhong()
{
    while (true)
    {
        headMenu("TIM KIEM PHONG");
        cout << "1. Tim kiem phong theo ma\n";
        cout << "2. Tim kiem phong theo trang thai\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string ma, trangThai;
        int index, trangThaiChoice;
        // bool found;

        switch (choice)
        {
        case 1:
            headMenu("TIM KIEM PHONG THEO MA");
            cout << "Nhap ma phong: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma phong khong duoc de trong!");
                break;
            }
            index = ListPhong.TimKiem(ma);
            if (index == -1)
            {
                cout << "[!] Khong tim thay phong!\n";
            }
            else
            {
                ListPhong.GetAt(index).hienThi();
            }
            pause();
            break;
        case 2:
        {
            headMenu("TIM KIEM PHONG THEO TRANG THAI");
            cout << "Chon trang thai:\n";
            cout << "1. Trong\n";
            cout << "2. Dang co khach\n";
            cout << "3. Dang don dep\n";
            cout << "Chon trang thai (1-3): ";
            if (!(cin >> trangThaiChoice) || trangThaiChoice < 1 || trangThaiChoice > 3)
            {
                showFail("Lua chon trang thai khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            trangThai = getTrangThai(trangThaiChoice);
            if (trangThai.empty())
            {
                showFail("Lua chon khong hop le!");
                break;
            }

            vector<int> danhSachPhong;
            for (int i = 0; i < ListPhong.GetSize(); i++)
            {
                if (ListPhong.GetAt(i).getTrangThai() == trangThai)
                {
                    danhSachPhong.push_back(i);
                }
            }

            if (danhSachPhong.empty())
            {
                cout << "[!] Khong tim thay phong nao!\n";
            }
            else
            {
                system("cls");
                headMenu("KET QUA TIM KIEM PHONG THEO TRANG THAI: " + trangThai);
                cout << "So luong: " << danhSachPhong.size() << " phong\n\n";
                cout << setw(5) << "STT" << setw(15) << "Ma phong" << setw(15) << "Loai phong"
                     << setw(20) << "Gia (VND)" << setw(20) << "Trang thai" << "\n";
                cout << string(75, '-') << "\n";
                for (int i = 0; i < danhSachPhong.size(); i++)
                {
                    const auto &p = ListPhong.GetAt(danhSachPhong[i]);
                    cout << setw(5) << (i + 1) << setw(15) << p.getMaPhong() << setw(15) << p.getLoaiPhong()
                         << setw(20) << formatTien(p.getGiaPhong()) << setw(20) << p.getTrangThai() << "\n";
                }
            }
            pause();
            break;
        }
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void QuanLiPhong()
{
    while (true)
    {
        headMenu("QUAN LI PHONG");
        cout << "1. Hien thi danh sach phong\n";
        cout << "2. Them phong moi\n";
        cout << "3. Cap nhat phong\n";
        cout << "4. Xoa phong\n";
        cout << "5. Tim kiem phong\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string ma, loai, trangThai;
        double gia;
        int loaiChoice;

        switch (choice)
        {
        case 1:
            headMenu("DANH SACH PHONG");
            if (ListPhong.IsEmpty())
            {
                cout << "[!] Danh sach phong trong.\n";
            }
            else
            {
                cout << setw(5) << "STT" << setw(15) << "Ma phong" << setw(15) << "Loai phong"
                     << setw(20) << "Gia (VND)" << setw(20) << "Trang thai" << "\n";
                cout << string(75, '-') << "\n";
                for (int i = 0; i < ListPhong.GetSize(); i++)
                {
                    auto &p = ListPhong.GetAt(i);
                    cout << setw(5) << (i + 1) << setw(15) << p.getMaPhong() << setw(15) << p.getLoaiPhong()
                         << setw(20) << formatTien(p.getGiaPhong()) << setw(20) << p.getTrangThai() << "\n";
                }
            }
            pause();
            break;
        case 2:
            headMenu("THEM PHONG MOI");
            cout << "Ma phong: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma phong khong duoc de trong!");
                break;
            }
            if (ListPhong.TimKiem(ma) != -1)
            {
                showFail("Ma phong da ton tai!");
                break;
            }
            cout << "Loai phong:\n";
            cout << "1. Don\n";
            cout << "2. Doi\n";
            cout << "3. VIP\n";
            cout << "Chon loai phong: ";
            if (!(cin >> loaiChoice) || loaiChoice < 1 || loaiChoice > 3)
            {
                showFail("Lua chon loai phong khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            loai = getLoaiPhong(loaiChoice);
            cout << "Gia phong/dem: ";
            if (!(cin >> gia) || gia <= 0)
            {
                showFail("Gia phong khong hop le!");
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            cin.ignore();
            trangThai = "Trong";
            ListPhong.Them(Phong(ma, loai, gia, trangThai));
            SavePhong();
            showSuccess("Them phong thanh cong!");
            break;
        case 3:
            MenuCapNhatPhong();
            break;
        case 4:
            headMenu("XOA PHONG");
            cout << "Nhap ma phong can xoa: ";
            getline(cin, ma);
            if (ma.empty())
            {
                showFail("Ma phong khong duoc de trong!");
                break;
            }
            if (ListPhong.TimKiem(ma) == -1)
            {
                showFail("Khong tim thay phong!");
                break;
            }
            ListPhong.Xoa(ma);
            SavePhong();
            showSuccess("Xoa phong thanh cong!");
            break;
        case 5:
            MenuTimKiemPhong();
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void DatPhong()
{
    headMenu("CHECK IN");
    try
    {
        string maPhong, maKhach, loaiPhong;
        int loaiChoice;

        cout << "Chon loai phong:\n";
        cout << "1. Don\n";
        cout << "2. Doi\n";
        cout << "3. VIP\n";
        cout << "Chon loai phong: ";
        if (!(cin >> loaiChoice) || loaiChoice < 1 || loaiChoice > 3)
        {
            showFail("Lua chon loai phong khong hop le!");
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        cin.ignore();
        loaiPhong = getLoaiPhong(loaiChoice);

        int phongIndex = -1;
        for (int i = 0; i < ListPhong.GetSize(); i++)
        {
            if (ListPhong.GetAt(i).getLoaiPhong() == loaiPhong &&
                ListPhong.GetAt(i).getTrangThai() == "Trong")
            {
                phongIndex = i;
                break;
            }
        }

        if (phongIndex == -1)
        {
            throw Exceptions::RoomNotAvailableException("Khong co phong " + loaiPhong + " nao trong! Vui long chon loai phong khac.");
            return;
        }

        maPhong = ListPhong.GetAt(phongIndex).getMaPhong();
        const auto &phongDuocChon = ListPhong.GetAt(phongIndex);
        cout << "[!] Phong: " << maPhong << " - Gia: " << formatTien(phongDuocChon.getGiaPhong()) << " VND\n";

        string hoTen, soDienThoai;
        int namSinh;

        cout << "Ma khach hang (CCCD): ";
        getline(cin, maKhach);
        if (maKhach.empty())
        {
            showFail("Ma khach hang khong duoc de trong!");
            return;
        }

        int khachHangIndex = ListKhachHang.TimKiem(maKhach);
        if (khachHangIndex != -1)
        {
            const auto &kh = ListKhachHang.GetAt(khachHangIndex);
            cout << "[!] Su dung thong tin khach hang: " << kh.getHoTen() << "\n";
        }
        else
        {
            if (!isValidCCCD(maKhach))
            {
                throw Exceptions::InvalidCustomerInfoException("Ma khach hang khong hop le!");
            }

            cout << "Ho ten: ";
            getline(cin, hoTen);
            if (hoTen.empty())
            {
                throw Exceptions::InvalidCustomerInfoException("Ho ten khong duoc de trong!");
            }

            cout << "So dien thoai: ";
            getline(cin, soDienThoai);
            if (!isValidPhoneNum(soDienThoai))
            {
                throw Exceptions::InvalidCustomerInfoException("So dien thoai khong hop le!");
            }

            cout << "Nam sinh: ";
            if (!(cin >> namSinh) || namSinh < 1900 || namSinh > 2024)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                throw Exceptions::InvalidCustomerInfoException("Nam sinh khong hop le!");
            }
            cin.ignore();

            ListKhachHang.Them(KhachHang(maKhach, hoTen, soDienThoai, namSinh));
            SaveKhachHang();
        }

        //  DateTime checkIn = GetCurrentDate();
        DateTime checkIn = GetDateTime("Nhap ngay check-in: ");

        DateTime checkOut = GetDateTime("Nhap ngay check-out du kien: ");

        string maBooking = "BK" + to_string(ListBooking.GetSize() + 1);
        ListBooking.Them(Booking(maBooking, maKhach, maPhong, checkIn, checkOut));
        ListPhong.GetAt(phongIndex).setTrangThai("Dang co khach");
        SaveBooking();
        SavePhong();
        showSuccess("Dat phong thanh cong! Ma booking: " + maBooking);
    }
    catch (const Exceptions::RoomNotAvailableException &e)
    {
        showFail(e.what());
    }
    catch (const Exceptions::InvalidCustomerInfoException &e)
    {
        showFail(e.what());
    }
}

void TraPhong()
{
    headMenu("TRA PHONG (CHECK-OUT)");
    string input;
    cout << "Nhap ma booking, ma phong hoac ma khach hang: ";
    getline(cin, input);

    if (input.empty())
    {
        showFail("Khong duoc de trong!");
        return;
    }

    int bookingIndex = -1;
    for (int i = 0; i < ListBooking.GetSize(); i++)
    {
        const auto &booking = ListBooking.GetAt(i);
        if (booking.getMaBooking() == input ||
            booking.getMaPhong() == input ||
            booking.getMaKhach() == input)
        {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1)
    {
        showFail("Khong tim thay booking!");
        if (ListBooking.GetSize() > 0)
        {
            cout << "\nDanh sach booking hien co:\n";
            for (int i = 0; i < ListBooking.GetSize(); i++)
            {
                const auto &b = ListBooking.GetAt(i);
                cout << "- " << b.getMaBooking() << " | Phong: " << b.getMaPhong()
                     << " | Khach: " << b.getMaKhach() << "\n";
            }
        }
        return;
    }

    Booking &booking = ListBooking.GetAt(bookingIndex);
    string maPhongBooking = booking.getMaPhong();

    cout << "\nThong tin booking:\n";
    cout << "Ma booking: " << booking.getMaBooking() << "\n";
    cout << "Ma phong: " << maPhongBooking << "\n";
    cout << "Ma khach hang: " << booking.getMaKhach() << "\n";
    cout << "Ngay check-in: ";
    booking.getCheckIn().hienThi();
    cout << "\n";
    cout << "Ngay check-out du kien: ";
    booking.getCheckOutDuKien().hienThi();
    cout << "\n";

    int phongIndex = ListPhong.TimKiem(maPhongBooking);
    double giaPhong = 0;

    if (phongIndex == -1)
    {
        cout << "[WARNING] Phong khong co trong danh sach hien tai. Vui long nhap gia phong/dem: ";
        if (!(cin >> giaPhong) || giaPhong <= 0)
        {
            showFail("Gia phong khong hop le!");
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        cin.ignore();
    }
    else
    {
        giaPhong = ListPhong.GetAt(phongIndex).getGiaPhong();
        cout << "Gia phong/dem: " << formatTien((long long)giaPhong) << " VND\n";
    }

    DateTime checkIn = booking.getCheckIn();
    DateTime checkOutDuKien = booking.getCheckOutDuKien();
    DateTime checkOut = GetCurrentDate();

    cout << "\nNgay check-out du kien: ";
    checkOutDuKien.hienThi();
    cout << "\n";
    cout << "Ngay check-out hien tai: ";
    checkOut.hienThi();
    cout << "\n";
    cout << "Nhap ngay check-out: ";
    string dateStr;
    getline(cin, dateStr);

    if (!dateStr.empty())
    {
        int d, m, y;
        if (!parseDate(dateStr, d, m, y))
        {
            showFail("Ngay khong hop le! Vui long nhap theo dinh dang DD/MM/YYYY");
            return;
        }
        checkOut = DateTime(d, m, y, 0, 0);
    }
    else
    {
        cout << "[!] Su dung ngay check-out hien tai: ";
        checkOut.hienThi();
        cout << "\n";
    }

    int soNgay = checkIn.soNgay(checkOut);
    if (soNgay == 0)
        soNgay = 1;
    long long tongTien = soNgay * giaPhong;
    system("cls");
    cout << "\n============================ HOA DON ============================\n";
    cout << "Ma booking: " << booking.getMaBooking() << "\n";
    cout << "Ma phong: " << maPhongBooking << "\n";
    cout << "Ma khach hang: " << booking.getMaKhach() << "\n";
    cout << "Ngay check-in: ";
    checkIn.hienThi();
    cout << "\n";
    cout << "Ngay check-out: ";
    checkOut.hienThi();
    cout << "\n";
    cout << "So ngay o: " << soNgay << "\n";
    cout << "Gia phong/dem: " << formatTien((long long)giaPhong) << " VND\n";
    cout << "Tong tien: " << formatTien((long long)tongTien) << " VND\n";
    cout << "============================\n";

    cout << "\nXac nhan khach hang da thanh toan? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (confirm.empty() || (tolower(confirm[0]) != 'y'))
    {
        cout << "[!] Huy thao tac tra phong.\n";
        pause();
        return;
    }

    ListLichSu.Them(LichSuDatPhong(booking.getMaKhach(), maPhongBooking, checkIn, checkOut, tongTien, LoginedInAccount.getUsername()));

    if (phongIndex != -1)
    {
        ListPhong.GetAt(phongIndex).setTrangThai("Dang don dep");
        SavePhong();
    }

    ListBooking.Xoa(booking.getMaBooking());

    SaveLichSu();
    SaveBooking();

    showSuccess("Tra phong thanh cong!");
}

void BaoCaoLichSu()
{
    while (true)
    {
        headMenu("BAO CAO & LICH SU");
        cout << "1. Hien thi toan bo lich su\n";
        cout << "2. Tra cuu lich su theo ma khach hang\n";
        cout << "3. Bao cao lich su theo ngay\n";
        cout << "0. Quay lai\n";
        cout << "\nVui long chon: ";
        int choice;
        cin >> choice;
        cin.ignore();

        double tongDoanhThu, tongTien;
        string maKhach, dateStr;
        int soLan, soGiaoDich;
        bool found;
        DateTime targetDate;

        switch (choice)
        {
        case 1:
            headMenu("TOAN BO LICH SU");
            if (ListLichSu.IsEmpty())
            {
                cout << "[!] Chua co lich su nao!\n";
            }
            else
            {
                cout << setw(5) << "STT" << setw(18) << "Ma khach hang" << setw(12) << "Ma phong"
                     << setw(12) << "Ngay den" << setw(12) << "Ngay di" << setw(18) << "Nguoi checkout"
                     << setw(18) << "Tong tien (VND)" << "\n";
                cout << string(92, '-') << "\n";

                tongDoanhThu = 0;
                for (int i = 0; i < ListLichSu.GetSize(); i++)
                {
                    const auto &ls = ListLichSu.GetAt(i);
                    DateTime ngayDen = ls.getNgayDen();
                    DateTime ngayDi = ls.getNgayDi();
                    int soNgay = ngayDen.soNgay(ngayDi);
                    if (soNgay == 0)
                        soNgay = 1;

                    cout << setw(5) << (i + 1)
                         << setw(18) << ls.getMaKhach()
                         << setw(12) << ls.getMaPhong()
                         << setw(12) << ngayDen.toString()
                         << setw(12) << ngayDi.toString()
                         << setw(18) << (ls.getNguoiCheckout().empty() ? "N/A" : ls.getNguoiCheckout())
                         << setw(18) << formatTien((long long)ls.getTongTien()) << "\n";

                    tongDoanhThu += ls.getTongTien();
                }
                cout << string(92, '-') << "\n";
                cout << setw(71) << left << "TONG CONG: "
                     << setw(18) << right << formatTien((long long)tongDoanhThu) << " VND\n";
            }
            pause();
            break;
        case 2:
            headMenu("TRA CUU LICH SU THEO KHACH HANG");
            cout << "Nhap ma khach hang: ";
            getline(cin, maKhach);
            if (maKhach.empty())
            {
                showFail("Ma khach hang khong duoc de trong!");
                break;
            }

            found = false;
            soLan = 0;
            tongTien = 0;
            for (int i = 0; i < ListLichSu.GetSize(); i++)
            {
                if (ListLichSu.GetAt(i).getMaKhach() == maKhach)
                {
                    ListLichSu.GetAt(i).hienThi();
                    soLan++;
                    tongTien += ListLichSu.GetAt(i).getTongTien();
                    found = true;
                }
            }

            if (found)
            {
                cout << "\nTong so lan: " << soLan << "\n";
                cout << "Tong tien da chi: " << formatTien((long long)tongTien) << " VND\n";
            }
            else
            {
                cout << "[!] Khong tim thay lich su!\n";
            }
            pause();
            break;
        case 3:
            headMenu("BAO CAO LICH SU THEO NGAY");
            cout << "Nhap ngay can bao cao: ";
            getline(cin, dateStr);

            if (dateStr.empty())
            {
                targetDate = GetCurrentDate();
            }
            else
            {
                int d, m, y;
                if (!parseDate(dateStr, d, m, y))
                {
                    showFail("Ngay khong hop le! Vui long nhap theo dinh dang DD/MM/YYYY");
                    break;
                }
                targetDate = DateTime(d, m, y, 0, 0);
            }

            found = false;
            tongTien = 0;
            soGiaoDich = 0;

            cout << "\nLich su ngay ";
            targetDate.hienThi();
            cout << ":\n";
            cout << setw(5) << "STT" << setw(18) << "Ma khach hang" << setw(12) << "Ma phong"
                 << setw(12) << "Ngay den" << setw(12) << "Ngay di" << setw(18) << "Tong tien (VND)" << "\n";
            cout << string(77, '-') << "\n";

            for (int i = 0; i < ListLichSu.GetSize(); i++)
            {
                const auto &ls = ListLichSu.GetAt(i);
                DateTime ngayDi = ls.getNgayDi();

                if (ngayDi.getDay() == targetDate.getDay() &&
                    ngayDi.getMonth() == targetDate.getMonth() &&
                    ngayDi.getYear() == targetDate.getYear())
                {
                    if (!found)
                    {
                        found = true;
                    }
                    soGiaoDich++;
                    tongTien += ls.getTongTien();

                    DateTime ngayDen = ls.getNgayDen();
                    cout << setw(5) << soGiaoDich
                         << setw(18) << ls.getMaKhach()
                         << setw(12) << ls.getMaPhong()
                         << setw(12) << ngayDen.toString()
                         << setw(12) << ngayDi.toString()
                         << setw(18) << formatTien((long long)ls.getTongTien()) << "\n";
                }
            }

            if (found)
            {
                cout << string(77, '-') << "\n";
                cout << setw(47) << left << "TONG CONG: "
                     << setw(18) << right << formatTien((long long)tongTien) << " VND\n";
                cout << "\nSo giao dich: " << soGiaoDich << "\n";
            }
            else
            {
                cout << "[!] Khong co lich su nao trong ngay nay!\n";
            }
            pause();
            break;
        case 0:
            return;
        default:
            showFail("Lua chon khong hop le!");
            break;
        }
    }
}

void ChotCa()
{
    SaveAccounts();
    SavePhong();
    SaveKhachHang();
    SaveBooking();
    SaveLichSu();
    system("cls");
    cout << "============================ CHOT CA ============================\n";

    double doanhThuThucTe = 0;
    int soGiaoDichThucTe = 0;

    for (int i = SoLuongLichSuBanDau; i < ListLichSu.GetSize(); i++)
    {
        doanhThuThucTe += ListLichSu.GetAt(i).getTongTien();
        soGiaoDichThucTe++;
    }

    int soPhongDatDuoc = soGiaoDichThucTe + (ListBooking.GetSize() - SoLuongBookingBanDau);
    int doanhThuUocTinh = 0;

    DateTime ngayHienTai = GetCurrentDate();
    for (int i = 0; i < ListBooking.GetSize(); i++)
    {
        const auto &booking = ListBooking.GetAt(i);
        DateTime checkOutDuKien = booking.getCheckOutDuKien();

        if (checkOutDuKien.getDay() == ngayHienTai.getDay() &&
            checkOutDuKien.getMonth() == ngayHienTai.getMonth() &&
            checkOutDuKien.getYear() == ngayHienTai.getYear())
        {
            string maPhong = booking.getMaPhong();
            int phongIndex = ListPhong.TimKiem(maPhong);

            if (phongIndex != -1)
            {
                int giaPhong = ListPhong.GetAt(phongIndex).getGiaPhong();
                DateTime checkIn = booking.getCheckIn();
                int soNgay = checkIn.soNgay(checkOutDuKien);
                if (soNgay == 0)
                    soNgay = 1;
                doanhThuUocTinh += soNgay * giaPhong;
            }
        }
    }

    cout << "\nThong tin le tan:\n";
    cout << "Ho ten: " << LoginedInAccount.getFullName() << "\n";
    cout << "Username: " << LoginedInAccount.getUsername() << "\n";
    cout << "Vai tro: " << GetRole(LoginedInAccount.getRole()) << "\n";

    cout << "\n============================ BANG TONG KET CA ============================\n";
    cout << setw(5) << right << "STT" << " " << setw(17) << left << "Ma khach hang" << setw(12) << left << "Ma phong"
         << setw(12) << left << "Ngay den" << setw(12) << left << "Ngay di" << setw(10) << right << "So ngay"
         << setw(18) << right << "Tong tien (VND)" << setw(15) << "Trang thai" << "\n";
    cout << string(102, '-') << "\n";

    int stt = 1;
    bool flagGiaoDich = false;

    // Show GD CHECKED OUT
    if (soGiaoDichThucTe > 0)
    {
        flagGiaoDich = true;
        for (int i = SoLuongLichSuBanDau; i < ListLichSu.GetSize(); i++)
        {
            const auto &ls = ListLichSu.GetAt(i);
            DateTime ngayDen = ls.getNgayDen();
            DateTime ngayDi = ls.getNgayDi();

            int soNgay = ngayDen.soNgay(ngayDi);
            if (soNgay == 0)
                soNgay = 1;

            cout << setw(5) << right << stt++ << " "
                 << setw(17) << left << ls.getMaKhach()
                 << setw(12) << left << ls.getMaPhong()
                 << setw(12) << left << ngayDen.toString()
                 << setw(12) << left << ngayDi.toString()
                 << setw(10) << right << soNgay
                 << setw(18) << right << formatTien((long long)ls.getTongTien())
                 << setw(15) << right << "Da checkout" << "\n";
        }
    }

    // CHUA CHECKOUT
    for (int i = SoLuongBookingBanDau; i < ListBooking.GetSize(); i++)
    {
        flagGiaoDich = true;
        const auto &booking = ListBooking.GetAt(i);
        string maPhong = booking.getMaPhong();
        int phongIndex = ListPhong.TimKiem(maPhong);

        DateTime checkIn = booking.getCheckIn();
        DateTime checkOutDuKien = booking.getCheckOutDuKien();
        int soNgay = checkIn.soNgay(checkOutDuKien);
        if (soNgay == 0)
            soNgay = 1;

        long long tongTien = 0;
        if (phongIndex != -1)
        {
            int giaPhong = ListPhong.GetAt(phongIndex).getGiaPhong();
            tongTien = soNgay * giaPhong;
        }

        cout << setw(5) << right << stt++ << " "
             << setw(17) << left << booking.getMaKhach()
             << setw(12) << left << booking.getMaPhong()
             << setw(12) << left << checkIn.toString()
             << setw(12) << left << checkOutDuKien.toString()
             << setw(10) << right << soNgay
             << setw(18) << right << formatTien(tongTien)
             << setw(15) << right << "Chua Checkout" << "\n";
    }

    if (!flagGiaoDich)
    {
        cout << setw(102) << "Khong co giao dich nao trong ca nay\n";
    }

    cout << string(102, '-') << "\n";
    cout << setw(76) << left << "TONG CONG:"
         << setw(18) << right << formatTien((long long)doanhThuThucTe) << " VND\n";
    cout << string(102, '=') << "\n";

    cout << "\nThong ke:\n";
    cout << "So phong dat duoc: " << soPhongDatDuoc << "\n";
    cout << "Doanh thu uoc tinh con: " << formatTien(doanhThuUocTinh) << " VND\n";
    cout << "Doanh thu thuc te: " << formatTien((long long)doanhThuThucTe) << " VND\n";

    cout << "\n[SUCCESS] Da luu tat ca du lieu!\n";
    pause();

    LoginedInAccount = TaiKhoan();
    SoLuongLichSuBanDau = 0;
    SoLuongBookingBanDau = 0;
    LaunchSystem();
}
