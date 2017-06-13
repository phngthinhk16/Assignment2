#pragma warning (disable: 4996)
#pragma warning (disable: 4308)
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
void Menu0();
void Menu1();
void Menu2_1();
void Menu2_2();
void Menu2_3();
// Khai báo các class
class Sach {
	char maSach[10];
	char tenSach[50];
	char tenTacGia[30];
public:
	void Them_Sach();
	void Chinh_Sua_Sach();
	void Xuat_Thong_Tin();
	char* Lay_Ma_Sach() { return maSach; }
	char* Lay_Ten_Sach() { return tenSach; }
	char* Lay_ten_Tac_Gia() { return tenTacGia; }
	void Xoa_Sach();

};
// hàm ghi sách xuống file
void Ghi_Sach(Sach sach0) {
	fstream f0("Sach.dat", ios::out | ios::binary | ios::app);
	f0.write((char*)&sach0, sizeof(sach0));
	f0.close();
}

void Sach::Them_Sach() {
	Sach sach0;
	cout << "\n====================== THEM SACH ======================\n";
	cout << "-Ma sach: ";
	fflush(stdin);
	cin.getline(sach0.maSach, 10);
	cout << "-Ten sach: ";
	fflush(stdin);
	cin.getline(sach0.tenSach, 50);
	cout << "-Ten tac gia: ";
	fflush(stdin);
	cin.getline(sach0.tenTacGia, 30);
	// ghi xuong file
	fstream f0("Sach.dat", ios::out | ios::binary | ios::app);
	f0.write((char*)&sach0, sizeof(sach0));
	f0.close();
	cout << "\nThem sach thanh cong!";
	system("pause");
}
void Sach::Chinh_Sua_Sach() {
	Sach sach0;
	bool found = false;
	char temp[10];
	cout << "\n======= CHINH SUA THONG TIN SACH======\n";
	cout << "Nhap ma sach can sua: ";
	fflush(stdin);
	cin.getline(temp, 10);	// do mã sách k có dấu cách nên dùng cin cũng đc
	fstream f0("Sach.dat", ios::in | ios::out | ios::binary);
	while (f0.read((char*)&sach0, sizeof(sach0)) && found == false) {
		if (strcmpi(sach0.Lay_Ma_Sach(), temp) == 0) {
			sach0.Xuat_Thong_Tin();
			cout << "\n======================\n";
			found = true;
			cout << "\nMa sach: " << sach0.maSach;
			cout << "\nTen moi cua sach: ";
			fflush(stdin);
			cin.getline(sach0.tenSach, 50);
			cout << "\nTen moi cua tac gia: ";
			fflush(stdin);
			cin.getline(sach0.tenTacGia, 30);
			int vitri = sizeof(sach0); vitri *= (-1);
			f0.seekp(vitri, 1);	// quay lại
			f0.write((char*)&sach0, sizeof(sach0));
			cout << "\nCap nhat thanh cong!";
			break;
		}
	}
	f0.close();
	if (found == 0) cout << "\nKHong tim thay sach can sua!";
	system("pause");
}
void Sach::Xuat_Thong_Tin() {
	cout << "\nMa sach: " << maSach;
	cout << "\nTen sach: " << tenSach;
	cout << "\nTac gia: " << tenTacGia;
	//system("pause");
}
void Sach::Xoa_Sach() {
	Sach sach0;
	char temp[10];
	bool found = false;
	cout << "\nNhap ma sach muon xoa: ";
	fflush(stdin);
	cin.getline(temp, 10);
	fstream f0("Sach.dat", ios::in | ios::out | ios::binary);
	fstream f1("Sach_temp.dat", ios::out | ios::binary);
	while (f0.read((char*)&sach0, sizeof(sach0))) {
		if (strcmpi(sach0.maSach, temp) != 0) {
			f1.write((char*)&sach0, sizeof(sach0));
		}
		else {
			found = true;
		}
	}
	f1.close();
	f0.close();
	remove("Sach.dat");
	rename("Sach_temp.dat", "Sach.dat");
	if (!found) { cout << "\nKhong tim duoc sach can xoa!"; }
	else {
		cout << "\nXoa thanh cong!";
	}
	system("pause");
}

