#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
//#include<time.h>
#include <stdio.h>
using namespace std;
class Accout {
	int ID;
	string TaiKhoan;
	string MatKhau;
	bool Active;
public:
	void DangNhap();
	void DangKi();
	string GetID();
	void DoiMatKhau();
};
class Sach {
public:
	string TenSach;
	string TacGia;
	string NhaXuatBan;
	string NamXuatBan;
	string GioiThieu;
	Sach() {
		TenSach = '*';
		TacGia = '*';
		NhaXuatBan = '*';
		NamXuatBan = '*';
		GioiThieu = '*';
	}
};
class User {
public:
	int ID;
	string Name;
	string SoCMND;
	string NgaySinh;
	string NgheNghiep;
	string Email;
	string Sdt;
	User() {
		ID = 0;
		Name = '*';
		SoCMND = '*';
		NgaySinh = '*';
		NgheNghiep = '*';
		Email = '*';
		Sdt = '*';
	};
	User(string &s);
	void TimSach();
	void MuonSach();
	void XemThongBao();
	void XemThongTin();
	void DoiMatKhau();
};
class ThuThu : User {
public:
	void ThemSach();
	void ChinhsuaSach();
	void Xoasach();
	void XacNhanMuonSach();
	void GiaiQuyet();//giải quyết việc mất sách, phạt các User 
};
class Admin : ThuThu {
public:
	void ThemAccout();
	void XoaAccout();
	void TimKiemAccout();
};

void Accout::DangNhap() {
	int j;
	do {
		cout << " Tai Khoan:";
		cin >> TaiKhoan;
		//getline(cin, tk);
		cout << "Mat Khau:";
		cin >> MatKhau;

		fstream l;
		l.open("Accout.txt", ios_base::in);
		string x, y, z;
		string t;
		while (getline(l, z)) {
			getline(l, x);
			getline(l, y);
			getline(l, t);
			int t1 = t[0] - 48;
			for (int i = 0; i<y.length(); i++) {
				y[i] = y[i] - 18;
			}
			if (x.compare(TaiKhoan) == 0 && y.compare(MatKhau) == 0) {
				if (t1 == 1) { j = 0; break; }
				else { cout << "Tai khoan cua ban da bi khoa" << endl; j = 2; }
			}
			else { j = 1; }
		}
		if (j == 1)cout << "Ban nhap sai Tai Khoan hoac Mat Khau" << endl;
		//cout <<tk<<"----"<<mk<<endl;
		l.close();
	}


	while (j != 0);
}
string Accout::GetID() {
	fstream l;
	l.open("Accout.txt", ios_base::in);
	string x, y, z;
	string t;
	while (getline(l, z)) {
		getline(l, x);
		getline(l, y);
		getline(l, t);
		if (x.compare(TaiKhoan) == 0) {
			return z;
			break;
		}
	}
	l.close();
}

