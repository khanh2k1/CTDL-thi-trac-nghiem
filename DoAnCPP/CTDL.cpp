

#include"mylib.h"
#include"structData.h"

#include<iostream>
#include<string>
#include<time.h>
#include<fstream>
#include<algorithm>
#include<math.h>
#include<Windows.h>

using namespace std;

// Khai bao bien toan cuc
listLOP listL;
listMONHOC listMH;
nodeCAUHOI* rootCH;
listSINHVIENDATHI listSVDT;



// LOAD FILE
void LoadDanhSachLopTuFile()
{
	ifstream filein;
	filein.open("LOPDEMO.txt", ios_base::in);
	filein >> listL.soLop;
	filein.ignore();
	int soSinhVien;

	for (int i = 0; i < listL.soLop; i++)
	{
		LOP lop;
		getline(filein, lop.maLop);
		getline(filein, lop.tenLop);

		filein >> soSinhVien;
		filein.ignore();
		listSINHVIEN listSV;
		listSV.pHead = NULL;
		for (int i = 0; i < soSinhVien; i++)
		{
			SINHVIEN sv;
			getline(filein, sv.ho);
			getline(filein, sv.ten);
			getline(filein, sv.gioiTinh);
			getline(filein, sv.maSV);
			getline(filein, sv.password);

			int soMH;
			filein >> soMH;;
			filein.ignore();

			if (soMH == 0)
			{
				sv.listDT.pHead = sv.listDT.pTail = NULL;
			}
			else
			{
				listDIEMTHI listDT;
				listDT.pHead = listDT.pTail = NULL;
				for (int i = 0; i < soMH; i++)
				{
					DIEMTHI dt;
					getline(filein, dt.maMH);
					filein >> dt.diem;
					filein.ignore();

					// khoi tao vung nho 
					nodeDIEMTHI* p;
					if (listDT.pHead == NULL)
					{
						p = new nodeDIEMTHI;
						p->data = dt;
						p->pNext = NULL;
						listDT.pHead = listDT.pTail = p;
					}
					else
					{
						// themCuoi
						nodeDIEMTHI* temp = new nodeDIEMTHI;
						temp->data = dt;
						temp->pNext = NULL;
						listDT.pTail->pNext = temp;
						listDT.pTail = temp;
					}
				}
				sv.listDT = listDT;
			}
			nodeSINHVIEN* p = new nodeSINHVIEN;
			p->data = sv;
			p->pNext = NULL;

			if (listSV.pHead == NULL)
			{
				listSV.pHead = listSV.pTail = p;
			}
			else
			{
				listSV.pTail->pNext = p;
				listSV.pTail = p;
			}
		}
		lop.ListSV = listSV;
		listL.Data[i] = lop;
	}
	filein.close();
}
void LoadDanhSachMonHocTuFile()
{
	ifstream filein;
	filein.open("MonHoc.txt", ios_base::in);
	filein >> listMH.soMH;
	filein.ignore();
	MONHOC MH;
	for (int i = 0; i < listMH.soMH; i++)
	{
		getline(filein, MH.tenMH);
		getline(filein, MH.maMH);
		listMH.danhSach[i] = MH;
	}
}
void themCauHoi(nodeCAUHOI*& root, CAUHOI CHdata)
{
	if (root == NULL)
	{
		nodeCAUHOI* node = new nodeCAUHOI;
		node->pLeft = NULL;
		node->pRight = NULL;
		node->data = CHdata;
		root = node;
	}
	else
	{
		if (root->data.id > CHdata.id) {
			themCauHoi(root->pLeft, CHdata);
		}
		else if (root->data.id < CHdata.id) {
			themCauHoi(root->pRight, CHdata);
		}
	}
}
void LoadCauHoiTuFile()
{
	rootCH = NULL;
	ifstream filein;
	filein.open("CauHoi.txt", ios_base::in);
	int soCH;
	filein >> soCH;

	//cout << "soCH: " << soCH << "\n";
	// load het cau hoi
	for (int i = 0; i < soCH; i++)
	{
		CAUHOI ch;
		filein >> ch.id; filein.ignore();
		getline(filein, ch.maMH);
		getline(filein, ch.ND);
		getline(filein, ch.A);
		getline(filein, ch.B);
		getline(filein, ch.C);
		getline(filein, ch.D);
		filein >> ch.DA;
		themCauHoi(rootCH, ch);
	}
	filein.close();
}
void themDapAn(nodeDAPAN*& root, DAPAN DAdata) {
	if (root == NULL) {
		nodeDAPAN* node = new nodeDAPAN;
		node->pLeft = NULL;
		node->pRight = NULL;
		node->data = DAdata;
		root = node;
	}
	else {
		if (root->data.data.id > DAdata.data.id) {
			themDapAn(root->pLeft, DAdata);
		}
		else if (root->data.data.id < DAdata.data.id) {
			themDapAn(root->pRight, DAdata);
		}
	}
}
void LoadDanhSachCauHoiSinhVienDaThi()
{
	listSVDT.pHead = NULL;
	ifstream filein;
	filein.open("luuCAUHOIDATHI.txt", ios_base::in);
	int soSV = 0;
	filein >> soSV; // 2
	filein.ignore();

	if (soSV == 0) return;
	else {

		for (int i = 0; i < soSV; i++) {

			SINHVIENDATHI SVdata;
			getline(filein, SVdata.maSV); // N19DCCN001
			int soCH = 0;

			filein >> soCH; // 1
			filein.ignore();
			nodeDAPAN* root = NULL;
			for (int j = 0; j < soCH; j++) {

				DAPAN DAdata;
				getline(filein, DAdata.data.maMH);
				filein >> DAdata.data.id;
				filein.ignore();

				getline(filein, DAdata.data.ND);
				getline(filein, DAdata.data.A);
				getline(filein, DAdata.data.B);
				getline(filein, DAdata.data.C);
				getline(filein, DAdata.data.D);
				filein >> DAdata.data.DA;
				filein >> DAdata.DA_USER;
				filein.ignore();
				themDapAn(root, DAdata);
			}
			filein >> SVdata.soCauDung;
			filein >> SVdata.diem;
			filein.ignore();

			SVdata.rootDA = root;
			nodeSINHVIENDATHI* temp = new nodeSINHVIENDATHI;
			temp->data = SVdata;
			temp->pNext = NULL;

			if (listSVDT.pHead == NULL) {
				listSVDT.pHead = listSVDT.pTail = temp;
			}
			else {
				listSVDT.pTail->pNext = temp;
				listSVDT.pTail = temp;
			}

		}
	}
	filein.close();
}
void LoadDuLieuTuFile()
{
	LoadDanhSachLopTuFile();
	LoadDanhSachMonHocTuFile();
	LoadCauHoiTuFile();
	LoadDanhSachCauHoiSinhVienDaThi();
}

//  CHECK
bool checkTrungLop(string maLop)
{
	int max = listL.soLop;
	for (int i = 0; i < max; i++)
	{
		if (maLop == listL.Data[i].maLop) return false;
	}
	return true;
}
bool checkTenLop(string tenLop) {
	int max = listL.soLop;
	for (int i = 0; i < max; i++) {
		if (tenLop == listL.Data[i].tenLop) return true;
	}
	return false;
}
bool checkMaLop(string nhapMaLop)
{
	for (int i = 0; i < listL.soLop; i++)
	{
		if (nhapMaLop == listL.Data[i].maLop)
		{
			return true;
		}
	}
	return false;
}
bool checkGioiTinh(string gioiTinh)
{
	if (gioiTinh == "NAM" || gioiTinh == "NU")
	{
		return true;
	}
	return false;
}
bool checkMaSV(string maSV)
{
	for (int i = 0; i < listL.soLop; i++)
	{
		for (nodeSINHVIEN* k = listL.Data[i].ListSV.pHead; k != NULL; k = k->pNext)
		{
			if (maSV == k->data.maSV) return false;
		}
	}
	return true;
}
bool checktenMH(string tenMH)
{
	for (int i = 0; i < listMH.soMH; i++)
	{
		if (tenMH == listMH.danhSach->tenMH) return true;
	}
	return false;
}
bool checkmaMH(string maMH)
{
	for (int i = 0; i < listMH.soMH; i++)
	{
		if (maMH == listMH.danhSach[i].maMH) return true;
	}
	return false;
}