class NguoiDung {
protected:
	char tenNguoiDung[30];
	char diaChi[50];
	char sdt[20];
	char email[30];
	bool trangThaiDangNhap;
	int soSachMuon;
	char maSachMuon[10];
public:
	NguoiDung();
	void MuonSach(char a[]) {
		soSachMuon++;
		strcpy(maSachMuon, a);
	}
	void TraSach() {
		soSachMuon--;
		strcpy(maSachMuon, "");
	}
	void Them();
	void Xoa();
	void Xuat_Thong_Tin_Nguoi_Dung();
	char* Lay_Ten() { return tenNguoiDung; }
	int Lay_So_Sach_Muon() { return soSachMuon; }

};
NguoiDung::NguoiDung() {
	strcpy(tenNguoiDung, "");
	strcpy(diaChi, "");
	strcpy(sdt, "");
	strcpy(email, "");
	trangThaiDangNhap = false;
	soSachMuon = 0;
	strcpy(maSachMuon, "");
}

// hàm ghi thông tin người dùng xuống file
void Ghi_Nguoi_Dung(NguoiDung nguoidung0) {
	fstream f0("NguoiDung.dat", ios::out | ios::binary);
	f0.write((char *)&nguoidung0, sizeof(nguoidung0));
	f0.close();
}

void NguoiDung::Them() {
	NguoiDung nd0;
	cout << "\nNhap ten: ";
	fflush(stdin);
	cin.getline(nd0.tenNguoiDung, 30);
	cout << "\nNhap dia chi: ";
	fflush(stdin);
	cin.getline(nd0.diaChi, 50);
	cout << "\nNhap so dien thoai: ";
	fflush(stdin);
	cin.getline(nd0.sdt, 20);
	nd0.soSachMuon = 0;
	fstream f0("NguoiDung.dat", ios::out | ios::binary);
	f0.write((char *)&nd0, sizeof(nd0));
	f0.close();

}

void NguoiDung::Xuat_Thong_Tin_Nguoi_Dung() {
	NguoiDung nd0;
	fstream f0("NguoiDung.dat", ios::in | ios::binary);
	while (f0.read((char*)&nd0, sizeof(nd0))) {
		cout << "\nTen: " << nd0.tenNguoiDung;
		cout << "\nDia chi: " << nd0.diaChi;
		cout << "\nSo dien thoai: " << nd0.sdt;
		cout << "\nSo sach da muon chua tra la: " << nd0.soSachMuon;
		cout << "\n=====================";
		break;
	}
	f0.close();

}




// hàm đọc file sách
void Doc_Sach(Sach sach0) {
	fstream f0("Sach.dat", ios::in);
	f0.read((char*)&sach0, sizeof(sach0));

	f0.close();
}
// hàm độc file thông tin người dùng
void Doc_Nguoi_Dung(NguoiDung nguoidung0) {
	fstream f0("NguoiDung.dat", ios::in);
	f0.read((char *)&nguoidung0, sizeof(nguoidung0));
	f0.close();
}

//========================================================================

class TaiKhoan :NguoiDung {
	char tenDangNhap[30];
	char matKhau[20];
	bool laNguoiDoc;
	bool laThuThu;
	bool laAdmin;

public:
	void Tao_Tai_Khoan();
	void Doi_Mat_Khau();
	void Xoa_Tai_Khoan();
	char* Lay_Ten_Dang_Nhap() { return tenDangNhap; }
	char* Lay_Mat_Khau() { return matKhau; }
	bool LaThuThu() { if (laThuThu == true) return true; return false; }
	bool LaNguoiDoc() { if (laNguoiDoc == true) return true; return false; }
	bool LaAdmin() { if (laAdmin == true) return true; return false; }
	void Xuat_Thong_Tin();
};
// hàm đọc file tài khoản
void Doc_Tai_Khoan(TaiKhoan tk0) {
	fstream f0("TaiKhoan.dat", ios::in | ios::app);
	f0.read((char *)&tk0, sizeof(tk0));
	f0.close();
}

// hàm ghi thông tin tài khoản xuống file
void Ghi_Tai_Khoan(TaiKhoan tk0) {
	fstream f0("TaiKhoan.dat", ios::out | ios::binary | ios::app);
	f0.write((char *)&tk0, sizeof(tk0));

	f0.close();
}