void Accout::DangKi() {
	fstream k, h, l;
	string x, y;
	User member;
	int j, t;
	do {

		cout << "Ho va ten:";
		cin >> member.Name;
		cout << "So CMND:";
		cin >> member.SoCMND;
		cout << "Ngay sinh:";
		cin >> member.NgaySinh;
		cout << "Nghe nghiep:";
		cin >> member.NgheNghiep;
		cout << "email:";
		cin >> member.Email;
		cout << "SDT:";
		cin >> member.Sdt;
		cout << " Tai Khoan:";
		cin >> TaiKhoan;
		//getline(cin, tk);
		cout << "Mat Khau:";
		cin >> MatKhau;
		j = 0, t = 0;

		k.open("Accout.txt", ios::in);
		while (getline(k, x)) {
			getline(k, y);
			if (y.compare(TaiKhoan) == 0) {
				t = 1;
				cout << "Tai khoan da ton tai" << endl;
				break;
			}
			j = j + 1;
		}
		j = j / 2;
		k.close();
	} while (t == 1);
	Active = true;
	for (int i = 0; i<MatKhau.length(); i++) {
		MatKhau[i] = MatKhau[i] + 18;
	}
	h.open("Accout.txt", ios::out | ios::app);
	h << j << "\n";
	h << TaiKhoan << "\n";
	h << MatKhau << "\n";
	h << Active << "\n";
	h.close();
	l.open("User.txt", ios::out | ios::app);
	l << j << "\n";
	l << member.Name << "\n";
	l << member.SoCMND << "\n";
	l << member.NgaySinh << "\n";
	l << member.NgheNghiep << "\n";
	l << member.Email << "\n";
	l << member.Sdt << "\n";
	l.close();
}
string ThoiGianHienTai() {
//	time_t now = time(0);
	struct tm  tstruct;
	char       buf[80];
	//tstruct = *localtime(&now);

	//strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
User::User(string &s) {
	int i = 0;
	string t;
	for (int j = 0; j<s.length(); j++) {
		i = i + (s[j] - 48)*pow(10, (s.length() - j - 1));
	}
	fstream f;
	f.open("User.txt", ios::in);
	while (getline(f, t)) {
		getline(f, Name);
		getline(f, SoCMND);
		getline(f, NgaySinh);
		getline(f, NgheNghiep);
		getline(f, Email);
		getline(f, Sdt);
		if (s.compare(t) == 0) break;
	}
	ID = i;
}
void User::TimSach() {
	Sach oop;
	string a;
	cout << "nhap thong tin sach can tim:\t";
	cin.ignore();
	getline(cin, a);
	//cin >>a;
	//cout <<a<<endl;
	//getline(cin, a);
	fstream k, h;

	int b = 1000;

	k.open("sach.txt", ios::in);
	while (getline(k, oop.TenSach)) {
		if (b > a.compare(oop.TenSach)) b = a.compare(oop.TenSach);
		getline(k, oop.TacGia);
		if (b > a.compare(oop.TacGia)) b = a.compare(oop.TacGia);
		getline(k, oop.NhaXuatBan);
		if (b > a.compare(oop.NhaXuatBan)) b = a.compare(oop.NhaXuatBan);
		getline(k, oop.NamXuatBan);
		if (b > a.compare(oop.NamXuatBan)) b = a.compare(oop.NamXuatBan);
		getline(k, oop.GioiThieu);
		if (b > a.compare(oop.GioiThieu)) b = a.compare(oop.GioiThieu);
	}
	k.close();
	h.open("sach.txt", ios::in);
	while (getline(h, oop.TenSach)) {
		getline(h, oop.TacGia);
		getline(h, oop.NhaXuatBan);
		getline(h, oop.NamXuatBan);
		getline(h, oop.GioiThieu);
		if (a.compare(oop.TenSach) == b || a.compare(oop.TacGia) == b || a.compare(oop.NhaXuatBan) == b || a.compare(oop.NamXuatBan) == b || a.compare(oop.GioiThieu) == b) {
			cout << oop.TenSach << endl;
			cout << oop.TacGia << endl;
			cout << oop.NhaXuatBan << endl;
			cout << oop.NamXuatBan << endl;
			cout << oop.GioiThieu << endl;
			break;
		}
	}
	h.close();
	int choice;
	cout << "1.Gui yeu cau muon sach nay." << endl;
	cout << "2.Thoat " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1: {
		fstream f;
		string s = ThoiGianHienTai();
		f.open("Muonsach.txt", ios::out | ios::app);
		f << "Ho_Ten:" << Name << "\n";
		f << "Ten_Sach:" << oop.TenSach << "\n";
		f << "Sdt:" << Sdt << "\n";
		f << "Email:" << Email << "\n";
		f << "Ngay_muon:" << s << "\n";
		f.close();
		break;
	}
	case 2: {
		break;
	}
	default:
		break;
	}
}

void main() {
	Accout App;
	//App.DangKi();
	App.DangNhap();
	//string s=App.GetID();//lấy ID ra
	//User op(s); //đưa ID vào để biết được user
	//User op;
	//op.TimSach();//tìm sách

	system("pause");
}