// FORMAT_TEXT
void vietHoa(string s) {
	int count = s.length();
	for (int i = 0; i < count; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
		}
	}
}


// NHAP LOP
void nhapLop() {
	system("cls");
	
	int n;
	cout << "\nMoi ban nhap so luong lop muon tao:";
	while (1) {
		if (cin >> n) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	cin.ignore();
	system("cls");
	cout << "Ban khong the tao cung ma lop duoi day:\n";
	for (int i = 0; i < listL.soLop; i++) {
		cout << listL.Data[i].maLop << endl;
	}
	int sl = listL.soLop;
	for (int i = 0; i < n; i++) {
		int dem = i + 1;
		if (listL.maxSize - listL.soLop + dem > 0) {
			int soLop = listL.soLop;
			string tenLop, maLop;
			while (1) {
				cout << "moi ban nhap ten lop THU " << i + 1 << ": "; getline(cin, tenLop);
				if (checkTenLop(tenLop) == true) cout << "\t\tTen lop da co, nhap lai\n";
				else break;
			}
			while (1) {
				cout << "moi ban nhap ma lop: " << i + 1 << ": "; getline(cin, maLop);
				if (checkMaLop(maLop) == true) cout << "\t\tMa lop da co, nhap lai\n";
				else break;
			}
			listL.Data[soLop].tenLop = tenLop;
			listL.Data[soLop].maLop = maLop;
			listL.Data[soLop].ListSV.pHead = listL.Data[soLop].ListSV.pTail = NULL;
			listL.soLop++;
		}
		else {
			cout << "Danh sach lop da day";
			break;
	}
	cout << "Ban da tao thanh cong " << n << " lop";
}


// IN DANH SACH LOP
void inThongTinSinhVien(SINHVIEN sv) {

	vietHoa(sv.ho); cout << sv.ho << "\n";
	vietHoa(sv.ten); cout << sv.ten << "\n";
	vietHoa(sv.gioiTinh); cout << sv.gioiTinh << "\n";
	vietHoa(sv.maSV); cout << sv.maSV << "\n";
	vietHoa(sv.password); cout << sv.password << "\n";
}
void inDanhSachSinhVien(nodeSINHVIEN* pHead)
{
	int i = 1;
	for (nodeSINHVIEN* k = pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\nthong tin sinh vien thu " << i << "\n";
		inThongTinSinhVien(k->data);
		++i;
	}
	cout << "\n\nNhan enter de quay ve MENU";

	cin.ignore();
	system("cls");
}
void inLop(LOP x)
{
	system("cls");
	gotoxy(0, 1); cout << "Ma lop: " << x.maLop;
	gotoxy(0, 2); cout << "Ten lop: " << x.tenLop;

	if (x.ListSV.pHead != NULL)
	{
		inDanhSachSinhVien(x.ListSV.pHead);
	}
	else
	{
		gotoxy(0, 3);
		cout << "So sinh vien :" << 0;
		gotoxy(0, 4);
		cout << "Moi nhan ENTER de quay lai MENU !"; cin.ignore(); system("cls");
	}
}
void inDanhSachLop()
{
	for (int i = 0; i < listL.soLop; i++)
	{
		cout << "\nThong tin lop " << listL.Data[i].tenLop << "\n";
		inLop(listL.Data[i]);
	}
}


// NHAP SINH VIEN
int chieudai = 5;
void suaThongTinSinhVien()
{
	system("cls");
	bool isTrue = 0;
	int y = 0;
	int luachon = -1;
	while (1)
	{

		string nhapMaLop;
		gotoxy(0, y); cout << "Ten lop";
		gotoxy(20, y); cout << "Ma lop";
		++y;
		int nhapSoLop = listL.soLop;
		for (int i = 0; i < listL.soLop; i++)
		{
			gotoxy(0, y); cout << listL.Data[i].tenLop;
			gotoxy(15, y); cout << listL.Data[i].maLop;
			++y;
		}
		++y;
		gotoxy(0, y); cout << "Moi ban nhap ma lop: ";
		int x = y;
		gotoxy(22, y); getline(cin, nhapMaLop);
		++y;
		isTrue = checkMaLop(nhapMaLop);
		if (isTrue == 0)
		{
			++y;
			gotoxy(0, y + 1); cout << "->ERROR<- : Ma Lop khong dung, vui long nhan ENTER de nhap lai !";
			cin.ignore();
			gotoxy(0, y + 1); cout << "                                                                                    ";
			gotoxy(22, x); cout << "                                           ";
		}
		else
		{
			system("cls");
			int i;
			for (i = 0; i < listL.soLop; i++) {
				if (nhapMaLop == listL.Data[i].maLop) {
					if (listL.Data[i].ListSV.pHead == NULL) {
						cout << "\nKHONG CO SINH VIEN NAO TRONG DANH SACH\n";
						cin.ignore();
						system("cls");
					}
					else {
						int chieudai = 0;
						gotoxy(40, chieudai); cout << "CHUC NANG"; ++chieudai;
						gotoxy(38, chieudai); cout << "============"; ++chieudai;
						gotoxy(40, chieudai); cout << "SUA SINH VIEN"; chieudai += 2;

						string maSV;
						gotoxy(0, chieudai); cout << "Moi ban nhap MA SINH VIEN can sua: ";
						gotoxy(40, chieudai); getline(cin, maSV); ++y;
						chieudai = chieudai + 10;



						for (nodeSINHVIEN* k = listL.Data[i].ListSV.pHead; k != NULL; k = k->pNext)
						{
							if (maSV == k->data.maSV)
							{
								SINHVIEN sv = k->data;
								gotoxy(0, chieudai); cout << "Ho:";
								gotoxy(0, chieudai + 1); cout << "Ten:";
								gotoxy(0, chieudai + 2); cout << "Gioi Tinh:";
								gotoxy(0, chieudai + 3); cout << "Ma SINH VIEN:";
								gotoxy(0, chieudai + 4); cout << "Password: ";

								gotoxy(20, chieudai); getline(cin, sv.ho); vietHoa(sv.ho);
								gotoxy(20, chieudai + 1); getline(cin, sv.ten); vietHoa(sv.ten);
								while (1)
								{
									gotoxy(0, chieudai + 2); cout << "Gioi Tinh: NAM-NU : ";
									gotoxy(20, chieudai + 2); getline(cin, sv.gioiTinh); vietHoa(sv.gioiTinh);
									if (checkGioiTinh(sv.gioiTinh) == true) break;
									else
									{
										gotoxy(20, chieudai + 2); cout << "->ERROR<- : Gioi tinh NAM hoac NU, nhan ENTER de nhap lai !";
										cin.ignore();
										gotoxy(20, chieudai + 2); cout << "                                                            ";
									}
								}
								while (1)
								{
									gotoxy(0, chieudai + 3); cout << "Ma sinh vien      : ";
									gotoxy(20, chieudai + 3); getline(cin, sv.maSV);
									if (checkMaSV(sv.maSV) == true) break;
									else
									{
										gotoxy(20, chieudai + 3); cout << "->ERROR<- : Ma sinh vien bi trung, nhan ENTER de nhap lai !";
										cin.ignore();
										gotoxy(20, chieudai + 3); cout << "                                                           ";
									}
								}
								gotoxy(20, chieudai + 4); getline(cin, sv.password);
								k->data = sv;
							}
						}
						system("cls"); gotoxy(0, 5); cout << "CAP NHAT THONG TIN SINH VIEN THANH CONG !";
						return;
					}
				}
				chieudai = 0;
			}
			y = 0;
		}

	}

}
void xoaDau(listSINHVIEN& temp)
{
	if (temp.pHead == NULL) {
		cout << "Khong co sinh vien nao trong danh sach !";
		return;
	}
	nodeSINHVIEN* k = new nodeSINHVIEN;
	k = temp.pHead;
	temp.pHead = temp.pHead->pNext;
	delete k;
}
void xoaCuoi(listSINHVIEN& temp)
{
	if (temp.pHead == NULL) {
		cout << "khong co sinh vien nao trong danh sach !";
		return;
	}
	for (nodeSINHVIEN* k = temp.pHead; k != NULL; k = k->pNext) {
		if (k->pNext == temp.pTail) {
			delete temp.pTail;
			k->pNext = NULL;
			temp.pTail = k;
		}
	}
}
void xoaBatKy(listSINHVIEN& temp, SINHVIEN data)
{
	if (temp.pHead == NULL) {
		cout << "khong co sinh vien nao trong danh sach !";
	}
	else
	{
		if (data.maSV == temp.pTail->data.maSV) {
			xoaCuoi(temp);
			return;
		}
		if (data.maSV == temp.pHead->data.maSV) {
			xoaDau(temp);
			return;
		}
		else
		{
			nodeSINHVIEN* q = new nodeSINHVIEN;
			for (nodeSINHVIEN* k = temp.pHead; k != NULL; k = k->pNext) {
				if (k->data.maSV == data.maSV) {
					q->pNext = k->pNext;
					k->pNext = NULL;
					k = q;
				}
				q = k;
			}
		}
	}
}
void xoaSinhVien()
{
	system("cls");
	cout << "TEN LOP";
	cout << "               ";
	cout << "MA LOP\n";
	for (int i = 0; i < listL.soLop; i++)
	{
		cout << listL.Data[i].tenLop;
		cout << "               ";
		cout << listL.Data[i].maLop;
		cout << "\n";
	}
	string maLop;
	cout << "\nMoi ban nhap MA LOP:"; getline(cin, maLop);
	system("cls");
	if (checkMaLop(maLop) == true)
	{
		for (int i = 0; i < listL.soLop; i++)
		{
			if (maLop == listL.Data[i].maLop)
			{
				system("cls");
				if (listL.Data[i].ListSV.pHead == NULL)
				{
					cout << "Khong co sinh vien nao trong danh sach de xoa !";
					cin.ignore();
					system("cls");
					return;
				}
				else
				{
					bool check = 0;
					string maSV;
					cout << "Moi nhap ma sinh vien de xoa: "; getline(cin, maSV);
					listSINHVIEN temp = listL.Data[i].ListSV;
					if (temp.pHead == NULL) {
						cout << "Lop khong co sinh vien !\n\n";
					}
					else {
						for (nodeSINHVIEN* k = temp.pHead; k != NULL; k = k->pNext) {
							if (maSV == k->data.maSV) {
								if (k->data.listDT.pHead == NULL) {
									xoaBatKy(temp, k->data);
									listL.Data[i].ListSV = temp;
									cout << "sinh vien da xoa thanh cong ! \n\n";
									check = 0;
									return;
								}
								else {
									cout << "Sinh vien da thi,khong the xoa !";
									cin.ignore();
									system("cls");
									return;
								}
							}
						}
						if (check == 0) {
							cout << "Ma sinh vien khong co trong danh sach";
							cin.ignore();
							system("cls");
							return;
						}
					}
				}
			}
		}
	}
	else {
		cout << "Nhap sai ma lop !";
		cin.ignore();
	}
}
SINHVIEN nhapThongTinSinhVien()
{
	SINHVIEN data;

	cout << "ho: "; getline(cin, data.ho); vietHoa(data.ho);
	cout << "ten: "; getline(cin, data.ten); vietHoa(data.ten);

	// check gioi tinh
	cout << "gioi tinh"; cin >> data.gioiTinh;
	// kiem tra trung maSV tat ca cac lop
	while (1) {
		cout << "ma sinh vien: "; getline(cin,data.maSV); vietHoa(data.maSV);
		if (checkMaSV(data.maSV) == true) {
			break;
		}
	}
	cout << "mat khau: "; getline(cin, data.password);
	// khoi tao listDT = NULL;
	data.listDT.pHead = data.listDT.pTail = NULL;
	return data;
}
void themSinhVien()
{
	system("cls");
	int soSV;
	string maLop;
	int x = 0;
	for (int i = 0; i < listL.soLop; i++) cout << listL.Data[i].maLop << "\n";
	bool check = 0;
	while (check == 0)
	{
		cout << "nhap ma lop: "; getline(cin, maLop);
		for (int i = 0; i < listL.soLop; i++) {
			if (maLop == listL.Data[i].maLop) {
				x = i;
				check = 1;
				break;
			}
		}
	}
	cout << "nhap soSV: "; cin >> soSV;
	cin.ignore();
	for (int i = 0; i < soSV; i++)
	{
		nodeSINHVIEN* temp = new nodeSINHVIEN;
		temp->data = nhapThongTinSinhVien();
		temp->pNext = NULL;
		if (listL.Data[x].ListSV.pHead == NULL) {
			listL.Data[x].ListSV.pHead = listL.Data[x].ListSV.pTail = temp;
		}
		else {
			listL.Data[x].ListSV.pTail->pNext = temp;
			listL.Data[x].ListSV.pTail = temp;
		}
	}
}
void nhapSinhVien() {

	int n;
	while (1) {
		cout << "1.them sinh vien\n";
		cout << "2.Sua thong tin sinh vien\n";
		cout << "3.Xoa sinh vien\n";
		cout << "0.Thoat";
		cout << "nhap lua chon cua ban: "; cin >> n;
		if (n == 1) themSinhVien();
		if (n == 2) suaThongTinSinhVien();
		if (n == 3) xoaSinhVien();
		if (n == 0) break;
	}
}


// NHAP MON HOC
void inMonHoc()
{
	while (1)
	{
		int chieudoc = 0;
		int chieungang = 5;
		gotoxy(chieudoc, chieungang); cout << "TEN MON HOC";
		gotoxy(chieudoc + 40, chieungang); cout << "MA MON HOC";
		++chieungang;
		for (int i = 0; i < listMH.soMH; i++)
		{
			gotoxy(chieudoc, chieungang); cout << listMH.danhSach[i].tenMH;
			gotoxy(chieudoc + 40, chieungang); cout << listMH.danhSach[i].maMH;
			++chieungang;
		}
		gotoxy(chieudoc, chieungang + 1); cout << "Nhan ENTER de tro ve MENU";
		cin.ignore();
		system("cls");
		return;
	}
}
void themMonHoc()
{

	int chieudoc = 0;
	int chieungang = 5;
	while (1)
	{
		chieudoc = 0;
		chieungang = 5;
		gotoxy(chieudoc, chieungang); cout << "TEN MON HOC";
		gotoxy(chieudoc + 20, chieungang); cout << "MA MON HOC";
		++chieungang;
		for (int i = 0; i < listMH.soMH; i++)
		{
			gotoxy(chieudoc, chieungang); cout << listMH.danhSach[i].tenMH;
			gotoxy(chieudoc + 20, chieungang); cout << listMH.danhSach[i].maMH;
			++chieungang;
		}
		++chieungang;
		int soMonHoc;
		gotoxy(chieudoc, chieungang); cout << "[=]> Moi ban nhap SO MON HOC muon them: ";
		//gotoxy(chieudoc + 45, chieungang); 
		while (1)
		{
			if (cin >> soMonHoc)
			{
				break;

			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		cin.ignore();
		system("cls");
		while (1)
		{
			while (1)
			{
				chieudoc = 0;
				chieungang = 5;
				++chieungang;
				gotoxy(chieudoc, chieungang); cout << "TEN MON HOC";
				gotoxy(chieudoc + 20, chieungang); cout << "MA MON HOC";
				++chieungang;
				int n = listMH.soMH;
				for (int i = 0; i < n; i++)
				{
					gotoxy(chieudoc, chieungang); cout << listMH.danhSach[i].tenMH;
					gotoxy(chieudoc + 20, chieungang); cout << listMH.danhSach[i].maMH;
					++chieungang;
				}
				++chieungang;

				for (int j = 0; j < soMonHoc; j++)
				{

					MONHOC mh;
					gotoxy(chieudoc, chieungang);     cout << "[]=> MA MON HOC can them thu  " << j + 1 << ": ";
					gotoxy(chieudoc, chieungang + 1); cout << "[]=> TEN MON HOC can them thu " << j + 1 << ": ";
					string maMH;
					string tenMH;

					gotoxy(chieudoc + 40, chieungang); getline(cin, maMH);
					// trung maMH
					while (checkmaMH(maMH) == true)
					{
						gotoxy(chieudoc, chieungang + 3); cout << "->ERROR<- : MA MON HOC bi trung, nhan ENTER de nhap lai !";
						cin.ignore();
						gotoxy(chieudoc, chieungang + 3); cout << "                                                                  ";
						gotoxy(chieudoc + 40, chieungang); cout << "                                                                         ";
						gotoxy(chieudoc + 40, chieungang); getline(cin, maMH);
					}
					gotoxy(chieudoc + 40, chieungang + 1); getline(cin, tenMH);
					// tenMH trung
					while (checktenMH(tenMH) == true)
					{
						gotoxy(chieudoc, chieungang + 4); cout << "->ERROR<- : TEN MON HOC bi trung, nhan ENTER de nhap lai !";
						cin.ignore();
						gotoxy(chieudoc, chieungang + 4); cout << "                                                                  ";
						gotoxy(chieudoc + 40, chieungang + 1); cout << "                                                                         ";
						gotoxy(chieudoc + 40, chieungang + 1); getline(cin, tenMH);
					}

					mh.maMH = maMH;
					mh.tenMH = tenMH;
					listMH.soMH = n + j;
					++listMH.soMH;
					listMH.danhSach[n + j] = mh;
					gotoxy(chieudoc + 40, chieungang); cout << "                                                      ";
					gotoxy(chieudoc + 40, chieungang + 1); cout << "                                                      ";
				}
				system("cls");
				return;
			}
			return;
		}
		return;
	}
}
void suaMonHoc()
{
	int chieungang = 3;
	gotoxy(0, chieungang); cout << "TEN MON HOC";
	gotoxy(20, chieungang); cout << "MA MON HOC";
	++chieungang;
	for (int i = 0; i < listMH.soMH; i++)
	{
		gotoxy(0, chieungang); cout << listMH.danhSach[i].tenMH;
		gotoxy(20, chieungang); cout << listMH.danhSach[i].maMH;
		++chieungang;
	}
	++chieungang;
	string maMH;
	bool isTrue = 1;
	while (1)
	{
		string check_maMH;
		string maMH, tenMH;
		int x = chieungang;
		gotoxy(0, chieungang);         cout << "Moi ban nhap MA MON HOC muon sua: ";
		gotoxy(35, chieungang); getline(cin, check_maMH);

		if (checkmaMH(check_maMH) == true)
		{
			++chieungang;
			gotoxy(0, chieungang);     cout << "Moi ban thay doi MA MON HOC:      ";
			gotoxy(0, chieungang + 1); cout << "Moi ban thay doi TEN MON HOC:     ";
			gotoxy(29, chieungang); getline(cin, maMH);
			gotoxy(29, chieungang + 1); getline(cin, tenMH);
			for (int i = 0; i < listMH.soMH; i++)
			{
				if (check_maMH == listMH.danhSach[i].maMH)
				{
					listMH.danhSach[i].maMH = maMH;
					listMH.danhSach[i].tenMH = tenMH;
					system("cls");
					break;
				}
			}
			return;
		}
		else
		{
			gotoxy(0, chieungang + 3); cout << "MA MON HOC khong chinh xac, nhan ENTER de nhap lai !";
			cin.ignore();
			gotoxy(0, chieungang + 3); cout << "                                                      ";
			gotoxy(35, chieungang); cout << "                                                      ";
		}
		chieungang = x;
	}
}
void xoaMonHoc()
{
	int chieungang = 3;
	gotoxy(0, chieungang); cout << "TEN MON HOC";
	gotoxy(20, chieungang); cout << "MA MON HOC";
	++chieungang;
	for (int i = 0; i < listMH.soMH; i++)
	{
		gotoxy(0, chieungang); cout << listMH.danhSach[i].tenMH;
		gotoxy(20, chieungang); cout << listMH.danhSach[i].maMH;
		++chieungang;
	}
	++chieungang;
	bool isTrue = 1;
	while (1)
	{
		string maMH, tenMH;
		int x = chieungang;
		gotoxy(0, chieungang);  cout << "Moi ban nhap MA MON HOC muon XOA: ";
		gotoxy(35, chieungang); getline(cin, maMH);
		if (checkmaMH(maMH) == true)
		{
			for (int i = 0; i < listMH.soMH; i++)
			{
				if (maMH == listMH.danhSach[i].maMH)
				{
					for (int j = i; j < listMH.soMH; j++)
					{
						listMH.danhSach[j] = listMH.danhSach[j + 1];
					}
					--listMH.soMH;
				}
			}
			cout << "XOA THANH CONG !";
			system("pause");
			system("cls");
			break;
		}
		else
		{
			gotoxy(0, chieungang + 3); cout << "MA MON HOC khong chinh xac, nhan ENTER de nhap lai !";
			cin.ignore();
			gotoxy(0, chieungang + 3); cout << "                                                      ";
			gotoxy(35, chieungang); cout << "                                                      ";
		}
		chieungang = x;
	}
}
void nhapMonHoc()
{
	system("cls");
	int luachon;
	int x = 0, y = 7;
	Nocursortype();
	gotoxy(x + 10, y - 2); cout << "TEN MON HOC";
	gotoxy(x + 50, y - 2); cout << "MA MON HOC";
	for (int i = 0; i < listMH.soMH; i++) {
		Nocursortype;
		gotoxy(x + 10, y); cout << listMH.danhSach[i].tenMH;
		gotoxy(x + 50, y); cout << listMH.danhSach[i].maMH;
		++y;
	}
	gotoxy(x + 10, y + 1); cout << "THEM MON HOC";
	++y;
	int min = 7;
	int max = y;
	int X = x + 8, Y = min;
	while (1) {
		Nocursortype;
		SetColor(15);
		gotoxy(x + 8, Y); cout << (char)219;
		char kitu = _getch();
		if (kitu == Up) {
			if (Y == min) {
				gotoxy(X, Y); cout << "  ";
				Y = max + 1;
			}
			gotoxy(X, Y); cout << "  ";
			Y--;
		}
		if (kitu == Down) {
			if (Y == max) {
				gotoxy(X, Y); cout << "  ";
				Y = min - 1;
			}
			gotoxy(X, Y); cout << "  ";
			Y++;
		}

		if (kitu == Enter) {
			int X = x + 8;
			int y = Y + 6;
			gotoxy(X, Y); cout << "  ";
			SetColor(15);
			gotoxy(X - 2, y); cout << (char)219;
			gotoxy(X, y - 1); cout << "BAN MUON THEM MON HOC ?";
			gotoxy(X, y); cout << "CO";
			gotoxy(X, y + 1); cout << "KHONG";

			while (1) {
				SetColor(15);
				gotoxy(X - 2, y); cout << (char)219;
				char c = _getch();
				if (c == Up) {
					if (y == Y + 6) {
						gotoxy(X - 2, y); cout << " ";
						y = y + 1;
					}
					else {
						gotoxy(X - 2, y); cout << " ";
						--y;
					}

				}
				if (c == Down) {
					if (y == Y + 7) {
						gotoxy(X - 2, y); cout << " ";
						y = y - 1;
					}
					else {
						gotoxy(X - 2, y); cout << " ";
						++y;
					}

				}


				gotoxy(10, 30); cout << "  ";
				gotoxy(10, 30); cout << y;
			}
		}
	}
}




// nhap cau hoi thi
void inThongTinCauHoiChiTiet(CAUHOI ch)
{
	cout << ch.id << endl;
	cout << ch.maMH << endl;
	cout << ch.ND << endl;
	cout << "A.  " << ch.A << endl;
	cout << "B.  " << ch.B << endl;
	cout << "C.  " << ch.C << endl;
	cout << "D.  " << ch.D << endl;
	cout << "DA: " << ch.DA << endl << endl;
}
void xuatLNR(nodeCAUHOI* root, string maMH)
{
	if (root != NULL)
	{
		xuatLNR(root->pLeft, maMH);
		if (root->data.maMH == maMH) {
			inThongTinCauHoiChiTiet(root->data);
		}
		xuatLNR(root->pRight, maMH);
	}
}
void inCauHoiTheoMaMH()
{
	int y = 0;
	system("cls");
	gotoxy(50, y); cout << "CHUC NANG";
	++y;
	gotoxy(48, y); cout << "=============";
	++y;
	gotoxy(45, y); cout << "IN DANH SACH CAU HOI";
	++y;
	gotoxy(0, y); cout << "TEN MON HOC";
	gotoxy(50, y); cout << "MA MON HOC";
	++y;
	for (int i = 0; i < listMH.soMH; i++)
	{
		gotoxy(0, y); cout << listMH.danhSach[i].tenMH;
		gotoxy(50, y); cout << listMH.danhSach[i].maMH;
		++y;
	}
	string maMH;
	gotoxy(0, y + 1); cout << "Moi ban nhap MA MON HOC: ";
	gotoxy(25, y + 1); getline(cin, maMH);
	system("cls");
	for (int i = 0; i < listMH.soMH; i++)
	{
		if (maMH == listMH.danhSach[i].maMH)
		{
			xuatLNR(rootCH, maMH);
		}
	}
	cout << "Nhan ENTER de quay tro ve MENU";
	cin.ignore();
	system("cls");
}
void demSoNodeCH(nodeCAUHOI* p, int& dem)
{
	if (p != NULL) {

		++dem;
		demSoNodeCH(p->pLeft, dem);
		demSoNodeCH(p->pRight, dem);
	}
}
void themCauHoiThi()
{

	for (int i = 0; i < listMH.soMH; i++)
	{
		cout << "TEN MON HOC: ";
		cout << listMH.danhSach[i].tenMH << "\n";
		cout << "MA MON HOC:  ";
		cout << listMH.danhSach[i].maMH << "\n\n";
	}
	int soCH;
	cout << "nhap so cau hoi muon them: ";
	while (1) {
		if (cin >> soCH) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	cin.ignore();
	int count = 0;
	demSoNodeCH(rootCH, count);
	for (int i = 0; i < soCH; i++) {
		CAUHOI data;
		++count;
		data.id = count;
		cout << "ma mon hoc: "; getline(cin, data.maMH);
		cout << "Noi dung cau hoi: "; getline(cin, data.ND);
		cout << "DAP A:       "; getline(cin, data.A);
		cout << "DAP B:       "; getline(cin, data.B);
		cout << "DAP C:       "; getline(cin, data.C);
		cout << "DAP D:       "; getline(cin, data.D);
		cout << "DAP AN DUNG: "; cin >> data.DA;
		cin.ignore();
		for (int i = 0; i < listMH.soMH; i++) {
			if (data.maMH == listMH.danhSach[i].maMH) {
				themCauHoi(rootCH, data);
			}
		}
	}
}
void nhapCauHoi()
{
	int luachon;
	while (1) {
		cout << "0.QUAY LAI MENU" << "\n";
		cout << "1.In danh sach cau hoi" << "\n";
		cout << "2.Them cau hoi " << "\n";
		cout << "nhap lua chon: "; cin >> luachon;
		cin.ignore();
		system("cls");
		if (luachon == 1) {
			inCauHoiTheoMaMH();
		}
		if (luachon == 2) {
			themCauHoiThi();
		}
		if (luachon == 0) {
			system("cls");
			return;
		}
	}
}



// THI TRAC NGHIEM CHO SINH VIEN
void inThongTinCauHoiLamBai(DAPAN DAdata) {
	cout << endl << DAdata.data.id << endl;
	cout << DAdata.data.ND << endl;
	cout << "A.  " << DAdata.data.A << endl;
	cout << "B.  " << DAdata.data.B << endl;
	cout << "C.  " << DAdata.data.C << endl;
	cout << "D.  " << DAdata.data.D << endl;
	cout << "Dap an cua ban: " << " ";
}
void dsCAUHOI(nodeCAUHOI* p, int& n, CAUHOI* CHdata) {
	if (p != NULL) {
		dsCAUHOI(p->pLeft, n, CHdata);
		CHdata[n] = p->data; ++n;
		dsCAUHOI(p->pRight, n, CHdata);
	}
}
void demSoNodeCHTheoMH(nodeCAUHOI* p, int& dem, string maMH)
{
	if (p != NULL) {
		if (p->data.maMH == maMH) ++dem;
		demSoNodeCHTheoMH(p->pLeft, dem, maMH);
		demSoNodeCHTheoMH(p->pRight, dem, maMH);
	}
}
void LoadDeThiTuFile(nodeDAPAN*& temp, string maMH, int soCHMuonThi)
{
	ifstream filein;
	filein.open("CauHoi.txt", ios_base::in);
	int soCH;
	filein >> soCH;

	// load het cau hoi
	int tongSoCH = 0;
	demSoNodeCHTheoMH(rootCH, tongSoCH, maMH);
	// randomID
	int max = tongSoCH;
	int min = 1;
	int N = max - min + 1;
	int* idMH = new int[max];
	for (int i = min; i <= max; i++) {
		idMH[i - min] = i;
	}
	srand(time(0));
	random_shuffle(idMH, idMH + N);

	int count = 0;
	for (int i = 0; i < soCH; i++)
	{
		CAUHOI ch;
		filein >> ch.id; filein.ignore();
		getline(filein, ch.maMH);
		getline(filein, ch.ND);
		getline(filein, ch.A);
		getline(filein, ch.B);
		getline(filein, ch.C);
		getline(filein, ch.D);
		filein >> ch.DA;
		DAPAN DAdata;
		DAdata.data = ch;
		DAdata.DA_USER = NULL;
		if (DAdata.data.maMH == maMH && count < soCHMuonThi) {
			DAdata.data.id = idMH[count];  ++count;
			themDapAn(temp, DAdata);
		}
	}
	filein.close();
}
void sapXepId(nodeDAPAN*& temp, int n, int& m) {
	if (temp != NULL) {
		sapXepId(temp->pLeft, n, m);
		if (m <= n) {
			temp->data.data.id = m; ++m;
		}
		sapXepId(temp->pRight, n, m);
	}
}
void inDe(nodeDAPAN* temp, int& n) {
	if (temp != NULL) {
		inDe(temp->pLeft, n);
		inThongTinCauHoiLamBai(temp->data);
		inDe(temp->pRight, n);
	}
}// LAY DUM ANH CAI MAN HINH DEN Á , CAI MÀN HINH HIÊN RA Á , LA CAI NAO ANH ?
void inDapAn(nodeDAPAN*& temp, int x, int& y, int& count, int& z) {
	if (temp != NULL) {
		inDapAn(temp->pLeft, x, y, count, z);
		gotoxy(x, y); cin >> temp->data.DA_USER; ++z;
		if (temp->data.DA_USER == temp->data.data.DA) {
			++count;
		}
		y = y + 7;
		inDapAn(temp->pRight, x, y, count, z);
	}
}
void checkDuyetDapAn(nodeDAPAN* root, string maMH, bool& check) {
	if (root != NULL) {
		checkDuyetDapAn(root->pLeft, maMH, check);
		if (root->data.data.maMH == maMH) {
			check = 1;
		}
		checkDuyetDapAn(root->pRight, maMH, check);
	}
}
void inDapAn(DAPAN DAdata) {
	cout << DAdata.data.maMH << endl;
	cout << DAdata.data.id << endl;
	cout << DAdata.data.ND << endl;
	cout << DAdata.data.A << endl;
	cout << DAdata.data.B << endl;
	cout << DAdata.data.C << endl;
	cout << DAdata.data.D << endl;
	cout << "dap an cua ban: " << DAdata.DA_USER << endl;
	cout << "dap an dung: " << DAdata.data.DA << endl << endl;
}
void xuatDanhSachDapAn(nodeDAPAN* root, string maMH) {

	if (root != NULL) {
		xuatDanhSachDapAn(root->pLeft, maMH);
		if (maMH == root->data.data.maMH) inDapAn(root->data);
		xuatDanhSachDapAn(root->pRight, maMH);
	}
}
void thiTracNghiemChoSV(SINHVIEN& data)
{
	string tenMH, maMH;
	bool checkTenMH = 0;
	int vitriMH = 0;
	// KIEM TRA TEN MON HOC
	while (checkTenMH == 0) {
		cout << "Moi ban nhap mon thi: "; getline(cin, tenMH);
		for (int i = 0; i < listMH.soMH; i++) {
			if (tenMH == listMH.danhSach[i].tenMH) {
				maMH = listMH.danhSach[i].maMH;
				vitriMH = i;
				checkTenMH = 1;
				break;
			}
		}
		if (checkTenMH == 1) break;
	}
	// check : dathi
	int soCHMuonThi;
	cout << "nhap so cau hoi ban muon thi: ";  cin >> soCHMuonThi;
	system("cls");
	cout << "ten mon thi : " << tenMH << endl;
	cout << "so cau hoi theo mon: " << soCHMuonThi << "\n";

	// in cau hoi ra man hinh
	// mon hoc thi dung 1 lan
	SINHVIENDATHI SVdata;
	SVdata.maSV = data.maSV;
	SVdata.diem = -1;
	SVdata.soCauDung = -1;
	SVdata.rootDA = NULL;



	int x = 16, y = 9, count = 0, soCHTheoMH = 0;
	LoadDeThiTuFile(SVdata.rootDA, maMH, soCHMuonThi); // dua cau hoi va dap an vao SVdata
	int z = 0;
	inDe(SVdata.rootDA, soCHTheoMH);
	inDapAn(SVdata.rootDA, x, y, count, z);
	int stt = 1;
	sapXepId(SVdata.rootDA, soCHMuonThi, stt);



	// sau khi thi xong :
	SVdata.soCauDung = count;
	SVdata.maSV = data.maSV;
	float diemMoiCau = 0;;

	if (count == soCHMuonThi) {
		SVdata.diem = 10;
	}
	else {
		diemMoiCau = (float)10 / soCHMuonThi;
		diemMoiCau = roundf(diemMoiCau * 10) / 10;
		SVdata.diem = diemMoiCau * count;
	}

	// check sinh vien da thi hay chua
	nodeDIEMTHI* k = new nodeDIEMTHI;
	k->data.diem = SVdata.diem;
	k->data.maMH = maMH;
	k->pNext = NULL;

	if (data.listDT.pHead == NULL) { // SINH VIEN CHUA THI MON NAO
		data.listDT.pHead = data.listDT.pTail = k;
	}
	else { //  SINH VIEN DA THI ROI
		bool trung = 0; // 1: trung mon thi
		for (nodeDIEMTHI* k = data.listDT.pHead; k != NULL; k = k->pNext) {
			if (k->data.maMH == maMH) { // SINH VIEN THI MON NAY ROI 
				k->data.diem = SVdata.diem;
				trung = 1;
				break;
			}
		}
		if (trung == 0) { // SINH VIEN CHUA THI MON NAY
			data.listDT.pTail->pNext = k;
			data.listDT.pTail = k;
		}
	}

	system("cls");
	// luu dap an cho sinh vien
	nodeSINHVIENDATHI* nodeSVDT = new nodeSINHVIENDATHI;
	nodeSVDT->data = SVdata;
	nodeSVDT->pNext = NULL;

	// neu chua co sinh vien nao thi:
	if (listSVDT.pHead == NULL) {                                  // th1 : chua co sinh vien thi   
		listSVDT.pHead = listSVDT.pTail = nodeSVDT;
	}
	else { // neu DA CO SINH VIEN THI ROI
		for (nodeSINHVIENDATHI* k = listSVDT.pHead; k != NULL; k = k->pNext) {
			if (k->data.maSV == data.maSV) {
				if (k->data.rootDA != NULL) {
					bool check = 0;
					checkDuyetDapAn(k->data.rootDA, maMH, check);
					if (check == 1) {
						if (k->data.rootDA->data.data.maMH == maMH) {  // th2: thi cung 1 mon 2 lan tro len
							k->data = SVdata;
						}
					}
					else {                                         // th3: thi 1 mon 1 lan
						listSVDT.pTail->pNext = nodeSVDT;
						listSVDT.pTail = nodeSVDT;
					}
				}
			}
		}
	}
	cout << "\nso cau dung: " << nodeSVDT->data.soCauDung;
	cout << "\nSo diem ban dat duoc: " << nodeSVDT->data.diem;
	cin.ignore();
	system("cls");

	for (nodeSINHVIENDATHI* m = listSVDT.pHead; m != NULL; m = m->pNext) {
		if (m->data.maSV == data.maSV) {
			cout << m->data.maSV << "\n";
			if (m->data.rootDA != NULL) {
				bool check = 0;
				checkDuyetDapAn(m->data.rootDA, maMH, check);
				cout << "\nma sinh vien : " << m->data.maSV;
				cout << "\nma mon hoc :" << maMH;
				cout << "\ncheck = " << check << endl;
				if (check == 1) {
					cout << "Ket qua cua sinh vien: " << data.ho << " " << data.ten << "\n";
					xuatDanhSachDapAn(m->data.rootDA, maMH);
					cout << "\nDiem: " << m->data.diem;
					cout << "\nSo cau dung: " << m->data.soCauDung;
					break;
				}
				else cout << "SINH VIEN CHUA THI MON NAY";
			}
		}
	}
}


// IN DAP AN CUA SINH VIEN
void inCauHoiDaThi(SINHVIEN data) {
	system("cls");
	bool check = 0;
	string tenMH, maMH;
	int danhDau = -1;
	while (1) {
		bool check = 0;
		cout << "Moi ban nhap ten mon hoc de xem danh sach cau hoi da thi: "; getline(cin, tenMH);
		for (int i = 0; i < listMH.soMH; i++) {
			if (tenMH == listMH.danhSach[i].tenMH) {
				maMH = listMH.danhSach[i].maMH;
				check = 1;
				break;
			}
		}
		if (check == 1) break;
	}


	if (listSVDT.pHead == NULL) {
		cout << "\nsinh vien chua thi";
		return;
	}
	else {
		for (nodeSINHVIENDATHI* m = listSVDT.pHead; m != NULL; m = m->pNext) {
			if (m->data.maSV == data.maSV) {
				bool check = 0;
				checkDuyetDapAn(m->data.rootDA, maMH, check);
				if (check == 1) {
					cout << "Ket qua cua sinh vien: " << data.ho << " " << data.ten << "\n";
					xuatDanhSachDapAn(m->data.rootDA, maMH);
					cout << "\nDiem: " << m->data.diem;
					cout << "\nSo cau dung: " << m->data.soCauDung;
					break;
				}
				else cout << "SINH VIEN CHUA THI MON NAY";
			}
		}
	}
}


// IN BANG DIEM CUA 1 LOP
void inBangDiemMonHocCua1Lop()
{
	system("cls");
	string tenLop;
	string tenMH;
	cout << "so lop: " << listL.soLop << "\n";

	for (int i = 0; i < listL.soLop; i++) {
		cout << "Ten Lop: ";
		cout << listL.Data[i].tenLop << "\n";
		cout << "Ma lop: ";
		cout << listL.Data[i].maLop;
		cout << "\n\n";
	}
	bool check = 0;
	cout << "\nnhap ten lop de xem diem thi: "; getline(cin, tenLop);
	for (int i = 0; i < listL.soLop; i++) {
		if (tenLop == listL.Data[i].tenLop) {
			for (nodeSINHVIEN* k = listL.Data[i].ListSV.pHead; k != NULL; k = k->pNext) {
				cout << "\nDiem cua sinh vien : " << k->data.ho << " " << k->data.ten;
				cout << "\nMa sinh vien: " << k->data.maSV << "\n\n";
				for (int j = 0; j < listMH.soMH; j++) {
					cout << listMH.danhSach[j].tenMH << ": ";
					check = 0;
					for (nodeDIEMTHI* p = k->data.listDT.pHead; p != NULL; p = p->pNext) {
						if (listMH.danhSach[j].maMH == p->data.maMH) {
							check = 1;
							cout << p->data.diem << "\n";
						}
					}
					if (check == 0) cout << " <CHUA THI>\n";

				}
				cout << "==========================\n";
			}
			break;
		}
	}
}


// GHI FILE
int demSoMonThi(listDIEMTHI listDT)
{
	int count = 0;
	if (listDT.pHead == NULL) return 0;
	if (listDT.pHead != NULL) {
		for (listDT.pHead; listDT.pHead != NULL; listDT.pHead = listDT.pHead->pNext) {
			++count;
		}
		return count;
	}
}
void ghiDiemSinhVien(ofstream& fileout, DIEMTHI dt)
{
	fileout << dt.maMH << endl;
	fileout << dt.diem << endl;
}
void ghiListDiem(ofstream& fileout, listDIEMTHI listDT)
{
	for (nodeDIEMTHI* k = listDT.pHead; k != NULL; k = k->pNext) {
		ghiDiemSinhVien(fileout, k->data);
	}
}
void ghiDanhSachSinhVien(ofstream& fileout, listSINHVIEN listSV)
{
	for (nodeSINHVIEN* k = listSV.pHead; k != NULL; k = k->pNext) {
		fileout << k->data.ho << endl;
		fileout << k->data.ten << endl;
		fileout << k->data.gioiTinh << endl;
		fileout << k->data.maSV << endl;
		fileout << k->data.password << endl;
		if (demSoMonThi(k->data.listDT) == 0) {
			fileout << 0 << endl;
		}
		else {
			fileout << demSoMonThi(k->data.listDT) << endl;
			ghiListDiem(fileout, k->data.listDT);
		}
	}
}
void ghiFileLop()
{
	ofstream fileout;
	fileout.open("LOPDEMO.txt", ios::out);
	if (listL.soLop == 0) {
		fileout << 0 << endl;
		return;
	}
	else {
		fileout << listL.soLop << endl;
		for (int i = 0; i < listL.soLop; i++) {
			if (listL.Data[i].ListSV.pHead == NULL) {
				fileout << listL.Data[i].maLop << endl;
				fileout << listL.Data[i].tenLop << endl;
				fileout << 0 << endl;
			}
			else {
				fileout << listL.Data[i].maLop << endl;
				fileout << listL.Data[i].tenLop << endl;
				int soLuongSV = 0;
				for (nodeSINHVIEN* z = listL.Data[i].ListSV.pHead; z != NULL; z = z->pNext) {
					++soLuongSV;
				}
				fileout << soLuongSV << endl;
				ghiDanhSachSinhVien(fileout, listL.Data[i].ListSV);

			}
		}
	}

}
void ghiMonHoc(ofstream& fileout, MONHOC mh)
{
	fileout << mh.tenMH << endl;
	fileout << mh.maMH << endl;
}
void ghiListMonHoc()
{
	ofstream fileout;
	fileout.open("MonHoc.txt", ios::trunc);
	if (listMH.soMH == 0) {
		fileout << 0 << endl;
	}
	else {
		fileout << listMH.soMH << endl;
		for (int i = 0; i < listMH.soMH; i++) {
			ghiMonHoc(fileout, listMH.danhSach[i]);
		}
	}

	fileout.close();
}
void ghiThongTinCauHoi(ofstream& fileout, CAUHOI data)
{
	fileout << data.id << endl;
	fileout << data.maMH << endl;
	fileout << data.ND << endl;
	fileout << data.A << endl;
	fileout << data.B << endl;
	fileout << data.C << endl;
	fileout << data.D << endl;
	fileout << data.DA << endl;
}
void ghiCauHoi(ofstream& fileout, nodeCAUHOI* root)
{
	if (root != NULL) {
		ghiCauHoi(fileout, root->pLeft);
		ghiThongTinCauHoi(fileout, root->data);
		ghiCauHoi(fileout, root->pRight);
	}
}
void ghiListCauHoi()
{
	ofstream fileout;
	fileout.open("CauHoi.txt", ios_base::trunc);
	int soCH = 0;
	demSoNodeCH(rootCH, soCH);
	if (soCH == 0) {
		fileout << 0 << endl;
	}
	else {
		demSoNodeCH(rootCH, soCH);
		fileout << soCH << endl;
		ghiCauHoi(fileout, rootCH);
	}
	fileout.close();
}
void ghiDapAn(ofstream& fileout, DAPAN DAdata) {
	fileout << DAdata.data.maMH << endl;
	fileout << DAdata.data.id << endl;
	fileout << DAdata.data.ND << endl;
	fileout << DAdata.data.A << endl;
	fileout << DAdata.data.B << endl;
	fileout << DAdata.data.C << endl;
	fileout << DAdata.data.D << endl;
	fileout << DAdata.data.DA << endl;
	fileout << DAdata.DA_USER << endl;
}
void demSoCHdaThi(nodeDAPAN* k, int& count) {
	if (k == NULL) return;
	else {
		demSoCHdaThi(k->pLeft, count);
		++count;
		demSoCHdaThi(k->pRight, count);
	}
}
void ghiDanhSachDapAn(ofstream& fileout, nodeDAPAN* k) {
	if (k != NULL) {
		ghiDanhSachDapAn(fileout, k->pLeft);
		ghiDapAn(fileout, k->data);
		ghiDanhSachDapAn(fileout, k->pRight);
	}
}
void ghiSinhVienDaThi(ofstream& fileout, SINHVIENDATHI SVdata) {
	fileout << SVdata.maSV << endl;
	int soCHdathi = 0;
	demSoCHdaThi(SVdata.rootDA, soCHdathi);
	fileout << soCHdathi << endl;
	ghiDanhSachDapAn(fileout, SVdata.rootDA);
	fileout << SVdata.soCauDung << endl;
	fileout << SVdata.diem << endl;
}
int demSVdaThi() {
	int count = 0;
	if (listSVDT.pHead == NULL) return 0;
	for (nodeSINHVIENDATHI* k = listSVDT.pHead; k != NULL; k = k->pNext) ++count;
	return count;
}
void ghiDanhSachSinhVienDaThi() {

	ofstream fileout;
	fileout.open("luuCAUHOIDATHI.txt", ios_base::trunc);
	if (listSVDT.pHead == NULL) {
		fileout << 0;
	}
	else {
		int soSVdathi = demSVdaThi();
		fileout << soSVdathi << endl;
		for (nodeSINHVIENDATHI* k = listSVDT.pHead; k != NULL; k = k->pNext) {
			ghiSinhVienDaThi(fileout, k->data);
		}
	}
}
void ghiFile()
{
	ghiListMonHoc();
	ghiListCauHoi();
	ghiFileLop();
	ghiDanhSachSinhVienDaThi();
}

// CHUC NANG CUA GV
void GV()
{

	int x = 10, y = 5;
	gotoxy(x + 20, y - 3); cout << "========== CAC CHUC NANG CUA GIAO VIEN ==========";
	gotoxy(x, y); cout << "Nhap lop.";
	gotoxy(x, y + 1); cout << "In danh sach lop.";
	gotoxy(x, y + 2); cout << "Nhap sinh vien.";
	gotoxy(x, y + 3); cout << "Nhap mon hoc.";
	gotoxy(x, y + 4); cout << "Nhap cau hoi thi.";
	gotoxy(x, y + 5); cout << "Thi trac nghiem.";
	gotoxy(x, y + 6); cout << "In bang diem thi trac nghiem cua 1 lop.";
	gotoxy(x, y + 7); cout << "Thoat chuong trinh.";

	while (1)
	{

		Nocursortype();
		SetColor(15);
		gotoxy(x - 2, y); cout << (char)219;
		gotoxy(x - 3, y); cout << (char)219;
		char c = _getch();

		if (c == Up) {
			if (y == 5) {
				gotoxy(x - 2, y); cout << " ";
				gotoxy(x - 3, y); cout << " ";
				y = y + 8;
			}
			gotoxy(x - 2, y); cout << " ";
			gotoxy(x - 3, y); cout << " ";
			--y;
		}
		if (c == Down) {
			if (y == 12) {
				gotoxy(x - 2, y); cout << " ";
				gotoxy(x - 3, y); cout << " ";
				y = y - 8;
			}
			gotoxy(x - 2, y); cout << " ";
			gotoxy(x - 3, y); cout << " ";
			++y;
		}
		if (c == Enter) {
			system("cls");
			if (y == 5) nhapLop();
			if (y == 6) inDanhSachLop();
			if (y == 7) nhapSinhVien();
			if (y == 8) nhapMonHoc();
			if (y == 9) nhapCauHoi();
			//if (y == 10) thiTracNghiemChoGV();
			if (y == 11) inBangDiemMonHocCua1Lop();
			if (y == 12) {
				system("cls");
				gotoxy(40, 5); cout << "CAM ON BAN DA SU DUNG CHUONG TRINH";
				break;
			}
			break;
		}
	}
}

// CHUC NANG SV
void SV(SINHVIEN& data)
{

	int x = 3, y = 10;
	gotoxy(x + 25, y - 9); cout << "========== CHUC NANG CUA SINH VIEN ==========";
	gotoxy(x, y - 2); cout << "TEN SINH VIEN: " << data.ho << " " << data.ten;
	gotoxy(x, y); cout << "Thi trac nghiem";
	gotoxy(x, y + 1); cout << "In cac cau hoi da thi";
	gotoxy(x, y + 2); cout << "Thoat chuong trinh";

	while (1) {

		Nocursortype();
		SetColor(15);
		gotoxy(x - 2, y); cout << (char)219;

		char c = _getch();

		if (c == Up) {
			Nocursortype();
			if (y == 10) {
				gotoxy(x - 2, y); cout << " ";
				y = y + 3;
			}
			gotoxy(x - 2, y); cout << " ";
			--y;
		}
		if (c == Down) {

			if (y == 12) {
				gotoxy(x - 2, y); cout << " ";
				y = y - 3;
			}
			gotoxy(x - 2, y); cout << " ";
			++y;
		}
		if (c == Enter) {
			Cursortype();
			system("cls");
			if (y == 10) {
				thiTracNghiemChoSV(data);
				cin.ignore();
				system("cls");
				break;
			}
			else if (y == 11) {
				inCauHoiDaThi(data);
				cin.ignore();
				system("cls");
				break;
			}
			else if (y == 12) {
				x = 3, y = 10;
				gotoxy(x + 25, y - 9); cout << "                                                            ";
				gotoxy(x, y - 2); cout << "                                                                 ";
				gotoxy(x, y); cout << "                                                                     ";
				gotoxy(x, y + 1); cout << "                                                                 ";
				gotoxy(x, y + 2); cout << "                                                                 ";
				gotoxy(x - 2, y + 2); cout << "  ";
				gotoxy(x + 27, y + 5); cout << "==========HEN GAP BAN LAN SAU==========";
				gotoxy(0, y + 10); cout << "Nhan nut bat ki de thoat";
				gotoxy(x + 27, y + 7);
				cout << "                     ";
				break;
			}
		}
	}
}

void dangNhap()
{
	string tk, mk;
	int x = 15, y = 10;
	int check = 0;
	gotoxy(20, 3); cout << "==================== CHUONG TRINH THI TRAC NGHIEM ====================";
	gotoxy(0, y); cout << "TEN DANG NHAP: ";
	gotoxy(0, y + 1); cout << "MAT KHAU     : ";
	gotoxy(15, y);
	char kitu;
	bool check1 = 1;
	while (check1) {
		gotoxy(x, y); cout << "                                                              ";
		gotoxy(x, y + 1); cout << "                                                                    ";
		while (1) {
			gotoxy(x, y);
			if (_kbhit()) {
				kitu = _getch();
				if ((kitu >= 'A' && kitu <= 'z') || (kitu >= '0' && kitu <= '9')) {
					if (tk.length() < 10) {
						tk.push_back(kitu);
						cout << kitu;
						++x;
					}

				}
				if (kitu == Backspace) {
					if (tk.length() > 0) {
						tk.erase(tk.length() - 1, 1);
						cout << "\b \b";
						--x;
					}

				}
				if (kitu == Enter) {
					++y; x = 15;
					gotoxy(x, y);
					break;
				}
			}
		}
		while (1) {
			gotoxy(x, y);
			if (_kbhit()) {
				kitu = _getch();
				if ((kitu >= 'A' && kitu <= 'z') || (kitu >= '0' && kitu <= '9')) {
					if (mk.length() < 20) {
						mk.push_back(kitu);
						cout << "*";
						++x;
					}
				}
				if (kitu == Backspace) {
					if (mk.length() > 0) {
						mk.erase(mk.length() - 1, 1);
						cout << "\b \b";
						--x;
					}

				}
				if (kitu == Enter) {
					x = 15;
					break;
				}
			}
		}
		if (tk == "GV" && mk == "GV") {
			system("cls");
			GV();
			break;
		}

		else {
			bool check = 0;
			SINHVIEN SVdata;
			for (int i = 0; i < listL.soLop; i++) {
				for (nodeSINHVIEN* k = listL.Data[i].ListSV.pHead; k != NULL; k = k->pNext) {
					vietHoa(tk);
					if (k->data.maSV == tk && k->data.password == mk) {
						system("cls");
						SV(k->data);
						check = 1;
						check1 = 0;
						break;
					}
				}
			}
			if (check == 0) {
				gotoxy(x, y + 5); cout << "Mat khau sai, nhan Enter de nhap lai";
				cin.ignore();
				gotoxy(x, y + 5); cout << "                                                                                            ";
				x = 15; y = 10;
				tk = "";
				mk = "";
				gotoxy(x, y);
			}
		}
		if (check1 == 0) break;
	}
}

int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	LoadDuLieuTuFile();
	dangNhap();
	ghiFile();		
    return _getch();
}