void TaiKhoan::Tao_Tai_Khoan() {
	TaiKhoan tk0;
	tk0.laNguoiDoc = true;	//cho giá trị ban đầu để
	tk0.laThuThu = true;	//dễ test chương trình
	tk0.laAdmin = true;		//
							// mới tạo tài khoản thì chưa có mượn quyển nào hết
	cout << "\nNhap ten dang nhap: ";
	fflush(stdin);
	cin.getline(tk0.tenDangNhap, 30);
	cout << "\nNhap mat khau: ";
	fflush(stdin);
	cin.getline(tk0.matKhau, 20);
	NguoiDung::Them();	// lấy thông tin của người dùng
						//Ghi_Tai_Khoan(tk0);
	fstream f0("TaiKhoan.dat", ios::out | ios::binary | ios::app);
	f0.write((char *)&tk0, sizeof(tk0));
	f0.close();

}

void TaiKhoan::Xuat_Thong_Tin() {
	TaiKhoan tk0;
	cout << "\n\t==Thong tin tai khoan ==\n";
	fstream f0("TaiKhoan.dat", ios::in | ios::binary);
	while (f0.read((char*)&tk0, sizeof(tk0))) {
		cout << "\nTen dang nhap: " << tk0.tenDangNhap;
		cout << "\nMat khau: " << tk0.matKhau;
		NguoiDung::Xuat_Thong_Tin_Nguoi_Dung();
	}
	system("pause");
	f0.close();

}
//Sach sach0;
//TaiKhoan tk0;
//NguoiDung nguoidung0;

void Tim_Sach() {
	Sach sach0;
	bool found = false;
	char ten[50], ma[10], tacgia[30];
	system("cls");
	cout << "========= \n\tTIM SACH ========\n";
	cout << "\n1. Tim theo ma sach.";
	cout << "\n2. Tim theo ten sach.";
	cout << "\n3. Tim theo ten tac gia."; // còn nữa
	cout << "\nBan chon: ";
	int chon;
	cin >> chon;
	switch (chon)
	{
	case 0: break;
	case 1: {
		cout << "\nNhap ma sach: ";
		fflush(stdin);
		cin.getline(ma, 50);

		fstream f0("Sach.dat", ios::in | ios::binary);
		while (f0.read((char*)&sach0, sizeof(sach0))) {
			//sach0.Xuat_Thong_Tin();
			if (strcmpi(sach0.Lay_Ma_Sach(), ma) == 0) {
				found = true;
				sach0.Xuat_Thong_Tin();
				system("pause");
			}
		}
		f0.close();
		if (!found) {
			cout << "\nKhong tim thay!";
		}

		cout << "\nBan co muon tiep tuc tiem kiem khong?";
		cout << "\n1.Co";
		cout << "\n2.Khong";
		cout << "\nBan chon: ";
		int chon1;
		cin >> chon1;
		if (chon1 == 1) {
			Tim_Sach();
		}
		else {
			void Menu2_2();
		}
		break;
	}
	case 2: {
		cout << "\nNhap ten sach: ";
		fflush(stdin);
		cin.getline(ten, 50);

		fstream f0("Sach.dat", ios::in | ios::binary);
		while (f0.read((char*)&sach0, sizeof(sach0))) {
			//sach0.Xuat_Thong_Tin();
			if (strcmpi(sach0.Lay_Ten_Sach(), ten) == 0) {
				found = true;
				sach0.Xuat_Thong_Tin();
				system("pause");
			}
		}
		f0.close();
		if (!found) {
			cout << "\nKhong tim thay!";
		}

		cout << "\nBan co muon tiep tuc tiem kiem khong?";
		cout << "\n1.Co";
		cout << "\n2.Khong";
		cout << "\nBan chon: ";
		int chon1;
		cin >> chon1;
		if (chon1 == 1) {
			Tim_Sach();
		}
		else {
			void Menu2_2();
		}
		break;
	}
	case 3: {
		cout << "\nNhap ten tac gia: ";
		fflush(stdin);
		cin.getline(tacgia, 50);

		fstream f0("Sach.dat", ios::in | ios::binary);
		while (f0.read((char*)&sach0, sizeof(sach0))) {
			//sach0.Xuat_Thong_Tin();
			if (strcmpi(sach0.Lay_ten_Tac_Gia(), ma) == 0) {
				found = true;
				sach0.Xuat_Thong_Tin();
				system("pause");
			}
		}
		f0.close();
		if (!found) {
			cout << "\nKhong tim thay!";
		}

		cout << "\nBan co muon tiep tuc tiem kiem khong?";
		cout << "\n1.Co";
		cout << "\n2.Khong";
		cout << "\nBan chon: ";
		int chon1;
		cin >> chon1;
		if (chon1 == 1) {
			Tim_Sach();
		}
		else {
			void Menu2_2();
		}
		break;
	}
	default:
		break;
	}
}
void Ghi_Nhan_Viec_Muon_Sach() {
	NguoiDung nd0;
	Sach sach0;
	char tennguoimuon[30];	// có thể dùng mã người dùng để xác nhận cho đơn giản hơn
	char masach[10];
	bool found_nd = false, found_sach = false;
	fstream f0("NguoiDung.dat", ios::in | ios::out | ios::binary);
	fstream f1("Sach.dat", ios::in | ios::out | ios::binary);
	cout << "\nNhap ten nguoi muon: ";
	fflush(stdin);
	cin.getline(tennguoimuon, 30);
	while (f0.read((char*)&nd0, sizeof(nd0)) && found_nd == false) {
		if (strcmpi(nd0.Lay_Ten(), tennguoimuon) == 0) {
			found_nd = true;
			if (nd0.Lay_So_Sach_Muon() == 0) {

				nd0.Xuat_Thong_Tin_Nguoi_Dung();
				cout << "\n==============================\n";
				cout << "\nNhap ma sach can muon: ";
				fflush(stdin);
				cin.getline(masach, 50);
				while (f1.read((char*)&sach0, sizeof(sach0)) && found_sach == false) {
					if (strcmpi(sach0.Lay_Ma_Sach(), masach) == 0) {
						found_sach = true;
						sach0.Xuat_Thong_Tin();
						cout << "\n==============================\n";
						// sửa lại file nhị phân NguoiDung- sosachmuon++
						nd0.MuonSach(masach);
						int vitri = sizeof(nd0)*(-1);
						f0.seekp(vitri, 1);
						f0.write((char*)&nd0, sizeof(nd0));
						cout << "\nMuon sach thanh cong!\nLuu y tra sach dung han!";
						break;
					}
				}
				if (!found_sach) cout << "\nKhong tim thay sach can muon!";
			}
			else {
				cout << "\nBan can tra sach truoc khi muon sach moi";
				system("pause");
				break;
			}
		}

	}
	if (!found_nd) cout << "\nKhong tim thay ten nguoi muon trong he thong thanh vien!";
	system("pause");
	f1.close();
	f0.close();
	system("pause");
}

void Ghi_Nhan_Viec_Tra_Sach() {
	NguoiDung nd0;
	Sach sach0;
	char tennguoitra[30];	// có thể dùng mã người dùng để xác nhận cho đơn giản hơn
	char masach[10];
	bool found_nd = false, found_sach = false;
	fstream f0("NguoiDung.dat", ios::in | ios::out | ios::binary);
	fstream f1("Sach.dat", ios::in | ios::binary);
	cout << "\nNhap ten nguoi tra: ";
	fflush(stdin);
	cin.getline(tennguoitra, 30);
	while (f0.read((char*)&nd0, sizeof(nd0)) && found_nd == false) {
		if (strcmpi(nd0.Lay_Ten(), tennguoitra) == 0) {
			found_nd = true;
			nd0.Xuat_Thong_Tin_Nguoi_Dung();
			cout << "\n==============================\n";
			cout << "\nNhap ma sach can tra: ";
			fflush(stdin);
			cin.getline(masach, 50);
			while (f1.read((char*)&sach0, sizeof(sach0)) && found_sach == false) {
				if (strcmpi(sach0.Lay_Ma_Sach(), masach) == 0) {
					found_sach = true;
					sach0.Xuat_Thong_Tin();
					cout << "\n==============================\n";
					nd0.TraSach();
					int vitri = sizeof(nd0)*(-1);
					f0.seekp(vitri, 1);
					f0.write((char*)&nd0, sizeof(nd0));
					cout << "\nTra sach thanh cong!";
					break;
				}
			}
			if (!found_sach) cout << "\nKhong tim thay sach can tra!";
		}

	}
	if (!found_nd) cout << "\nKhong tim thay ten nguoi muon trong he thong thanh vien!";
	system("pause");
	f1.close();
	f0.close();
}

void Menu2_1() { // chương trình chính cho độc giả
	int chon;
	do
	{
		cout << "\n\n\t\t====== MENU DANH CHO DOC GIA =======\n";
		cout << "\n0. Thoat.";
		cout << "\n1. Tim sach.";
		cout << "\n3. Gui yeu cau muon sach.";
		cout << "\n4. Xem thong bao.";
		cout << "\n5. Xem thong tin (lich su hoat dong).";
		cout << "\n6. Doi mat khau.";
		cout << "\nBan chon (0-6): ";
		cin >> chon;
		switch (chon)
		{
		case 0: break;
		case 1: {
			Tim_Sach();
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
		case 5: {

			break;
		}
		case 6: {
			break;
		}
		default:
			break;
		}
	} while (chon != 0);
}
void Menu2_2() { // chương trình chính cho thủ thư
	int chon;
	Sach sach0;
	TaiKhoan tk0;
	NguoiDung nd0;
	do
	{
		system("cls");
		cout << "\n\n\t\t====== MENU DANH CHO THU THU =======\n";
		cout << "\n0. Thoat.";
		cout << "\n1. Them sach.";
		cout << "\n2. Chinh sua thong tin sach.";
		cout << "\n3. Xoa sach.";
		cout << "\n4. In danh sach cac quyen sach hien co..";
		cout << "\n5. Tim kiem sach.";
		cout << "\n6. Ghi nhan muon sach."; // còn nữa ...
		cout << "\n7. Danh sach nguoi dung.";
		cout << "\n8. Ghi nhan tra sach.";
		cout << "\nBan chon (0-5): ";
		cin >> chon;
		if (chon == 0) break;
		switch (chon)
		{
		case 0: Menu0; break;
		case 1: {
			sach0.Them_Sach();
			break;
		}
		case 2: {
			sach0.Chinh_Sua_Sach();
			break;
		}
		case 3: {
			sach0.Xoa_Sach(); break;
		}
		case 4: {
			fstream f0("Sach.dat", ios::in | ios::binary);
			while (f0.read((char*)&sach0, sizeof(sach0))) {
				sach0.Xuat_Thong_Tin();
				cout << "\n==========================";
			}
			system("pause");
			f0.close();
			break;
		}
		case 5: {
			Tim_Sach();
			break;
		}
		case 6: {
			Ghi_Nhan_Viec_Muon_Sach();
			break;
		}
		case 7: {
			tk0.Xuat_Thong_Tin();
			break;
		case 8: {
			Ghi_Nhan_Viec_Tra_Sach(); break;
		}
		}
		default:
			break;
		}
	} while (chon != 0);
}
void Menu2_3() { // chương trình chính cho admin
	int chon;
	do
	{
		cout << "\n\n\t\t====== MENU DANH CHO ADMIN =======\n";
		cout << "\n0. Thoat.";
		cout << "\n1. Them nguoi dung.";
		cout << "\n3. Chinh sua thong tin nguoi dung.";
		cout << "\n4. Xoa nguoi dung.";
		cout << "\n5. Tim kiem nguoi dung.";
		cout << "\n6. Them tai khoan";
		cout << "\n7. Mo/khoa tai khoan.";
		cout << "\n8. Dat lai mat khau";
		cout << "\nBan chon (0-6): ";
		cin >> chon;
		switch (chon)
		{
		case 0: break;
		case 1: {
			break;
		}

		default:
			break;
		}
	} while (chon != 0);
}
// hàm đăng nhập
void Dang_Nhap() {
	int chon;
	do {
		system("cls");
		cout << "\n\t==== Chon loai tai khoan ==== ";
		cout << "\n1.Doc Gia.";
		cout << "\n2.Thu Thu.";
		cout << "\n3.Admin.";
		cout << "\nBan chon: ";
		cin >> chon;
	} while (chon < 1 || chon >3 || cin.fail());
	char TenDangNhap[30];
	char MatKhau[20];
	int Timduoc = 0;
	switch (chon)
	{
	case 1: {
		cout << "\nTen dang nhap: ";
		fflush(stdin);
		cin.getline(TenDangNhap, 30);
		cout << "\nMat khau: ";
		fflush(stdin);
		cin.getline(MatKhau, 20);
		TaiKhoan tk0;
		fstream f0("TaiKhoan.dat", ios::in, ios::binary);
		while (f0.read((char *)&tk0, sizeof(tk0)) && Timduoc == 0)
		{
			//tk0.Xuat_Thong_Tin();
			if (strcmpi(tk0.Lay_Ten_Dang_Nhap(), TenDangNhap) == 0 && strcmpi(tk0.Lay_Mat_Khau(), MatKhau) == 0 && tk0.LaNguoiDoc() == true) {
				cout << "\nDang nhap thanh cong!";
				system("pause");

				Menu2_1(); // chương trình chính dành cho độc giả
				Timduoc = 1;
				break;
			}
		}
		if (!Timduoc) {
			cout << "Loi dang nhap!";
			system("pause");
			break;
		}
		f0.close(); break;

	}
	case 2: {
		cout << "\nTen dang nhap: ";
		fflush(stdin);
		cin.getline(TenDangNhap, 30);
		cout << "\nMat khau: ";
		fflush(stdin);
		cin.getline(MatKhau, 20);
		TaiKhoan tk0;
		bool Timduoc = 0;
		fstream f0("TaiKhoan.dat", ios::in | ios::binary);
		while (f0.read((char *)&tk0, sizeof(tk0)))
		{
			if (strcmpi(tk0.Lay_Ten_Dang_Nhap(), TenDangNhap) == 0 && strcmpi(tk0.Lay_Mat_Khau(), MatKhau) == 0 && tk0.LaThuThu() == true) {
				cout << "\nDang nhap thanh cong!";
				Timduoc = true;
				system("pause");
				Menu2_2(); // chương trình chính dành cho thủ thư
				break;
			}
		}
		if (!Timduoc) {
			cout << "\nLoi dang nhap!";
			system("pause");
		}
		f0.close();
		break;
	}
	case 3: {

		cout << "\nTen dang nhap: ";
		fflush(stdin);
		cin.getline(TenDangNhap, 30);
		cout << "\nMat khau: ";
		fflush(stdin);
		cin.getline(MatKhau, 20);
		TaiKhoan tk0;
		int Timduoc = 0;
		fstream f0("TaiKhoan.dat", ios::in);
		while (f0.read((char *)&tk0, sizeof(tk0)) && Timduoc == 0)
		{
			if (strcmpi(tk0.Lay_Ten_Dang_Nhap(), TenDangNhap) == 0 && strcmpi(tk0.Lay_Mat_Khau(), MatKhau) == 0 && tk0.LaAdmin() == true) {
				cout << "\nDang nhap thanh cong!";
				system("pause");
				Menu2_3(); // chương trình chính dành cho admin
			}
		}
		if (!Timduoc) {
			cout << "\nLoi dang nhap!";
			system("pause");
		}
		f0.close();
		break;
		f0.close();
	}
	default:
		break;
	}
}
// hàm đăng ký
void Dang_Ky() {
	TaiKhoan tk0;
	tk0.Tao_Tai_Khoan();
}


void Menu1() {
	int chon;
	do {
		system("cls");
		cout << "\n\n\t\t===== TRANG DANG NHAP ===== \n";
		cout << "\n0. Tro lai.";
		cout << "\n1. Dang ky.";
		cout << "\n2. Dang nhap.";
		cout << "\nBan chon (1-2): ";
		cin >> chon;
		switch (chon)
		{
		case 0: break;
		case 1: {
			Dang_Ky();
			cout << "\nDang ky thanh cong!";
			system("pause");
			break;
		}
		case 2: Dang_Nhap(); break;
		default:
			break;
		}
	} while (chon != 0);
}

void Menu0() {
	int chon;
	do {
		system("cls");
		cout << "\n\n\t\t========== CHUONG TRINH THU VIEN ==========\n";
		cout << "\nBan co muon dang nhap truoc khi dung khong?";
		cout << "\n1. Co.";
		cout << "\n2. Khong.";
		cout << "\n0. Thoat chuong trinh.";
		cout << "\nBan chon (1-2): ";
		cin >> chon;
		if (chon == 1) {
			Menu1();
		}
		else if (chon == 2) {
			cout << "Khong dang nhap thi khoi xai, OK?";
			system("pause");
		}
	} while (chon != 0);
}

int main() {
	Menu0();
	return 0;
}