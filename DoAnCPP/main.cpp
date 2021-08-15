
#include"mylib.h"
#include"structData.h"
#include<string.h>
#include<iostream>
#include<string>
#include<time.h>
#include<fstream>
#include<algorithm>
#include<Windows.h>
#include<thread>
#include<conio.h>

using namespace std;

// Khai bao bien toan cuc

listLOP listL;
listMONHOC listMH;
nodeCAUHOI* rootCH;

int* id = new int[10000];
int count_id = 0;


const int X = 80;
const int Y = 20;

// thanh sang
void thanhsangMoi(int tdX, int tdY, string s1, string s2) {

	for (int i = 0; i < 65; i++) {
		SetBGColor(5); gotoxy(tdX + i, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << s1;
	gotoxy(tdX + 40, tdY); cout << s2;	
}
void thanhsangCu(int tdX, int tdY, string s1, string s2) {

	for (int i = 0; i < 65; i++) {
		SetBGColor(16); gotoxy(tdX + i, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << s1;
	gotoxy(tdX + 40, tdY); cout << s2;
}
void thanhsangMoi_menu(int tdX, int tdY, string nd, int color) {

	for (int i = 0; i < 30; i++) {
		SetBGColor(color); gotoxy(tdX + i, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << nd;
}
void thanhsangCu_menu(int tdX, int tdY, string nd) {

	for (int i = 0; i < 30; i++) {
		SetBGColor(16); gotoxy(tdX + i, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << nd;
}
void thanhsang_menu(int tdX, int tdY, int tdYcu, string temp[2], int min, int color) {
	int a, b;
	a = (tdY - min) / 2;
	thanhsangMoi_menu(tdX, tdY, temp[a], color);
	b = (tdYcu - min) / 2;
	thanhsangCu_menu(tdX, tdYcu, temp[b]);
}
void thanhsang_lop(int tdX, int tdY, int tdYcu, int min) {
	int a, b;
	a = (tdY - min) / 2;
	thanhsangMoi(tdX, tdY, listL.Data[a].tenLop, listL.Data[a].maLop);
	b = (tdYcu - min) / 2;
	thanhsangCu(tdX, tdYcu, listL.Data[b].tenLop, listL.Data[b].maLop);
}
void thanhsang_monhoc(int tdX, int tdY, int tdYcu, int min) {
	int a, b;
	string khoangtrang = "                    ";
	a = (tdY - min) / 2;
	thanhsangMoi(tdX, tdY, listMH.danhSach[a].tenMH, listMH.danhSach[a].maMH);
	b = (tdYcu - min) / 2;
	thanhsangCu(tdX, tdYcu, listMH.danhSach[b].tenMH, listMH.danhSach[b].maMH);
}
void thanhsang_sinhvien(int tdX, int tdY, int tdYcu, int min) {
	
	// thanh sang cu
	int b = tdYcu - min;
	for (int i = 2; i < 79; i++) {
		SetBGColor(16); gotoxy(tdX + i, tdYcu); cout << " ";
	}
	gotoxy(20 + tdX, tdYcu); cout << (char)179; // chieu doc
	gotoxy(40 + tdX, tdYcu); cout << (char)179; // chieu doc
	gotoxy(60 + tdX, tdYcu); cout << (char)179; // chieu doc
	
	// thanh sang moi
	int a = tdY - min;
	for (int i = 2; i < 79; i++) {
		SetBGColor(5); gotoxy(tdX + i, tdY); cout << " ";
	}
	gotoxy(20 + tdX, tdY); cout << (char)179; // chieu doc
	gotoxy(40 + tdX, tdY); cout << (char)179; // chieu doc
	gotoxy(60 + tdX, tdY); cout << (char)179; // chieu doc
}
void thanhsangcu_hcn(int tdX, int tdY, string nd) {
	for (int i = 0; i < 30; i++) {
		SetBGColor(16); gotoxy(tdX + i - 1, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << nd;
}
void thanhsangmoi_hcn(int tdX, int tdY, string nd) {
	for (int i = 0; i < 30; i++) {
		SetBGColor(5); gotoxy(tdX + i - 1, tdY); cout << " ";
	}
	gotoxy(tdX, tdY); cout << nd;
}
void thanhsang_hcn(int tdX, int tdY, int tdYcu, string nd[], int min) {
	int a, b;
	a = (tdY - min) / 2;
	thanhsangmoi_hcn(tdX, tdY, nd[a]);
	b = (tdYcu - min) / 2;
	thanhsangcu_hcn(tdX, tdYcu, nd[b]);
}
void xoa() {
	const int X = 100, Y = 20;
	int i;
	for (i = 0; i < 4; i++) {
		gotoxy(X, Y + i); cout << "                                              ";
	}
}
void khung() {
	
}
void khungmonhoc(int tdX, int tdY, int dai, int rong) {
	// thanh doc
	int i;
	for (i = 0; i <= dai; i++) {
		gotoxy(tdX, i + tdY); cout << "o";
		gotoxy(tdX + rong, i + tdY); cout << "o";
	}
	int max = i + tdY - 1; // max doc
	// thanh ngang
	for (i = 0; i <= rong; i++) {
		gotoxy(tdX + i, tdY - 1); cout << "o";
		gotoxy(tdX + i, max + tdY); cout << "o";
	}
}


// hop
void CreatBox(int x, int y, int w, int h)
{
	for (int ix = x; ix < x + w - 1; ix++)
	{
		gotoxy(ix, y);
		cout << char(196);
		gotoxy(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; ++iy)
	{
		gotoxy(x, iy); cout << char(179);
		gotoxy(x + w - 1, iy); cout << char(179);
		gotoxy(x + 10, iy); cout << char(179);
		gotoxy(x + 60, iy); cout << char(179);
		gotoxy(x + 80, iy); cout << char(179);
		gotoxy(x + 100, iy); cout << char(179);
		gotoxy(x + 140, iy); cout << char(179);
	}
	//Noi goc
	gotoxy(x, y); cout << char(218);	
	gotoxy(x + w - 1, y); cout << char(191);
	gotoxy(x, y + h); cout << char(192);
	gotoxy(x + w - 1, y + h); cout << char(217);
	//Noi canh
	gotoxy(x + 10, y); cout << char(194);
	gotoxy(x + 10, y + h); cout << char(193);
	gotoxy(x + 60, y); cout << char(194);
	gotoxy(x + 60, y + h); cout << char(193);
	gotoxy(x + 80, y); cout << char(194);
	gotoxy(x + 80, y + h); cout << char(193);
	gotoxy(x + 100, y); cout << char(194);
	gotoxy(x + 100, y + h); cout << char(193);
	gotoxy(x + 140, y); cout << char(194);
	gotoxy(x + 140, y + h); cout << char(193);

}
void Box(int count)
{
	const int x = 16;
	const int y = 9;
	CreatBox(x, y, 179, 2);
	int i = count;
	CreatBox(x, y + (i * 2), 179, 2);
	//Noi goc
	gotoxy(x, y + (i * 2)); cout << char(195);
	gotoxy(x + 179 - 1, y + (i * 2)); cout << char(180);
	//Noi canh
	gotoxy(x + 10, y + (i * 2)); cout << char(197);
	gotoxy(x + 60, y + (i * 2)); cout << char(197);
	gotoxy(x + 80, y + (i * 2)); cout << char(197);
	gotoxy(x + 100, y + (i * 2)); cout << char(197);
	gotoxy(x + 140, y + (i * 2)); cout << char(197);
	//++i;
}
void Box_InSinhVien(int tdX, int tdY) {
	int soSV = 26;
	int count = 0;
	int j = 0;
	// chieu ngang
	for (int i = 1; i < 80; i++) {
		gotoxy(i + tdX, tdY - 1); cout << (char)219;
		gotoxy(i + tdX, tdY + 2); cout << (char)196;
		gotoxy(i + tdX, tdY + soSV * 2 + 1); cout << (char)219; // thanh duoi chot
	}
	// chieu doc
	for (int i = 0; i < soSV*2 + 1 ; i++) {
		gotoxy(0+tdX + 1, i + tdY); cout << (char)219;
		gotoxy(20+tdX, i + tdY); cout << (char)179;
		gotoxy(40 + tdX, i + tdY); cout << (char)179;
		gotoxy(60 + tdX, i + tdY); cout << (char)179;
		gotoxy(80 + tdX - 1, i + tdY); cout << (char)219;
	}
	gotoxy(tdX + 5, tdY + 1); cout << "Ma Sinh Vien";
	gotoxy(tdX + 25, tdY + 1); cout << "Ho va Ten lot";
	gotoxy(tdX + 45, tdY + 1); cout << "Ten Chinh";
	gotoxy(tdX + 65, tdY + 1); cout << "Gioi Tinh";
}
void Box_InDiemThi(int tdX, int tdY) {
	int soSV = 26;
	int count = 0;
	int j = 0;
	// chieu ngang
	for (int i = 1; i < 80; i++) {
		gotoxy(i + tdX, tdY - 1); cout << (char)219;
		gotoxy(i + tdX, tdY + 2); cout << (char)196;
		gotoxy(i + tdX, tdY + soSV * 2 + 1); cout << (char)219; // thanh duoi chot
	}
	// chieu doc
	for (int i = 0; i < soSV * 2 + 1; i++) {
		gotoxy(0 + tdX + 1, i + tdY); cout << (char)219;
		gotoxy(20 + tdX, i + tdY); cout << (char)179;
		gotoxy(40 + tdX, i + tdY); cout << (char)179;
		gotoxy(60 + tdX, i + tdY); cout << (char)179;
		gotoxy(80 + tdX - 1, i + tdY); cout << (char)219;
	}
	gotoxy(tdX + 5, tdY + 1); cout << "Ma Sinh Vien";
	gotoxy(tdX + 25, tdY + 1); cout << "Ho va Ten lot";
	gotoxy(tdX + 45, tdY + 1); cout << "Ten Chinh";
	gotoxy(tdX + 65, tdY + 1); cout << "Diem Thi";
}
void box_dangnhap(int tdX, int tdY, int chieudai) {
	// thanh ngang 
	int i;
	tdY++;
	for (i = 0; i < chieudai; i++) {
		gotoxy(tdX + i, tdY); cout << (char)196;
		gotoxy(tdX + i, tdY + 2); cout << (char)196;
		gotoxy(tdX + i, tdY + 4); cout << (char)196;
		//gotoxy(tdX + i, tdY + 6); cout << (char)196;
	}
	int max = i - 1;
	gotoxy(tdX, tdY); cout << (char)218;        // goc trai tren cung
	gotoxy(tdX + max, tdY); cout << (char)191;  // goc phai tren cung

	// thanh doc
	for (i = 1; i < 4; i++) {
		gotoxy(tdX, tdY + i); cout << (char)179;
		gotoxy(tdX + max, tdY + i); cout << (char)179;
		gotoxy(tdX + 15, tdY + i); cout << (char)179;
	}
	gotoxy(tdX + 15, tdY); cout << (char)194; // thanh giua tren cung

	int max1 = i;
	gotoxy(tdX, tdY + max1); cout << (char)192; // goc trai duoi cung
	gotoxy(tdX + max, tdY + max1); cout << (char)217; // goc phai duoi cung
	gotoxy(tdX + 15, tdY + max1); cout << (char)193; // thanh giua cuoi
}
void nutEsc() {
	gotoxy(0, 0); cout << "oooooooooooooooooooooo";
	gotoxy(0, 1); cout << "OO        ESC       OO";
	gotoxy(0, 2); cout << "OO     (TRO LAI)    OO";
	gotoxy(0, 3); cout << "oooooooooooooooooooooo";
}
void box_hcn(int tdX, int tdY) {
	int i;
	for (i = 0; i < 30; i++) {
		gotoxy(tdX + i, tdY); cout << (char)196; // ngang
		gotoxy(tdX + i, tdY + 2); cout << (char)196;
		//gotoxy(tdX + i, tdY + 4); cout << (char)196; // ngang
		//gotoxy(tdX + i, tdY + 6); cout << (char)196;
		if (i < 1) {
			gotoxy(tdX - 1, tdY + i + 1); cout << (char)179; // doc
			gotoxy(tdX + 30, tdY + i + 1); cout << (char)179;
		}
	}
	gotoxy(tdX - 1, tdY); cout << (char)218;        // goc trai tren cung
	gotoxy(tdX + 30, tdY); cout << (char)191;  // goc phai tren cung
	gotoxy(tdX - 1, tdY + 2); cout << (char)192; // goc trai duoi cung
	gotoxy(tdX + 30, tdY + 2); cout << (char)217; // goc phai duoi cung
}
void box_hcn1(int tdX, int tdY, int length) {
	int i;
	for (i = 0; i < length; i++) {
		gotoxy(tdX + i, tdY); cout << (char)196; // ngang
		gotoxy(tdX + i, tdY + 2); cout << (char)196;
		//gotoxy(tdX + i, tdY + 4); cout << (char)196; // ngang
		//gotoxy(tdX + i, tdY + 6); cout << (char)196;
		if (i < 1) {
			gotoxy(tdX - 1, tdY + i + 1); cout << (char)179; // doc
			gotoxy(tdX + length, tdY + i + 1); cout << (char)179;
		}
	}
	gotoxy(tdX - 1, tdY); cout << (char)218;        // goc trai tren cung
	gotoxy(tdX + length, tdY); cout << (char)191;  // goc phai tren cung
	gotoxy(tdX - 1, tdY + 2); cout << (char)192; // goc trai duoi cung
	gotoxy(tdX + length, tdY + 2); cout << (char)217; // goc phai duoi cung
}


// LOAD FILE
void LoadDanhSachLopTuFile(){
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
/*void randomid() {

	srand(time(NULL));
	int max = 10000;
	int min = 1;
	int N = max - min + 1;
	int i;

	for (i = min; i <= max; i++) {
		id[i - min] = i;
	}

	random_shuffle(id, id + N);

	ofstream fileout;
	fileout.open("idRanDom.txt", ios_base::out);
	for (i = 0; i < 10000; i++) {
		fileout << id[i];
		fileout << endl;
	}
	fileout.close();
	delete[] id;
}*/
void LoadID() {
	ifstream filein;
	filein.open("idRanDom.txt", ios_base::in);
	int soID;
	filein >> soID;
	int i = 0;
	for (i; i < soID; i++) {
		filein >> id[i];
		++count_id;
	}
	filein.close();
}
void LoadCauHoiTuFile()
{
	ifstream filein;
	filein.open("CauHoi.txt", ios_base::in);
	int soCH = 0;
	filein >> soCH;
	
	
	if (soCH == 0) {
		filein.close();
		return;
	}
	else {
		rootCH = NULL;
		//randomid();
		for (int i = 0; i < soCH; i++)
		{
			CAUHOI ch;
			filein >> ch.id;
			filein.ignore();
			
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

}
void LoadDuLieuTuFile()
{
	LoadID();
	LoadDanhSachLopTuFile();
	LoadDanhSachMonHocTuFile();
	LoadCauHoiTuFile();
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
			if (maSV == k->data.maSV) return false; // neu giong nhau thi sai
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
		if (maMH == listMH.danhSach[i].maMH) return true;   // neu giong nhau return true
	}
	return false;
}


// FORMAT_TEXT
void vietHoa(string& s) {
	int count = s.length();
	for (int i = 0; i < count; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
		}
	}
}
void chuanHoaChuoiTen(string& s) {

	int i = 0;
	// xoa dau
	while (s[i] == 32) {
		i++;
	}
	s.erase(0, i);
	// xoa giua
	i = 0;
	while (i < s.length()) {
		if (s[i - 1] == 32 && s[i] == 32) {
			s.erase(i, 1);
			--i;
		}
		++i;
	}
	// xoa cuoi
	i = s.length() - 1;
	if (s[i] == 32) {
		while (s[i] == 32) --i;
		int n = s.length() - 1;
		s.erase(n, i);
	}
}
void chuanHoaChuoiMa(string& s) {

	int i = 0;
	int n = s.length();
	// xoa het khoang trang
	for (int i = 0; i < n; i++) {
		if (s[i] == 32) {
			s.erase(i, 1);
			--i;
		}
	}
}
void nhapchuoi(int& tdX, int&tdY, string& temp,  bool& check, int max, int min, bool& checkEnter, int maxlength) {
	Cursortype();
	char s;
	if (_kbhit()) {
		s = _getch();
		if (s == Up) {
			if (tdY == min) tdY = max;
			else tdY = tdY - 2;
		}
		else if (s == Down) {
			if (tdY == max) tdY = min;
			else tdY = tdY + 2;
		}
		else if (s == Left || s == Right) {

		}
		else if (s >= 'A' && s <= 'z' || (s >= 40 && s <= 63) || s == Space) {
			if (temp.length() < maxlength) {
				if (s >= 'a' && s <= 'z') s = s - 32;
				temp.push_back(s);
				gotoxy(tdX, tdY); cout << s; ++tdX;
			}
		}
		else if (s == Backspace) {
			if (temp.length() > 0) {
				temp.erase(temp.length() - 1, 1);
				gotoxy(tdX, tdY); cout << "\b \b"; --tdX;
			}
		}
		else if (s == Esc) {
			check = 1;
		}
		else if (s == Enter) {
			checkEnter = 1;
		}
	}
}
void xuLiChuoi(int& tdX, int& tdY, string& temp, int X, int Y) {
	char s;
	if (_kbhit()) {
		s = _getch();
		if (s == Up) {
			--tdY;
		}
		else if (s == Down) {
			++tdY;
		}
		else if (s == Left || s == Right) {
			s = _getch();
		}
		else if (s >= 'A' && s <= 'z' || s >= '0' && s <= '9') {
			if (temp.length() < 15) {
				if (s >= 'a' && s <= 'z') s = s - 32;
				temp.push_back(s);
				gotoxy(tdX, tdY); cout << s; ++tdX;
			}
		}
		else if (s == Backspace) {
			if (temp.length() > 0) {
				temp.erase(temp.length() - 1, 1);
				gotoxy(tdX, tdY); cout << "\b \b"; --tdX;
			}
		}
	}
}


// NHAP LOP
void themLop() {
    
	if (listL.soLop == listL.maxSize) {
		gotoxy(110, 19); cout << "oooooooooooooooooooooooooooooooooooooooooooooooo";
		gotoxy(110, 20); cout << "O         KHONG THE THEM LOP DUOC NUA          0";
		gotoxy(110, 21); cout << "oooooooooooooooooooooooooooooooooooooooooooooooo";
		cin.ignore();
		return;
	}
	else {
		string tenLop, maLop;
		bool check2 = 0;
		bool check = 0;
		while (1) {
			bool check3 = 0;
			int i;
			int tdX = 100, tdX1 = 100;
			int tdY = 20;
			int Y = tdY;
			int X = tdX;
			nutEsc();
			gotoxy(tdX, Y - 6); cout << "     ooooooooooooooooooooooooooooooooooooooo";
			gotoxy(tdX, Y - 5); cout << "     O               THEM LOP              O";
			gotoxy(tdX, Y - 4); cout << "     ooooooooooooooooooooooooooooooooooooooo";
			box_dangnhap(tdX - 12, Y - 2, 70);
			gotoxy(tdX - 10, Y);     cout << "TEN LOP";
			gotoxy(tdX - 10, Y + 2); cout << "MA LOP";
			box_hcn(tdX - 11, Y + 3);
			gotoxy(tdX - 10, Y + 4); cout << "NHAN ENTER DE LUU";


			int max = Y + 2, min = Y;
			bool checkEnter = 0;
			tdX = tdX + 5;
			tdX1 = tdX1 + 5;
			gotoxy(tdX, Y);

			string tenLop1, maLop1;
			while (1) {

				if (check == 1) { //  thoat
					tenLop = maLop = "";
					for (int i = 0; i < Y + 5; i++) {
						gotoxy(tdX - 20, Y - 6 + i); cout << "                                                                                                 ";
					}
					return;
				}
				if (tdY == Y) {
					nhapchuoi(tdX, tdY, tenLop1, check, max, min, checkEnter, 20);
					gotoxy(tdX, tdY);
				}
				else if (tdY == Y + 2) {
					nhapchuoi(tdX1, tdY, maLop1, check, max, min, checkEnter, 20);
					gotoxy(tdX1, tdY);
				}
				
				if (checkEnter == 1) { // check ENTER
					Nocursortype();
					string temp[2] = {
					"TAO",
					"TRO LAI"
					};
					box_hcn(X - 1, Y + 5);
					box_hcn(X - 1, Y + 7);
					gotoxy(X, Y + 6); cout << temp[0];
					gotoxy(X, Y + 8); cout << temp[1];
					thanhsangmoi_hcn(X, Y + 6, temp[0]);
					tdY = Y + 6;
					int tdYcu = tdY;

					bool flag = 0;
					while (1) {
						char s = _getch();
						tdYcu = tdY;
						if (s == Up) {
							if (tdY == Y + 6) tdY = Y + 8;
							else tdY = tdY - 2;
						}
						else if (s == Esc) {
							checkEnter = 0;
							check2 = 1;
							ClearConsoleToColors(15, 16);
							break;
						}
						else if (s == Down) {
							if (tdY == Y + 8) tdY = Y + 6;
							else tdY = tdY + 2;
						}
						thanhsang_hcn(X, tdY, tdYcu, temp, Y + 6);
						if (s == Enter) {
							chuanHoaChuoiMa(maLop1);
							chuanHoaChuoiTen(tenLop1);
							if (tdY == Y + 6) {  // tao
								if ((tenLop1.length() > 5 && maLop1.length() > 5) && (checkTenLop(tenLop1) == false && checkMaLop(maLop1) == false)) {
									tenLop = tenLop1;
									maLop = maLop1;
									check2 = 1;
									break;
								}
								else {
									if ((checkTenLop(tenLop1) == true || checkMaLop(maLop1) == true)) {
										gotoxy(X - 2, Y + 11); cout << "TEN LOP hoac MA LOP da co";
									}
									if ((tenLop1.length() <= 5 || maLop1.length() <= 5)) {

										gotoxy(X - 2, Y + 12); cout << "Ki tu ban nhap phai co do dai tu 6-20 ";
									}
								}
							}
							gotoxy(X - 2, Y + 5); cout << "                                        ";
							gotoxy(X - 2, Y + 6); cout << "                                        ";
							gotoxy(X - 2, Y + 7); cout << "                                        ";
							gotoxy(X - 2, Y + 8); cout << "                                        ";
							gotoxy(X - 2, Y + 9); cout << "                                        ";
							gotoxy(X - 2, Y + 10); cout << "                                       ";
							tdY = Y;
							gotoxy(89, Y);     cout << "                                                 ";
							gotoxy(89, Y + 2); cout << "                                                 ";
							checkEnter = 0;
							check3 = 1;
							break;
						}
						gotoxy(X - 2, Y + 11); cout << "                                                          ";
						gotoxy(X - 2, Y + 12); cout << "                                                          ";
					}

				}

				if (check2 == 1 || check3 == 1) break;
			}
			if (check2 == 1 || check == 1) {
				system("cls");
				break;
			}
		}
		ClearConsoleToColors(15, 16);
		int n = listL.soLop;
		listL.Data[n].tenLop = tenLop;
		listL.Data[n].maLop = maLop;
		++listL.soLop;
		listL.Data[n].ListSV.pHead = listL.Data[n].ListSV.pTail = NULL;
	}


	ClearConsoleToColors(15, 16);
}
void sua_xoa_ThongTinLop(LOP& lop, int vitri) {
	
	//ClearConsoleToColors(15, 16);
	setBackgroundColor(16);
	string tenLop, maLop;
	bool check2 = 0;
	bool check = 0;
	while (1) {
		bool check3 = 0;
		int i;
		int tdX = 100, tdX1 = 100;
		int tdY = 20;
		int Y = tdY;
		int X = tdX;
		string tenLop1 = lop.tenLop, maLop1 = lop.maLop;
		tdX = tdX + 5;
		tdX1 = tdX1 + 5;

		nutEsc();
		gotoxy(tdX, Y - 6); cout << "oooooooooooooooooooooooooooooooooooooooooooooooo";
		gotoxy(tdX, Y - 5); cout << "O               SUA THONG TIN LOP              O";
		gotoxy(tdX, Y - 4); cout << "oooooooooooooooooooooooooooooooooooooooooooooooo";
		box_dangnhap(X - 12, Y - 2, 70);
		gotoxy(X - 10, Y);     cout << "TEN LOP";   gotoxy(tdX, Y); cout << tenLop1;
		gotoxy(X - 10, Y + 2); cout << "MA LOP";    gotoxy(tdX1, Y + 2); cout << maLop1;
		box_hcn(X - 11, Y + 3);
		gotoxy(X - 10, Y + 4); cout << "NHAN ENTER DE LUU";

		Cursortype();
		int max = Y + 2, min = Y;
		bool checkEnter = 0;
		tdX = tdX + tenLop1.length();
		tdX1 = tdX1 + maLop1.length();
		while (1) {

			if (check == 1) { // quay lai
				tenLop = maLop = "";
				system("cls");
				break;
			}
			if (tdY == Y) {
				nhapchuoi(tdX, tdY, tenLop1,check, max, min, checkEnter,20);
				gotoxy(tdX, tdY);
			}
			if (tdY == Y + 2) {
				nhapchuoi(tdX1, tdY, maLop1, check, max, min, checkEnter,20);
				gotoxy(tdX1, tdY);
			}
			if (check == 1) {
				system("cls");
				return;
			}
			if (checkEnter == 1) { // check ENTER
				Nocursortype();
				string temp[3] = {
				"SUA",
				"XOA",
				"TRO LAI"
				};
				box_hcn(X - 1, Y + 5);
				box_hcn(X - 1, Y + 7);
				box_hcn(X - 1, Y + 9);
				gotoxy(X, Y + 6); cout << temp[0];
				gotoxy(X, Y + 8); cout << temp[1];
				gotoxy(X, Y + 10); cout << temp[2];
				thanhsangmoi_hcn(X, Y + 6, temp[0]);
				tdY = Y + 6;
				int tdYcu = tdY;

				bool flag = 0;
				while (1) {
					char s = _getch();
					tdYcu = tdY;
					if (s == Left || s == Right) s = _getch();
					if (s == Up) {
						if (tdY == Y + 6) tdY = Y + 10;
						else tdY = tdY - 2;
					}
					else if (s == Esc) {
						checkEnter = 0;
						check2 = 1;
						system("cls");
						break;
					}
					else if (s == Down) {
						if (tdY == Y + 10) tdY = Y + 6;
						else tdY = tdY + 2;
					}
					thanhsang_hcn(X, tdY, tdYcu, temp, Y + 6);
					if (s == Enter) {

						chuanHoaChuoiMa(maLop1);
						chuanHoaChuoiTen(tenLop1);
						if (tdY == Y + 6) {  // sua thong tin lop

							if ((tenLop1.length() <= 3 || maLop1.length() <= 3)) {

								gotoxy(X - 2, Y + 12); cout << "Ki tu ban nhap phai co do dai tu 3-20 ";
							}

							else {

								string temp_malop = listL.Data[vitri].maLop;
								string temp_tenlop = listL.Data[vitri].tenLop;

								listL.Data[vitri].tenLop = tenLop1;
								listL.Data[vitri].maLop = maLop1;

								bool checktrung = 0;
								for (int i = 0; i < listL.soLop; i++) {
									if (vitri == i) continue;
									if (listL.Data[vitri].tenLop == listL.Data[i].tenLop || (listL.Data[vitri].maLop == listL.Data[i].maLop)) {
										gotoxy(X - 2, Y + 13); cout << "Ma Lop hoac Ten Lop bi trung";
										checktrung = 1;
										break;
									}
								}
								if (checktrung == 0) {
									gotoxy(X - 2, Y + 13); cout << "SUA THANH CONG";

								}
								else {
									listL.Data[vitri].maLop = temp_malop;
									listL.Data[vitri].tenLop = temp_tenlop;
								}
								Sleep(1000);
								check2 = 1;
								break;
							}
						}

						else if (tdY == Y + 8) { // xoa lop
							if (lop.ListSV.pHead == NULL) {
								gotoxy(X - 2, Y + 12); cout << "XOA THANH CONG ";
								for (int i = 0; i < listL.soLop; i++) {
									if (lop.maLop == listL.Data[i].maLop) {
										for (int j = i; j < listL.soLop; j++) {
											listL.Data[j] = listL.Data[j + 1];
										}
										--listL.soLop;
										break;
									}
								}
								check2 = 1;
								break;
							}
							else {
								gotoxy(X - 2, Y + 12); cout << "LOP CO SINH VIEN KHONG THE XOA ";
								Sleep(1000);
							}
						}

						for (int i = 0; i < 15; i++) {
							gotoxy(X - 2, Y + 5 + i); cout << "                                                  ";
						}

						tdY = Y;
						checkEnter = 0;
						check3 = 1;
						gotoxy(89, Y);     cout << "                                            ";
						gotoxy(89, Y + 2); cout << "                                            ";
						break;
					}
					gotoxy(X - 2, Y + 12); cout << "                                                          ";
					gotoxy(X - 2, Y + 13); cout << "                                                          ";
					gotoxy(X - 2, Y + 14); cout << "                                                          ";
					gotoxy(X - 2, Y + 15); cout << "                                                          ";
	

				}
			}

			if (check2 == 1 || check3 == 1) break;
		}
		if (check2 == 1 || check == 1) {
			system("cls");
			break;
		}
	}
	ClearConsoleToColors(15, 16);
}
void suaThongTinLop_dohoa() {
	//system("cls");
	ClearConsoleToColors(15, 16);
	bool check = 0;
	while (1) {


		const int x = 20, y = 10;
		bool check = 0;
		nutEsc();
		box_hcn1(x + 34, y - 3, 40);
		gotoxy(x + 35, y - 2); cout << "NHAN ENTER DE SUA THONG TIN LOP";
		box_hcn(x - 1, y - 3); 
		gotoxy(x, y - 2); cout << "NHAN TAB DE THEM LOP MOI";
		gotoxy(x, y); cout << "SO LUONG LOP: ";
		gotoxy(x + 15, y); cout << listL.soLop;
		gotoxy(x, y + 2); cout << "TEN LOP";
		gotoxy(x + 40, y + 2); cout << "MA LOP";
		int max = 5;
		int min = max + y;
		int tdY = min;
		int tdX = x;
		int tdYcu = tdY;

		for (int i = 0; i < listL.soLop; i++) {
			gotoxy(x, y + max); cout << listL.Data[i].tenLop;
			gotoxy(x + 40, y + max); cout << listL.Data[i].maLop;
			max = max + 2;
		}

		string khoangtrang = "                   ";
		string lop[2];
		thanhsangMoi(x, tdY, listL.Data[0].tenLop, listL.Data[0].maLop);
		int flag = 0;
		while (1) {
			Nocursortype();
			char s;
			if (_kbhit()) {
				s = _getch();

				if (s == tab) {
					setBackgroundColor(16);
					themLop();
					thanhsangCu(x, tdY, listL.Data[(tdY - min) / 2].tenLop, listL.Data[(tdY - min) / 2].maLop);
					break;
				}

				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max + y - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2 + y) tdY = min;
					else tdY = tdY + 2;
				}
				flag = 1;
				if (s == Esc) {
					system("cls");
					ClearConsoleToColors(15, 16);
					check = 1;
					return;
				}
				if (s == Enter) {
					sua_xoa_ThongTinLop(listL.Data[(tdY - min) / 2], (tdY - min) / 2);
					if (tdY >= min) {
						tdYcu = tdYcu - 2;
					}
					/*nutEsc();
					Nocursortype();
					gotoxy(x, y); cout << "SO LUONG LOP: ";
					gotoxy(x + 15, y); cout << listL.soLop;
					gotoxy(x, y + 2); cout << "TEN LOP";
					gotoxy(x + 40, y + 2); cout << "MA LOP";
					max = 5;
					for (int i = 0; i < listL.soLop; i++) {
						gotoxy(x, y + max); cout << listL.Data[i].tenLop;
						gotoxy(x + 40, y + max); cout << listL.Data[i].maLop;
						max = max + 2;
					}
					tdY = min;*/
					break;
				}
				thanhsang_lop(tdX, tdY, tdYcu, min);
			}
		}
		
		if (check == 1) {
			ClearConsoleToColors(15, 16);
			break;
		}
	}
	
}
void nhapLop() {
	suaThongTinLop_dohoa();
}


// IN DANH SACH LOP
void inThongTinSinhVien(SINHVIEN sv, int tdX, int& tdY) {

	gotoxy(tdX + 5, tdY + 3); vietHoa(sv.maSV); cout << sv.maSV;
	gotoxy(tdX + 25, tdY + 3); vietHoa(sv.ho); cout << sv.ho;
	gotoxy(tdX + 45, tdY + 3); vietHoa(sv.ten); cout << sv.ten;
	gotoxy(tdX + 65, tdY + 3); vietHoa(sv.gioiTinh); cout << sv.gioiTinh;
}	
void inDanhSachSinhVien(LOP lop) {
	
	int z = 2;
	int trang = 1;
	int soLuong = 15;
	listSINHVIENTHEOLOP* listSVTL = new listSINHVIENTHEOLOP;

	int i = 0;
	if (lop.ListSV.pHead == NULL) listSVTL->soSV = 0;
	else {
		for (nodeSINHVIEN* k = lop.ListSV.pHead; k != NULL; k = k->pNext) {
			listSVTL->Data[i] = k->data;
			++i; ++listSVTL->soSV;
		}
	}
	int tongsotrang = 1;
	if (listSVTL->soSV != 0) {
		if (listSVTL->soSV % soLuong == 0) {
			tongsotrang = listSVTL->soSV / soLuong;
		}
		else tongsotrang = listSVTL->soSV / soLuong + 1;
	}
	ClearConsoleToColors(15, 16);
	int tdX = 70, tdY = 20, tdYcu;
	int min = 14; tdYcu = tdY;
	const int Y = tdY;
	//thanhsang_sinhvien(tdX, tdY, tdY, min);
	bool check = 0;
	while (true) {
		system("cls");
		tdY = 20;
		nutEsc();
		gotoxy(tdX + 5, Y - 8); cout << "TEN LOP: " << lop.tenLop;
		gotoxy(tdX + 5, Y - 7); cout << "MA LOP : " << lop.maLop;
		gotoxy(tdX + 5, Y - 6); cout << "SO SINH VIEN: " << listSVTL->soSV;
		gotoxy(tdX + 5, Y - 5); cout << "TRANG THU " << trang << "/" << tongsotrang;
		
		for (i = (trang - 1) * soLuong; i < trang * soLuong && i < listSVTL->soSV; i++) {
			gotoxy(tdX + 5, Y - 1); cout << "Ma Sinh Vien";
			gotoxy(tdX + 25, Y - 1); cout << "Ho va Ten lot";
			gotoxy(tdX + 45, Y - 1); cout << "Ten Chinh";
			gotoxy(tdX + 65, Y - 1); cout << "Gioi Tinh";
			inThongTinSinhVien(listSVTL->Data[i], tdX, tdY);
			tdY = tdY + 2;
		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{
			case 27:
				system("cls");
				return;

			case 72:
				// Len
				if (trang >= 1) {
					trang--;
					flag = 1;
				}
				if (trang == 0) trang = tongsotrang;
				break;

			case 80:
				// Xuong
				if (trang <= tongsotrang) {
					trang++;
					flag = 1;
				}
				if (trang == tongsotrang + 1) trang = 1;
				break;
			}

			if (flag) {
				check = 1;
				break;
			}
		}
	
	}
}
void inDanhSachLop(){
	system("cls");
	//ClearConsoleToColors(15, 16);
	const int x = 90, y = 5;
	bool check = 0;
	nutEsc();
	gotoxy(x, y); cout << "SO LUONG LOP: ";
	gotoxy(x + 15, y); cout << listL.soLop;
	gotoxy(x, y + 2); cout << "TEN LOP";
	gotoxy(x + 30, y + 2); cout << "MA LOP";
	int max = 5;
	int min = max + y;
	int tdY = min;
	int tdX = x;
	int tdYcu = tdY;

	for (int i = 0; i < listL.soLop; i++) {
		gotoxy(x, y + max); cout << listL.Data[i].tenLop;
		gotoxy(x + 30, y + max); cout << listL.Data[i].maLop;
		max = max + 2;
	}

	string khoangtrang = "                   ";
	string lop[2];
	thanhsangMoi(x, tdY, listL.Data[0].tenLop, listL.Data[0].maLop);
	int flag = 0;
	while (1) {

		char s;
		if (_kbhit()) {
			s = _getch();
			tdYcu = tdY;
			if (s == Up) {
				if (tdY == min) tdY = max + y - 2;
				else tdY = tdY - 2;
			}
			if (s == Down) {
				if (tdY == max - 2 + y) tdY = min;
				else tdY = tdY + 2;
			}
			flag = 1;
			if (s == Esc) {
				system("cls");
				ClearConsoleToColors(15, 16);
				return;
			}
			if (s == Enter) {
				inDanhSachSinhVien(listL.Data[(tdY - min) / 2]);
				if (tdY >= min) {
					tdYcu = tdYcu - 2;
				}
				nutEsc();
				gotoxy(x, y); cout << "SO LUONG LOP: ";
				gotoxy(x + 15, y); cout << listL.soLop;
				gotoxy(x, y + 2); cout << "TEN LOP";
				gotoxy(x + 30, y + 2); cout << "MA LOP";
				max = 5;
				for (int i = 0; i < listL.soLop; i++) {
					gotoxy(x, y + max); cout << listL.Data[i].tenLop;
					gotoxy(x + 30, y + max); cout << listL.Data[i].maLop;
					max = max + 2;
				}
			}
			thanhsang_lop(tdX, tdY, tdYcu, min);
		}
	}
}


// NHAP SINH VIEN
void THEMSINHVIEN(listSINHVIENTHEOLOP*& listSVTL, int stt);
void xoaDiemThi(listDIEMTHI& temp, string maMH) {
	if (temp.pHead == NULL) {
		return;
	}
	else{
		if (temp.pHead->data.maMH == maMH) {
			nodeDIEMTHI* k = new nodeDIEMTHI;
			temp.pHead = k;
			temp.pHead = temp.pHead->pNext;
			delete k;
		}
		else if (temp.pTail->data.maMH == maMH) {
			for (nodeDIEMTHI* k = temp.pHead; k != NULL; k = k->pNext) {
				if (k->pNext == temp.pTail) {
					delete temp.pTail;
					k->pNext = NULL;
					temp.pTail = k;
				}
			}
		}
		else {
			nodeDIEMTHI* g = new nodeDIEMTHI;
			for (nodeDIEMTHI* k = temp.pHead; k != NULL; k = k->pNext) {
				if (k->data.maMH == maMH) {
					g->pNext = k->pNext;
					delete k;
					return;
				}
				g = k;
			}
		}
	}
}
void xoaDau(listSINHVIEN& temp)
{
	nodeSINHVIEN* k = new nodeSINHVIEN;
	k = temp.pHead;
	temp.pHead = temp.pHead->pNext;
	delete k;	
}
void xoaCuoi(listSINHVIEN& temp)
{
	for (nodeSINHVIEN* k = temp.pHead; k != NULL; k = k->pNext) {
		if (k->pNext == temp.pTail) {
			delete temp.pTail;
			k->pNext = NULL;
			temp.pTail = k;
			return;
		}
	}
}
void xoaBatKy(listSINHVIEN& temp, SINHVIEN data)
{
	if (temp.pHead == NULL) {
		return;
	}
	else
	{
		if (data.maSV == temp.pTail->data.maSV) {
			xoaCuoi(temp);
			return;
		}
		else if (data.maSV == temp.pHead->data.maSV) {
			xoaDau(temp);
			return;
		}
		else
		{
			nodeSINHVIEN* g = new nodeSINHVIEN;
			for (nodeSINHVIEN* k = temp.pHead; k != NULL; k = k->pNext) {
				if (k->data.maSV == data.maSV) {
					g->pNext = k->pNext;
					delete k;
					return;
				}
				g = k;
			}
		}
	}
}
void inThongTin_1_sinhvien(SINHVIEN sv, int X, int Y) {
	int tdX = X - 15;
	int tdY = Y;
	int n = 5;
	gotoxy(tdX + n, tdY - 4); cout << "oooooooooooooooooooooooooooooooooooooo";
	gotoxy(tdX + n, tdY - 3); cout << "o        THONG TIN SINH VIEN         o";
	gotoxy(tdX + n, tdY - 2); cout << "oooooooooooooooooooooooooooooooooooooo";
	box_dangnhap(tdX, tdY, 70);
	box_dangnhap(tdX, tdY + 4, 70);
	box_dangnhap(tdX, tdY + 6, 70); 
	box_hcn(tdX + 1, tdY + 11);

	n = 17;
	for (int i = tdY + 2; i < tdY + 10; i = i + 2) {
		gotoxy(tdX + n, i); cout << "                                               ";
	}
	gotoxy(tdX + 1, tdY + 2); cout << "Ma sinh vien"; gotoxy(tdX + n, tdY + 2); cout << sv.maSV;
	gotoxy(tdX + 1, tdY + 4); cout << "Ho va ten lot"; gotoxy(tdX + n, tdY + 4); cout << sv.ho;
	gotoxy(tdX + 1, tdY + 6); cout << "Ten"; gotoxy(tdX + n, tdY + 6); cout << sv.ten;
	gotoxy(tdX + 1, tdY + 8); cout << "Gioi tinh"; gotoxy(tdX + n , tdY + 8); cout << sv.gioiTinh;
	gotoxy(tdX + 1, tdY + 10); cout << "Mat khau"; gotoxy(tdX + n, tdY + 10); cout << sv.password; // 
	gotoxy(tdX + 1, tdY + 12); cout << "Nhan Enter de luu";
}
void xoa_inThongTin_1_sinhvien(int X, int Y) {
	int tdX = X - 15;
	int tdY = Y;
	int n = 5;

	for (int i = tdY - 5; i < tdY + 20; i++) {
		gotoxy(tdX + n, i); cout << "                                                                ";
	}
}
void gioitinh(string& gioitinh, int& tdY, int tdX, bool& checkEnter, bool& check) {
	Nocursortype();
	char s;
	tdX = tdX - 2;
	if (_kbhit()) {
		s = _getch();
		if (s == Up) tdY = tdY - 2;
		else if (s == Down) tdY = tdY + 2;

		if (s == Left) { 
			gioitinh = "NAM";
		
			gotoxy(tdX + 3,tdY); cout << " ";
			gotoxy(tdX - 1,tdY); cout << (char)219;
			gotoxy(tdX , tdY); cout << "   ";
			gotoxy(tdX , tdY); cout << gioitinh;
			
		}
		if (s == Right) {
			gioitinh = "NU";
		
			gotoxy(tdX - 1, tdY); cout << " ";
			gotoxy(tdX + 3, tdY); cout << (char)219;
			gotoxy(tdX , tdY); cout << "   ";
			gotoxy(tdX , tdY); cout << gioitinh;
			
		}
		if (s == Enter) {
			checkEnter = 1;
		}
		if (s == Esc) {
			check = 1;
		}
	}
}
void suaThongTin_1_sinhVien(SINHVIEN& sv, listSINHVIENTHEOLOP*& listSVTL, int sttLop) {

	setBackgroundColor(16);
	
	bool check2 = 0;
	bool check = 0;
	string masv1 = sv.maSV, ho1 = sv.ho, ten1 = sv.ten, gioitinh1 = sv.gioiTinh, mk1 = sv.password;
	
	while (1) {
		Cursortype();

		bool check3 = 0;

		nutEsc();
		
		bool checkEnter = 0;
		int i;
		int tdX = 150;
		int tdXmasv, tdXho, tdXten, tdXgioitinh, tdXmk;
		tdXmasv = tdXho = tdXten = tdXgioitinh = tdXmk = tdX + 2;
		int tdY = 25;
		const int Y = tdY;
		const int X = tdX;
		tdXmasv = tdXmasv + masv1.length();
		tdXho = tdXho + ho1.length();
		tdXten += ten1.length();
		tdXgioitinh += gioitinh1.length();
		tdXmk += mk1.length();
		inThongTin_1_sinhvien(sv, X, Y);
		tdY = Y + 2;
		const int max = Y + 10, min = Y + 2;
		gotoxy(tdXmasv, tdY);

		while (1) {

			if (check == 1) { // quay lai
				masv1 = ho1 = ten1 = gioitinh1 = mk1 = "";
				for (int i = Y - 6; i < Y + 22; i++) {
					gotoxy(X - 20, i); cout << "                                                                               ";
				}
				check = 1;
				check2 = 1;
				return;
			}
			if (tdY == Y + 2) {

				nhapchuoi(tdXmasv, tdY, masv1, check, max, min, checkEnter,15);
				gotoxy(tdXmasv, tdY);
			}
			if (tdY == Y + 4) {
				nhapchuoi(tdXho, tdY, ho1, check, max, min, checkEnter,15);
				gotoxy(tdXho, tdY);
			}
			if (tdY == Y + 6) {
				nhapchuoi(tdXten, tdY, ten1, check, max, min, checkEnter,15);
				gotoxy(tdXten, tdY);
			}
			if (tdY == Y + 8) {
				
				gioitinh(gioitinh1, tdY, tdXgioitinh,checkEnter, check);
				
			}
			if (tdY == Y + 10) {
				nhapchuoi(tdXmk, tdY, mk1, check, max, min, checkEnter,15);
				gotoxy(tdXmk, tdY);
			}
			
			if (checkEnter == 1) { // check ENTER
				Nocursortype();
				string temp[3] = {
				"SUA",
				"XOA",
				"TRO LAI"
				};
				
				int Y1 = Y + 7;
				

				box_hcn(X + 20, Y1 + 5);
				box_hcn(X + 20, Y1 + 7);
				box_hcn(X + 20, Y1 + 9);

				gotoxy(X + 21, Y1 + 6); cout << temp[0];
				gotoxy(X + 21, Y1 + 8); cout << temp[1];
				gotoxy(X + 21, Y1 + 10); cout << temp[2];

				thanhsangmoi_hcn(X + 21, Y1 + 6, temp[0]);

				tdY = Y1 + 6;
				int tdYcu = tdY;

				bool flag = 0;
				while (1) {
					char s = _getch();
					tdYcu = tdY;
					if (s == Up) {
						if (tdY == Y1 + 6) tdY = Y1 + 10;
						else tdY = tdY - 2;
					}
					
					else if (s == Down) {
						if (tdY == Y1 + 10) tdY = Y1 + 6;
						else tdY = tdY + 2;
					}

					thanhsang_hcn(X + 21, tdY, tdYcu, temp, Y1 + 6);

					if (s == Enter) {

						chuanHoaChuoiMa(masv1);
						chuanHoaChuoiTen(ho1);
						chuanHoaChuoiMa(ten1);
						chuanHoaChuoiMa(mk1);

						if (tdY == Y1 + 6) {  // sua thong tin sinh vien
							if (masv1.length() >= 5 && ho1.length() >= 1 && mk1.length() > 5 && ten1.length() >= 1) {
								
								if (checkMaSV(masv1) == true || masv1 == sv.maSV) { // khong trung ma
									sv.maSV = masv1;
									sv.ho = ho1;
									sv.ten = ten1;
									sv.gioiTinh = gioitinh1;
									sv.password = mk1;

									

									gotoxy(X - 2, Y1+ 14); cout << "SUA THONG TIN SINH VIEN THANH CONG";
									Sleep(1000);
									
									check = 1;
									check2 = 1;
									check3 = 1;
									for (int i = 10; i <55; i++) {
										gotoxy(120, i); cout << "                                                                                                                 ";
									}
									break;
								}
							}
							else {  

								if (masv1.length() < 6 || ho1.length() < 1 || ten1.length() < 1 || mk1.length() < 6) {

									masv1 = sv.maSV, ho1 = sv.ho, ten1 = sv.ten, gioitinh1 = sv.gioiTinh, mk1 = sv.password;
								}
							}

						}

						// xoa sinh vien
						if (tdY == Y1 + 8) {
							
							if (listSVTL->soSV > 0) {
								
								sv.maSV = masv1;
								int i;
								for (i = 0; i < listSVTL->soSV; i++) {

									if (sv.maSV == listSVTL->Data[i].maSV && listSVTL->Data[i].listDT.pHead == NULL) {
										xoaBatKy(listL.Data[sttLop].ListSV, listSVTL->Data[i]);
										int j = i;
										for (j; j < listSVTL->soSV; j++) {
											listSVTL->Data[j] = listSVTL->Data[j + 1];
										}
										--listSVTL->soSV;

										// xoa trong danh sach lien ket don
										xoaBatKy(listL.Data[sttLop].ListSV, sv);
										
										
										gotoxy(X - 2, Y1 + 14); cout << "XOA THONG TIN SINH VIEN THANH CONG";
										Sleep(500);
										check = 1;
										check2 = 1;
										check3 = 1;
										for (int i = 10; i < 55; i++) {
											gotoxy(120, i); cout << "                                                                                                                 ";
										}
										
										break;
									}
									if(sv.maSV == listSVTL->Data[i].maSV && listSVTL->Data[i].listDT.pHead != NULL){
										gotoxy(X - 2, Y1 + 14); cout << "SINH VIEN DA THI";
										Sleep(500);
										gotoxy(X - 2, Y1 + 14); cout << "                       ";
										break;
									}
								}
							}
					    }
						// tro lai
					
						for (int i = Y1 + 5; i <= Y1 + 11; i++) {
							gotoxy(X + 19, i); cout << "                                               ";
						}
						

						// sua, xoa , tro lai
						/*int i = 0;
						for (i = Y + 5; i <= Y1 + 14; i++) {
							gotoxy(X, i); cout << "                                                                        ";
						}*/

						tdY = Y;
						gotoxy(tdXmasv, Y);
						checkEnter = 0;
						check3 = 1;
						
						masv1 = sv.maSV, ho1 = sv.ho, ten1 = sv.ten, gioitinh1 = sv.gioiTinh, mk1 = sv.password;
						break;
					}
				}
			}

			if (check2 == 1 || check3 == 1) {
				//check = 1;
				break;
			}
		}

		if (check == 1) {
			break;
		}
	}
}
void timSinhVien(LOP& lop, int sttLop) {
	ClearConsoleToColors(15, 16);
	
	listSINHVIENTHEOLOP* listSVTL = new listSINHVIENTHEOLOP; // chuyen qua mang 

	int tdX = 40, tdY = 20, tdYcu;
	int z = 2;
	int trang = 1;
	int soLuong = 15;
	int min = 14; tdYcu = tdY;
	const int Y = tdY;

	int i = 0;

	for (nodeSINHVIEN* k = lop.ListSV.pHead; k != NULL; k = k->pNext) {
		listSVTL->Data[i] = k->data;
		++i; ++listSVTL->soSV;
	}

	

	bool check = 0;
	while (true) {
		Nocursortype();
		gotoxy(tdX + 15, 15); cout << "                  ";
		for (i = 23; i < 54; i = i + 2) {
			gotoxy(tdX, i); cout << "                                                                                     ";
		}
		tdY = 20;
		nutEsc();


		// hop tim sinh vien
		box_hcn(tdX + 4, Y - 15);
		gotoxy(tdX + 5, Y - 14); cout << "nhan TAB de TIM SINH VIEN";
	
		box_hcn(tdX + 4, Y - 12);
		gotoxy(tdX + 5, Y - 11); cout << "nhan Enter de THEM SINH VIEN";


		gotoxy(tdX + 47, Y - 9); cout << "^";
		gotoxy(tdX + 40, Y - 8); cout << "UP:    |";
		gotoxy(tdX + 40, Y - 6); cout << "DOWN:  |";
		gotoxy(tdX + 47, Y - 5); cout << "v";


		int tongsotrang = 1;

		if (listSVTL->soSV % soLuong == 0) {
			tongsotrang = listSVTL->soSV / soLuong;
		}
		else tongsotrang = listSVTL->soSV / soLuong + 1;

		gotoxy(tdX + 5, Y - 8); cout << "TEN LOP: " << lop.tenLop;
		gotoxy(tdX + 5, Y - 7); cout << "MA LOP : " << lop.maLop;
		gotoxy(tdX + 5, Y - 6); cout << "SO SINH VIEN: " << listSVTL->soSV;
		gotoxy(tdX + 5, Y - 5); cout << "TRANG THU " << trang << "/" << tongsotrang;

		for (i = (trang - 1) * soLuong; i < trang * soLuong && i < listSVTL->soSV; i++) {

			gotoxy(tdX + 5, Y - 1); cout << "Ma Sinh Vien";
			gotoxy(tdX + 25, Y - 1); cout << "Ho va Ten lot";
			gotoxy(tdX + 45, Y - 1); cout << "Ten Chinh";
			gotoxy(tdX + 65, Y - 1); cout << "Gioi Tinh";
			inThongTinSinhVien(listSVTL->Data[i], tdX, tdY);

			tdY = tdY + 2;

		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{

			case Enter:

				THEMSINHVIEN(listSVTL, sttLop);
				flag = 1;
				break;

			case Esc:

				system("cls");
				check = 1;
				return;

			case Up:
				// Len
				if (trang >= 1) {

					trang--;
					flag = 1;
				}
				if (trang == 0) trang = tongsotrang;
				break;

			case Down:
				// Xuong
				if (trang <= tongsotrang) {

					trang++;
					flag = 1;
				}
				if (trang == tongsotrang + 1) trang = 1;
				break;

			case tab:

				Cursortype();

				// tim sinh vien

				string temp;
				string maLop;
				int tdX = 40;
				int Y = 20;
				gotoxy(tdX + 5, Y - 14); cout << "                             ";
				gotoxy(tdX + 5, Y - 14);
				while (1) {
					char s;
					if (_kbhit()) {
						s = _getch();
						if (s == Left || s == Right || s == Up || s == Down) s = _getch();
						if (s >= 'A' && s <= 'z' || s >= '0' && s <= '9') {
							if (temp.length() < 15) {
								if (s >= 'a' && s <= 'z') s = s - 32;
								temp.push_back(s);
								gotoxy(tdX + 5, Y - 14); cout << s; ++tdX;
							}
						}
						else if (s == Backspace) {
							if (temp.length() > 0) {
								temp.erase(temp.length() - 1, 1);
								gotoxy(tdX + 5, Y - 14); cout << "\b \b"; --tdX;
							}
						}
						else if (s == Enter) {
							int i;
							for (i = 0; i < listSVTL->soSV; i++) {
								if (temp == listSVTL->Data[i].maSV) {
									suaThongTin_1_sinhVien(listSVTL->Data[i], listSVTL, sttLop);
									i = 0;
									for (nodeSINHVIEN* k = lop.ListSV.pHead; k != NULL; k = k->pNext) {
										k->data = listSVTL->Data[i];
										++i;
									}
									Cursortype();
									gotoxy(tdX + 5, Y - 14);
									flag = 1;
									break;
								}
								
							}
							break;
							
						}
						else if (s == Esc) {
							gotoxy(tdX + 5, Y - 14);
							//check = 1;
							flag = 1;
							break;
						}
					}
				}

			} // switch

			if (flag) {
				//check = 1;
				break;
			}
		}
		if (check == 1) {
			break;
		}
	}
	ClearConsoleToColors(15, 16);
	delete listSVTL;


}
void inDanhSachLop_suaSV_xoaSV() {
	system("cls");
	//ClearConsoleToColors(15, 16);
	
	bool check = 0;
	while (1) {
		const int x = 90, y = 5;
		int max = 5;
		int min = max + y;
		int tdY = min;
		int tdX = x;
		int tdYcu = tdY;

		nutEsc();
		khungmonhoc(x - 20, y - 2, y + listL.soLop * 2 + 4, 100);
		gotoxy(x, y); cout << "SO LUONG LOP: ";
		gotoxy(x + 15, y); cout << listL.soLop;
		gotoxy(x, y + 2); cout << "TEN LOP";
		gotoxy(x + 40, y + 2); cout << "MA LOP";
		

		for (int i = 0; i < listL.soLop; i++) {
			gotoxy(x, y + max); cout << listL.Data[i].tenLop;
			gotoxy(x + 40, y + max); cout << listL.Data[i].maLop;
			max = max + 2;
		}

		string khoangtrang = "                   ";
		string lop[2];
		thanhsangMoi(x, tdY, listL.Data[0].tenLop, listL.Data[0].maLop);
		int flag = 0;
		while (1) {

			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
				
					if (tdY == min) tdY = max + y - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
				
					if (tdY == max - 2 + y) tdY = min;
					else tdY = tdY + 2;
				}
				
				if (s == Esc) {
					flag = 1;
					check = 1;
					system("cls");
					ClearConsoleToColors(15, 16);
					return;
				}
				if (s == Enter) {
				
					int sttLop = (tdY - min) / 2;
					timSinhVien(listL.Data[sttLop], sttLop);

					if (tdY >= min) {
						tdYcu = tdYcu - 2;
					}
					flag = 1;
				}
				thanhsang_lop(tdX, tdY, tdYcu, min);
			}
			if (flag == 1) {
				system("cls");
				break;
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
	ClearConsoleToColors(15, 16);
}
void THEMSINHVIEN(listSINHVIENTHEOLOP*& listSVTL, int stt) {

	int i = 0;
	LOP lop = listL.Data[stt];
	for (nodeSINHVIEN* k = lop.ListSV.pHead; k != NULL; k = k->pNext) {
		++i;
	}
	if (i >= 10000) return;

	
	SINHVIEN sv;

	setBackgroundColor(16);

	bool check2 = 0;
	bool check = 0;

	while (1) {
		bool check3 = 0;
		int i;
		int tdX = 150;
		int tdXmasv, tdXho, tdXten, tdXgioitinh, tdXmk;
		tdXmasv = tdXho = tdXten = tdXgioitinh = tdXmk = tdX + 2;
		int tdY = 25;
		const int Y = tdY;
		const int X = tdX;

		nutEsc();
		inThongTin_1_sinhvien(sv, X, Y);

		Cursortype();
		int max = Y + 10, min = Y + 2;
		bool checkEnter = 0;

		tdXmasv = tdXmasv + sv.maSV.length();
		tdXho = tdXho + sv.ho.length();
		tdXten += sv.ten.length();
		tdXgioitinh += sv.gioiTinh.length();
		tdXmk += sv.password.length();

		tdY = Y + 2;
		gotoxy(tdXmasv, tdY);

		while (1) {

			if (check == 1) { // quay lai
				
				system("cls");
				break;
			}
			if (tdY == Y + 2) {

				nhapchuoi(tdXmasv, tdY, sv.maSV, check, max, min, checkEnter, 15);
				gotoxy(tdXmasv, tdY);
			}
			if (tdY == Y + 4) {
				nhapchuoi(tdXho, tdY, sv.ho, check, max, min, checkEnter, 20);
				gotoxy(tdXho, tdY);
			}
			if (tdY == Y + 6) {
				nhapchuoi(tdXten, tdY, sv.ten, check, max, min, checkEnter, 15);
				gotoxy(tdXten, tdY);
			}
			if (tdY == Y + 8) {

				gioitinh(sv.gioiTinh, tdY, tdX + 4, checkEnter, check);
				
			}
			if (tdY == Y + 10) {
				nhapchuoi(tdXmk, tdY, sv.password, check, max, min, checkEnter, 15);
				gotoxy(tdXmk, tdY);
			}

			if (checkEnter == 1) { // check ENTER
				Nocursortype();
				string temp[2] = {
				"THEM SINH VIEN",
				"TRO LAI"
				};
				int Y1 = Y;
				Y1 = Y1 + 7;

				box_hcn(X + 20, Y1 + 5);
				box_hcn(X + 20, Y1 + 7);

				gotoxy(X + 21, Y1 + 6); cout << temp[0];
				gotoxy(X + 21, Y1 + 8); cout << temp[1];

				thanhsangmoi_hcn(X + 21, Y1 + 6, temp[0]);

				tdY = Y1 + 6;
				int tdYcu = tdY;

				bool flag = 0;
				while (1) {
					char s = _getch();
					tdYcu = tdY;
					if (s == Up) {
						if (tdY == Y1 + 6) tdY = Y1 + 8;
						else tdY = tdY - 2;
					}
					else if (s == Esc) {
						checkEnter = 0;
						check2 = 1;
						break;
					}
					else if (s == Down) {
						if (tdY == Y1 + 8) tdY = Y1 + 6;
						else tdY = tdY + 2;
					}

					thanhsang_hcn(X + 21, tdY, tdYcu, temp, Y1 + 6);

					if (s == Enter) {

						chuanHoaChuoiMa(sv.maSV);
						chuanHoaChuoiTen(sv.ho);
						chuanHoaChuoiMa(sv.ten);
						chuanHoaChuoiMa(sv.password);

						if (tdY == Y1 + 6) {  // sua thong tin sinh vien
							if (sv.maSV.length() > 5 && sv.ho.length() >= 1 && sv.password.length() > 5 && sv.ten.length() >= 1) {

								if (checkMaSV(sv.maSV) == true) { // khong trung ma

									nodeSINHVIEN* temp = new nodeSINHVIEN;
									temp->data = sv;
									temp->pNext = NULL;
									temp->data.listDT.pHead = NULL;
									lop.ListSV.pTail->pNext = temp;
									lop.ListSV.pTail = temp;

									listL.Data[stt] = lop;
									listSVTL->Data[listSVTL->soSV] = sv;
									listSVTL->soSV++;

									check2 = 1;
									gotoxy(X - 2, Y1 + 14); cout << "THEM SINH VIEN THANH CONG";
									check2 = 1;
									check = 1;
									Sleep(1000);
									system("cls");
									break;
								}
								else {

									gotoxy(X - 2, Y1 + 13); cout << "Ma sinh vien da duoc su dung";
								}

							}
							else {

								if (sv.maSV.length() < 6 || sv.ho.length() < 1 || sv.ten.length() < 1 || sv.password.length() < 5) {

									gotoxy(X - 2, Y1 + 15); cout << "Ki tu ban nhap phai co do dai tu 6 ki tu";
								}

							}
						}

						
						xoa_inThongTin_1_sinhvien(tdX, Y);
						// tro lai
					
						


						// sua, xoa , tro lai
						int i = 0;
						for (i = Y + 5; i <= Y1+ 14; i++) {
							gotoxy(X, i); cout << "                                                                        ";
						}
						//tdY = Y;
						checkEnter = 0;
						check3 = 1;

						break;
					}
				
				}
			}

			if (check2 == 1 || check3 == 1) break;
		}
		if (check2 == 1 || check == 1) {
			break;
		}
	}
	
	
		//ClearConsoleToColors(15, 16);

	if(i>=10000){
	gotoxy(70, 20); cout << "==================================================";
	gotoxy(70, 21); cout << "==========LOP DA DAY, KHONG THE THEM NUA==========";
	gotoxy(70, 22); cout << "==================================================";
	Sleep(1000);
    }
	
}
void nhapSinhVien() {
	inDanhSachLop_suaSV_xoaSV();	
}
		

	// NHAP MON HOC
void themMonHoc() {
	setBackgroundColor(16);
	bool check = 0;
	const int x = 120, y = 14;
	gotoxy(x, y - 4); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	gotoxy(x, y - 3); cout << "O                        THONG TIN MOC HOC                        O";
	gotoxy(x, y - 2); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	box_dangnhap(x, y, 70);
	gotoxy(x + 2, y + 2); cout << "TEN MON HOC";
	gotoxy(x + 2, y + 4); cout << "MA MON HOC";
	box_hcn(x + 1, y + 6); gotoxy(x + 2, y + 7); cout << "Nhan Enter de them mon hoc";
	int tdXma = x + 2 + 15, tdXten = x + 2 + 15;
	int tdY = y + 2;
	gotoxy(tdXten, tdY);
	Cursortype();
	bool flag = 0;
	string maMH, tenMH;
	int max = y + 4;
	int min = y + 2;
	bool checkEnter = 0;
	while (1) {
		if (flag == 1) {
			maMH = tenMH = "";
			system("cls");
			break;
		}
		else if (tdY == min) {
			nhapchuoi(tdXten, tdY, tenMH, flag, max, min, checkEnter, 40);
			gotoxy(tdXten, tdY);
		}
		else if (tdY == max) {
			nhapchuoi(tdXma, tdY, maMH, flag, max, min, checkEnter, 15);
			gotoxy(tdXma, tdY);
		}
		if (checkEnter == 1) {
			
			setBackgroundColor(16);
			Nocursortype();
			string temp[2] = {
				"TAO",
				"TRO LAI"
			};
			int n = 2;
			int max1 = y + 9 +n + 2;
			int min1 = y + 7 +n + 2;
			
			box_hcn(x + 1, min1 - 1);
			box_hcn(x + 1, max1 - 1);
			
			gotoxy(x + 2, min1); cout << temp[0];
			gotoxy(x + 2, max1); cout << temp[1];

			thanhsangmoi_hcn(x + 2, min1, temp[0]);

			bool check1 = 0;
			int tdY1cu;
			int tdY1 = min1 ;

			while (1) {
				char s;
				if (_kbhit()) {
					tdY1cu = tdY1;
					s = _getch();
					if (s == Up) {
						if (tdY1 == min1) tdY1 = max1;
						else tdY1 = tdY1 - 2;
					}
					if (s == Down) {
						if (tdY1 == max1) tdY1 = min1;
						else tdY1 = tdY1 + 2;

					}
					thanhsang_hcn(x + 2, tdY1, tdY1cu, temp, min1);
					if (s == Enter) {

						chuanHoaChuoiMa(maMH);
						chuanHoaChuoiTen(tenMH);

						if (tdY1 == min1) {  
							if (checktenMH(tenMH) == true || checkmaMH(maMH) == true || tenMH.length() <= 2 || maMH.length() <= 2) {    // dieu kien bi sai
								if (checktenMH(tenMH) == true || checkmaMH(maMH) == true) {
									gotoxy(x, y + 16); cout << "LOI : MA MON HOC hoac TEN MON HOC da duoc su dung";
									
								}
								if (tenMH.length() <= 2 || maMH.length() <= 2) {
									gotoxy(x, y + 15); cout << "LOI : MA MON HOC VA TEN MON HOC phai tu 3 ki tu tro len";
									
								}
								Sleep(1000);
							}

							else {             // dieu kien dung
								listMH.danhSach[listMH.soMH].tenMH = tenMH;
								listMH.danhSach[listMH.soMH].maMH = maMH;
								++listMH.soMH;
								check = 1;
							}
							for (int i = 0; i < 5; i++) {
								gotoxy(x - 1, min1 + i - 1); cout << "                                     ";
							}
							
							gotoxy(x, y + 15); cout << "                                                            ";
							gotoxy(x, y + 16); cout << "                                                            ";
						}
						
						for (int i = 0; i < 5; i++) {
							gotoxy(x - 1, min1 + i - 1); cout << "                                     ";
						}
						checkEnter = 0;
						check1 = 1;
						flag = 1;
					}
				}
				if (check1 == 1) break;	
			}	
		}
		if (check == 1) {
			system("cls"); 
			break;
		}
	}
}
void sua_va_xoa_MonHoc(MONHOC& mh, int vitri) {
	
	setBackgroundColor(16);
	bool check1 = 0;
	
		bool check = 0;
		const int x = 120, y = 14;
		int max = y + 4;
		int min = y + 2;
		int tdY = y + 2;

		string tenMH = mh.tenMH, maMH = mh.maMH;
		int tdXten = x + 16 + tenMH.length();
		int tdXma = x + 16 + maMH.length();
		nutEsc();

		gotoxy(x, y - 4); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
		gotoxy(x, y - 3); cout << "O                        THONG TIN MOC HOC                        O";
		gotoxy(x, y - 2); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
		box_dangnhap(x, y, 70);
		gotoxy(x + 2, y + 2); cout << "TEN MON HOC"; gotoxy(x + 16, y + 2); cout << tenMH;
		gotoxy(x + 2, y + 4); cout << "MA MON HOC";  gotoxy(x + 16, y + 4); cout << maMH;
		box_hcn(x + 1, y + 6); gotoxy(x + 2, y + 7); cout << "Nhan Enter de them mon hoc";
		bool flag = 0;
		bool checkEnter = 0;
		gotoxy(tdXten, y + 2);

		while (1) {   // nhap tenMH va maMH

			Cursortype();
			if (flag == 1) {
				//check1 = 1;
				//system("cls");
				break;
			}
			else if (tdY == min) {
				nhapchuoi(tdXten, tdY, tenMH, flag, max, min, checkEnter, 40);
				gotoxy(tdXten, tdY);
			}
			else if (tdY == max) {
				nhapchuoi(tdXma, tdY, maMH, flag, max, min, checkEnter, 15);
				gotoxy(tdXma, tdY);
			}
			if (checkEnter == 1) {  // nhan Enter de quay lai hoac sua 

				string temp[3] = {
					"SUA",
					"XOA",
					"TRO LAI"
				};

				box_hcn(x, y + 9);
				gotoxy(x + 1, y + 10); cout << temp[0];
				box_hcn(x, y + 11);
				gotoxy(x + 1, y + 12); cout << temp[1];
				box_hcn(x, y + 13);
				gotoxy(x + 1, y + 14); cout << temp[2];
				tdY = y + 10;
				thanhsangmoi_hcn(x + 1, tdY, temp[0]);
				int tdYcu = tdY;

				while (1) {  // tro lai va sua
					Nocursortype();
					char s;
					if (_kbhit()) {
						s = _getch();
						tdYcu = tdY;
						/*if (s == Esc) {
							checkEnter = 0;
							maMH = mh.maMH;
							tenMH = mh.tenMH;
							system("cls");
							break;
						}*/
						if (s == Up) {
							if (tdY == y + 10) tdY = y + 14;
							else tdY = tdY - 2;
						}
						if (s == Down) {
							if (tdY == y + 14) tdY = y + 10;
							else tdY = tdY + 2;
						}

						else  if (s == Enter) {
							setBackgroundColor(16);
							chuanHoaChuoiTen(tenMH);
							chuanHoaChuoiMa(maMH);

							if (tdY == y + 10) {  // sua 

								if (tenMH.length() > 2 && maMH.length() > 2) {

									bool checktrung = 0;

									string temp_tenMH = listMH.danhSach[vitri].tenMH;
									string temp_maMH = listMH.danhSach[vitri].maMH;


									listMH.danhSach[vitri].tenMH = tenMH;
									listMH.danhSach[vitri].maMH = maMH;

									for (int i = 0; i < listMH.soMH; i++) {
										if (i == vitri) continue;
										if (listMH.danhSach[vitri].tenMH == listMH.danhSach[i].tenMH || listMH.danhSach[vitri].maMH == listMH.danhSach[i].maMH) {

											gotoxy(x + 1, y + 16); cout << "ma mon hoc hoac ten mon hoc da duoc su dung";
											listMH.danhSach[vitri].tenMH = temp_tenMH;
											listMH.danhSach[vitri].maMH = temp_maMH;
											checktrung = 1;
											break;
										}
									}
									if (checktrung == 0) {
										gotoxy(x + 1, y + 16); cout << "Sua thong tin mon hoc thanh cong";
									}


								}
								else if (tenMH.length() < 3 || maMH.length() < 3) {
									gotoxy(x + 1, y + 17); cout << "Chuoi phai tu 3 ki tu tro len";
								}

								Sleep(1000);
								gotoxy(x + 1, y + 14); cout << "                                                         ";
								gotoxy(x + 1, y + 16); cout << "                                                         ";
								flag = 1;




							}

							if (tdY == y + 12) {   // xoa 
								flag = 1;
								if (listMH.soMH > 0) {
									maMH = mh.maMH;
									for (int j = 0; j < listL.soLop; j++) {
										for (nodeSINHVIEN* k = listL.Data[j].ListSV.pHead; k != NULL; k = k->pNext) {
											for (nodeDIEMTHI* q = k->data.listDT.pHead; q != NULL; q = q->pNext) {
												if (q->data.maMH == maMH) {
													xoaDiemThi(k->data.listDT, maMH);
												}
											}
										}
									}
									for (int i = 0; i < listMH.soMH; i++) {
										if (maMH == listMH.danhSach[i].maMH) {
											for (int j = i; j < listMH.soMH; j++) {
												listMH.danhSach[j] = listMH.danhSach[j + 1];
											}
										}
									}
									--listMH.soMH;
									break;
								}
								else return;
							}
							int i;
							for (i = 9; i < 16; i++) {
								gotoxy(x - 2, y + i); cout << "                                        ";
							}
							tdY = min;
							checkEnter = 0;
							flag = 1;
							break;


						}
						thanhsang_hcn(x + 1, tdY, tdYcu, temp, y + 10);
					}
				}

			}

		}
		
	
	ClearConsoleToColors(15, 16);
}
void monHoc() {	
	system("cls");
	ClearConsoleToColors(15, 16);

	bool check = 0;
	const int x = 50, y = 3;
	int max = 5 + y;
	int min = max;
	int tdY = max;
	int tdX = x;
	int tdYcu = tdY;
	

	while (1) {
		khungmonhoc(x - 20, y - 2, y + listMH.soMH * 2 + 4, 85);
		Nocursortype();
		nutEsc();
		box_hcn(x, 0);
		gotoxy(x+1, 1); cout << "nhan Tab de them mon hoc";
		gotoxy(x, y); cout << "SO LUONG MON HOC: ";
		gotoxy(x + 18, y); cout << listMH.soMH;
		gotoxy(x, y + 2); cout << "TEN MON HOC";
		gotoxy(x + 40, y + 2); cout << "MA MON HOC";
		max = 5 + y;
		for (int i = 0; i < listMH.soMH; i++) {
			gotoxy(x, max); cout << listMH.danhSach[i].tenMH;
			gotoxy(x + 40, max); cout << listMH.danhSach[i].maMH;
			max = max + 2;
		}
		thanhsangMoi(x, tdY, listMH.danhSach[(tdY - min) / 2].tenMH, listMH.danhSach[(tdY - min) / 2].maMH);
		while (1) {
			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2) tdY = min;
					else tdY = tdY + 2;
				}
				
				if (s == Esc) {
					check = 1;
					break;
				}
				if (s == tab){
					if (listMH.soMH < listMH.maxSize) {
						themMonHoc();
						if (tdY == min) {
							tdYcu = max;
						}
						else tdYcu = tdYcu - 2;
						break;
					}
				}
				if (s == Enter) {
					sua_va_xoa_MonHoc(listMH.danhSach[(tdY - min) / 2], (tdY - min) / 2);
					tdY = min;
					break;
				}
				
				Nocursortype();
				thanhsang_monhoc(x, tdY, tdYcu, min);
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
}


// in cau hoi
void demSoNodeCHtheoMH(nodeCAUHOI* p, int& dem, string maMH);
void demSoNodeCH(nodeCAUHOI* p, int& dem);
void inThongTinCauHoiChiTiet(CAUHOI ch, int tdX, int tdY)
{
	setBackgroundColor(16);
	gotoxy(tdX, tdY - 1); cout << "MA MON HOC: " << ch.maMH;
	gotoxy(tdX, tdY); cout << "ID: " << ch.id;
	gotoxy(tdX, tdY+1); cout <<"NOI DUNG: " << ch.ND; 
	gotoxy(tdX, tdY+3); cout << "A.  " << ch.A; 
	gotoxy(tdX, tdY+5); cout << "B.  " << ch.B; 
	gotoxy(tdX, tdY+7); cout << "C.  " << ch.C; 
	gotoxy(tdX, tdY+9); cout << "D.  " << ch.D;
	for (int i = 0; i < 4; i++) {
		if(ch.DA == 'A') thanhsangmoi_hcn(tdX, tdY + 3, "A.  " + ch.A);
		if(ch.DA == 'B') thanhsangmoi_hcn(tdX, tdY + 5, "B.  " + ch.B);
		if(ch.DA == 'C') thanhsangmoi_hcn(tdX, tdY + 7, "C.  " + ch.C);
		if(ch.DA == 'D') thanhsangmoi_hcn(tdX, tdY + 9, "D.  " + ch.D);
	}
	
	//gotoxy(tdX, tdY+7); cout << "DA: " << ch.DA; 
}
void chuyenCauHoi_LNR(nodeCAUHOI* root, string maMH, CAUHOI*& listCAUHOI, int& dem)
{
	if (root == NULL) return;
	else {
		if (root != NULL)
		{
			chuyenCauHoi_LNR(root->pLeft, maMH, listCAUHOI, dem);
			if (root->data.maMH == maMH) {
				listCAUHOI[dem] = root->data;
				++dem;
			}
			chuyenCauHoi_LNR(root->pRight, maMH, listCAUHOI, dem);
		}
	}
}
void inCauHoiTheoMaMH(MONHOC mh){
	ClearConsoleToColors(15, 16);

	int count = 0; // tong so cau hoi
	demSoNodeCHtheoMH(rootCH, count, mh.maMH);
	if (count == 0) {
		system("cls");
		return;
	}
	CAUHOI* listcauhoi = new CAUHOI[count];

	int dem = 0; // vi tri
	chuyenCauHoi_LNR(rootCH, mh.maMH, listcauhoi, dem);

	int stt = 1;
	int tongtrang = 1;
	int soCHtrong1trang = 3;

	if (count % soCHtrong1trang != 0) {
		tongtrang = count / soCHtrong1trang + 1;
	}
	else if (count < 2) {
		tongtrang = 1;
	}
	else {
		tongtrang = count / soCHtrong1trang;
	}

	
	bool check = 0;
	while (true) {
	
		ClearConsoleToColors(15, 16);
		
		int tdX = 5, tdY = 20;
		nutEsc();
	
		gotoxy(tdX , 10); cout << "TEN MON HOC: " << mh.tenMH;
		gotoxy(tdX, 11); cout << "MA MON HOC: : " << mh.maMH;
		gotoxy(tdX, 12); cout << "SO CAU HOI: " << count;
		gotoxy(tdX, 13); cout << "TRANG THU " << stt << "/" << tongtrang;
		cout << endl;
		
		for (int i = (stt - 1) * soCHtrong1trang; i < stt * soCHtrong1trang && i < count; i++) {
			inThongTinCauHoiChiTiet(listcauhoi[i], tdX, tdY);
			if (stt * soCHtrong1trang - (stt-1) * soCHtrong1trang >= soCHtrong1trang / 2) {
				tdX = tdX + 80;
				tdY = 20;
			}
			else tdY = tdY + 9;
		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{

			case 27:
				system("cls");
				return;

			case 72:
				// Len
				if (stt >= 1) {
					stt--;
					flag = 1;
				}
				if (stt == 0) stt = tongtrang;
				break;

			case 80:
				// Xuong
				if (stt <= tongtrang) {
					stt++;
					flag = 1;
				}
				if (stt == tongtrang + 1) stt = 1;
				break;
			}

			if (flag) {
				check = 1;
				break;
			}
		}
	}
	//delete[] listcauhoi;
}
void chonDapAn(int& tdX, int& tdY, char& da, int max, int min, bool& checkEnter, bool& check) {
	
	char DA[4] = { 'A','B','C','D' };
	int count = 0;
	while (1) {
		
		Nocursortype();
		char s;
		if (_kbhit()) {
			s = _getch();
			if (s == Left) {
				if (count <= 0) count = 3;
				else --count;
				gotoxy(tdX, tdY); cout << DA[count];
			}
			else if (s == Right) {
				if (count >= 3) count = 0;
				else ++count;
				gotoxy(tdX, tdY); cout << DA[count];
			}
			else if (s == Up) {
				da = DA[count];
				tdY = tdY - 2;
				break;
			}
			else if (s == Down) {
				da = DA[count];
				tdY = min;
				break;
			}
			else if (s == Enter) {
				if (tdY == max) {
					da = DA[count];
					checkEnter = 1;
					break;
				}
			}
			else if (s == Esc) {
				check = 1;
				break;
			}
			
		}
	}

}
void taoCauHoi(MONHOC mh)
{
	ClearConsoleToColors(15, 16);
	CAUHOI ch;
	const int X = 40, Y = 10;
	int tdXnd, tdXa, tdXb, tdXc, tdXd, tdXda, tdXid;
	
	int tdY = Y + 4;
	int max = Y + 14;
	int min = Y + 4;
	
	for (int i = 0; i < 12; i = i + 2) {
		box_dangnhap(X, Y + i, 150);
	}

	int n = 1;

	ch.id = id[count_id - 1];
	ch.DA = 'A';
	ch.maMH = mh.maMH;
	tdXid = tdXnd = tdXa = tdXb = tdXc = tdXd = tdXda = X + n + 15;
	khung();
	gotoxy(X + n, Y - 4); cout << "TEN MON HOC: ";
	gotoxy(X + n + 15, Y - 4); cout << mh.tenMH;

	gotoxy(X + n, Y - 2); cout << "MA MON HOC: ";
	gotoxy(X + n + 15, Y - 2); cout << mh.maMH;

	gotoxy(X + n, Y + 2); cout << "ID";
	gotoxy(X + n, Y + 4); cout << "NOI DUNG";
	gotoxy(X + n, Y + 6); cout << "A";
	gotoxy(X + n, Y + 8); cout << "B";
	gotoxy(X + n, Y + 10); cout << "C";
	gotoxy(X + n, Y + 12); cout << "D";
	gotoxy(X + n, Y + 14); cout << "DAP AN";
	gotoxy(X + n + 15, Y + 14); cout << "<<";
	gotoxy(X + n + 18, Y + 14); cout << ">>";
	
	box_hcn(X + n, Y + 15); // box enter
	gotoxy(X + n, Y + 16); cout << "Nhan Enter de tao";
	gotoxy(tdXid, Y + 2); cout << ch.id;

	nutEsc();
	bool check = 0, checkEnter = 0;
	while (1) {
		if (check == 1) break;

		if (tdY == min) {
			nhapchuoi(tdXnd, tdY, ch.ND, check, max, min, checkEnter, 120);
			gotoxy(tdXnd, tdY);
		}
		else if (tdY == min + 2) {
			nhapchuoi(tdXa, tdY, ch.A, check, max, min, checkEnter, 120);
			gotoxy(tdXa, tdY);
		}
		else if (tdY == min + 4) {
			nhapchuoi(tdXb, tdY, ch.B, check, max, min, checkEnter, 120);
			gotoxy(tdXb, tdY);
		}
		else if (tdY == min + 6) {
			nhapchuoi(tdXc, tdY, ch.C, check, max, min, checkEnter, 120);
			gotoxy(tdXc, tdY);
		}
		else if (tdY == min + 8) {
			nhapchuoi(tdXd, tdY, ch.D, check, max, min, checkEnter, 120);
			gotoxy(tdXd, tdY);
		}
		else if (tdY == min + 10) {
			tdXda = tdXda + 2;
			gotoxy(tdXda, tdY); cout << ch.DA;
			chonDapAn(tdXda, tdY, ch.DA, max, min, checkEnter, check);
			tdXda = tdXda - 2;
		}
		
		
		// nhan enter de tao
		if (checkEnter == 1) {
			string temp[2]
			{
				"TAO",
				"TRO LAI"
			};
			box_hcn(X + 1, Y + 18); 
			box_hcn(X + 1, Y + 20);
			gotoxy(X + 1, Y + 19); cout << temp[0];
			gotoxy(X + 1, Y + 21); cout << temp[1];

			int tdY, tdYcu;
			tdY = tdYcu = Y + 19;
			if (tdY == Y + 19) tdYcu = Y + 21;
			thanhsang_hcn(X + 2, tdY, tdYcu, temp, Y + 19);
			while (1) {
				Nocursortype();
				char s;
				if (_kbhit()) {
					
					tdYcu = tdY;
					s = _getch();
					if (s == Up) {
						if (tdY == Y + 19) tdY = Y + 21;
						else tdY = tdY - 2;
					}
					if (s == Down) {
						if (tdY == Y + 21) tdY = Y + 19;
						else tdY = tdY + 2;
					}
					if (s == Enter) {
						if (tdY == Y + 19) {

							// kiem tra dieu kien
							chuanHoaChuoiTen(ch.ND);
							chuanHoaChuoiTen(ch.A);
							chuanHoaChuoiTen(ch.B);
							chuanHoaChuoiTen(ch.C);
							chuanHoaChuoiTen(ch.D);

							if (ch.ND.length() < 3 || ch.A.length() < 1 || ch.B.length() < 1 || ch.C.length() < 1 || ch.D.length() < 1) {
								
								gotoxy(X + 1, Y + 23); cout << "CAU HOI KHONG HOP LE";
								Sleep(1000);
								gotoxy(X + 1, Y + 23); cout << "                                       ";
								checkEnter = 0;
								
							}
							else {
								
								gotoxy(X + 1, Y + 23); cout << "TAO CAU HOI THANH CONG";
								Sleep(1000);
								gotoxy(X + 1, Y + 23); cout << "                      ";
								checkEnter = 0;
								check = 1;
								themCauHoi(rootCH, ch);
								--count_id;
							}
							
						}
						
						for (int i = 0; i < 5; i++) {
							gotoxy(X, Y + 18 + i); cout << "                                      ";
						}

						tdY = Y + min;
						checkEnter = 0;
						break;
					}
					thanhsang_hcn(X + 2, tdY, tdYcu, temp, Y + 19);
				}
			}
		}
	}

	system("cls");
}
void nhapCauHoi() {
	bool check = 0;
	const int x = 80, y = 3;
	int max = 5 + y;
	int min = max;
	int tdY = max;
	int tdX = x;
	int tdYcu = tdY;
	while (1) {
		ClearConsoleToColors(15, 16);
		khungmonhoc(x - 10, y - 2, y + listMH.soMH * 2 + 4, 75);
		Nocursortype();
		nutEsc();
		gotoxy(x, y); cout << "SO LUONG MON HOC: ";
		gotoxy(x + 18, y); cout << listMH.soMH;
		gotoxy(x, y + 2); cout << "TEN MON HOC";
		gotoxy(x + 40, y + 2); cout << "MA MON HOC";
		max = 5 + y;
		for (int i = 0; i < listMH.soMH; i++) {
			gotoxy(x, max); cout << listMH.danhSach[i].tenMH;
			gotoxy(x + 40, max); cout << listMH.danhSach[i].maMH;
			max = max + 2;
		}
		thanhsangMoi(x, tdY, listMH.danhSach[(tdY - min) / 2].tenMH, listMH.danhSach[(tdY - min) / 2].maMH);
		bool check1 = 0;
		while (1) {
			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2) tdY = min;
					else tdY = tdY + 2;
				}

				if (s == Esc) {
					check = 1;
					break;
				}
				if (s == Enter) {
					int min1 = tdY;
					int tdY1 = min1;
					int tdY1cu = tdY1;
					int max1 = min1 + 4;
					SetBGColor(16);
					string temp[3] = {
						"TAO CAU HOI",
						"IN CAU HOI",
						"TRO LAI"
					};
					int n = 70;
					
					for (int i = 0; i < 5; i = i + 2) {
						box_hcn(x + n, min1 + i - 1);
						gotoxy(x + n + 1, min1 + i); cout << temp[i / 2];
					}
					
					
					thanhsangmoi_hcn(x + n + 1, min1, temp[0]);
					while (1) {
						char s;
						if (_kbhit()) {

							tdY1cu = tdY1;

							s = _getch();
							if (s == Up) {
								if (tdY1 == min1) tdY1 = max1;
								else tdY1 = tdY1- 2;
							}
							else if (s == Down) {
								if (tdY1 == max1) tdY1 = min1;
								else tdY1 = tdY1 + 2;
							}
							if (s == Enter) {
								if (tdY1 == min1) {
									taoCauHoi(listMH.danhSach[(tdY - min) / 2]);
								}
								else if (tdY1 == max1 - 2) {
									inCauHoiTheoMaMH(listMH.danhSach[(tdY - min) / 2]);
								}
								system("cls");
								check1 = 1;
								break;
							}
							thanhsang_hcn(x + n + 1, tdY1, tdY1cu, temp, min1);
						}
					}
					
					
					
					break;
				}
				Nocursortype();
				thanhsang_monhoc(x, tdY, tdYcu, min);
			}
			if (check1 == 1) {
				system("cls");
				break;
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}

}


// DONG HO
int h, m, s;
bool stop = 1; // DIEU KIEN DUNG CUA DONG HO
char numToChar(int n) {
	switch (n) {
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	}
}
void dongHo(int h, int m, int s, char time[])
{
	int temp;
	// giay
	temp = s;
	s = s % 10;
	time[7] = numToChar(s);
	temp = temp / 10;
	time[6] = numToChar(temp);

	// phut
	temp = m;
	m = m % 10;
	time[4] = numToChar(m);
	temp = temp / 10;
	time[3] = numToChar(temp);

	// gio
	temp = h;
	h = h % 10;
	time[1] = numToChar(h);
	temp = temp / 10;
	time[0] = numToChar(temp);
}
bool chuyenDongCuaDongHo(int& h, int& m, int& s) {

		if (s == 0 && m > 0) {
			s = 60;
			--m;
		}
		else if (m == 0 && h > 0) {
			h--;
			m = 60;
		}
		else if (m == 0 && s == 0) {
			stop = 0;
			return 0;
		}
		else if (stop == 0) {
			return 0;
		}
		s--;
		return 1;
	}
void inDongHo(int h, int m, int s) {
	bool stop = 1;
	Nocursortype();
	char time[8] = { '0','0',':','0','0',':','0','0' };
	int i = 10;
	
	
	while (chuyenDongCuaDongHo(h, m, s) == true) {
		
		dongHo(h, m, s, time);
		for (int i = 0; i < 8; i++) {
			Nocursortype();
			gotoxy(7 + i, 17); cout << time[i];
		}
		Sleep(1000);
		for (int i = 0; i < 8; i++) {
			Nocursortype();
			gotoxy(5 + i, 17); cout << "   ";
		
		}
	}
}
void nhapThoiGian() {
	// truong hop m = 1;
	if (m <= 60) {
		h = 0;
		m--;
		s = 59;
	}

	if (m > 59) {
		int temp = m;
		m %= 60; // 
		h = temp / 60;
	}
	inDongHo(h, m, s);
}


// THI TRAC NGHIEM CHO SINH VIEN
void inThongTinCauHoiDaThi(CAUHOI ch, int tdX, int tdY, char daDUNG) {
	setBackgroundColor(16);
	gotoxy(tdX, tdY); cout << "ID: " << ch.id;
	gotoxy(tdX, tdY + 1); cout << "NOI DUNG: " << ch.ND;
	gotoxy(tdX, tdY + 3); cout << "A.  " << ch.A;
	gotoxy(tdX, tdY + 5); cout << "B.  " << ch.B;
	gotoxy(tdX, tdY + 7); cout << "C.  " << ch.C;
	gotoxy(tdX, tdY + 9); cout << "D.  " << ch.D;
	

	for (int i = 0; i < 4; i++) { // dap an cua ban
		if (ch.DA == 'A') thanhsangMoi_menu(tdX, tdY + 3, "A.  " + ch.A, 8);
		if (ch.DA == 'B') thanhsangMoi_menu(tdX, tdY + 5, "B.  " + ch.B, 8);
		if (ch.DA == 'C') thanhsangMoi_menu(tdX, tdY + 7, "C.  " + ch.C, 8);
		if (ch.DA == 'D') thanhsangMoi_menu(tdX, tdY + 9, "D.  " + ch.D, 8);
	}

	for (int i = 0; i < 4; i++) {
		if (daDUNG == 'A') thanhsangMoi_menu(tdX, tdY + 3, "A.  " + ch.A,12);
		if (daDUNG == 'B') thanhsangMoi_menu(tdX, tdY + 5, "B.  " + ch.B, 12);
		if (daDUNG == 'C') thanhsangMoi_menu(tdX, tdY + 7, "C.  " + ch.C,12);
		if (daDUNG == 'D') thanhsangMoi_menu(tdX, tdY + 9, "D.  " + ch.D,12);
	}
	for (int i = 0; i < 4; i++) {
		if (daDUNG == ch.DA == 'A') thanhsangMoi_menu(tdX, tdY + 3, "A.  " + ch.A, 8);
		if (daDUNG == ch.DA == 'B') thanhsangMoi_menu(tdX, tdY + 5, "B.  " + ch.B, 8);
		if (daDUNG == ch.DA == 'C') thanhsangMoi_menu(tdX, tdY + 7, "C.  " + ch.C, 8);
		if (daDUNG == ch.DA == 'D') thanhsangMoi_menu(tdX, tdY + 9, "D.  " + ch.D, 8);
	}

}
void inCauHoiDaThiTheoMaMH(int* id, int socauhoithi, CAUHOI* listcauhoitheomonhoc, char* listda, MONHOC mh, int socaudung, SINHVIEN sv, float diem) {
	ClearConsoleToColors(15, 16);

	int stt = 1;
	int tongtrang = 1;
	int soCHtrong1trang = 3;

	if (socauhoithi % soCHtrong1trang != 0) {
		tongtrang = socauhoithi / soCHtrong1trang + 1;
	}
	else if (socauhoithi < 2) {
		tongtrang = 1;
	}
	else {
		tongtrang = socauhoithi / soCHtrong1trang;
	}


	bool check = 0;
	while (true) {

		ClearConsoleToColors(15, 16);
		
		int tdX = 5, tdY = 20;
		nutEsc();
		gotoxy(tdX + 60, 9);  cout << "MA SINH VIEN        :" << sv.maSV;
		gotoxy(tdX + 60, 10); cout << "HO VA TEN SINH VIEN :" << sv.ho << " " << sv.ten;
		gotoxy(tdX + 60, 11); cout << "SO CAU DUNG         :" << socaudung;
		gotoxy(tdX + 60, 12); cout << "DIEM                :" << diem;

		gotoxy(tdX, 10); cout << "TEN MON HOC: " << mh.tenMH;
		gotoxy(tdX, 11); cout << "MA MON HOC: : " << mh.maMH;
		gotoxy(tdX, 12); cout << "SO CAU HOI: " << socauhoithi;
		gotoxy(tdX, 13); cout << "TRANG THU " << stt << "/" << tongtrang;
		
		thanhsangMoi_menu(tdX, 15, "DAP AN CUA BAN", 12);
		thanhsangMoi_menu(tdX, 17, "DAP AN CAU HOI", 8);

		for (int i = (stt - 1) * soCHtrong1trang; i < stt * soCHtrong1trang && i < socauhoithi; i++) {
			inThongTinCauHoiDaThi(listcauhoitheomonhoc[i], tdX, tdY, listda[i]);
			if (stt * soCHtrong1trang - (stt - 1) * soCHtrong1trang >= soCHtrong1trang / 2) {
				tdX = tdX + 80;
				tdY = 20;
			}
			else tdY = tdY + 9;
		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{
			case 27:
				system("cls");
				return;

			case 72:
				// Len
				if (stt >= 1) {
					stt--;
					flag = 1;
				}
				if (stt == 0) stt = tongtrang;
				break;

			case 80:
				// Xuong
				if (stt <= tongtrang) {
					stt++;
					flag = 1;
				}
				if (stt == tongtrang + 1) stt = 1;
				break;
			}

			if (flag) {
				check = 1;
				break;
			}
		}

	}
	ClearConsoleToColors(15, 16);
	delete[] listcauhoitheomonhoc;
} // in cac cau hoi da thi
void demcaudung(nodeCAUHOI* root, int socaudung, string maMH) {

}
void demSoNodeCHtheoMH(nodeCAUHOI* p, int& dem, string maMH);
void demSoNodeCH(nodeCAUHOI* p, int& dem);
void cauhoithi(nodeCAUHOI* rootCH, CAUHOI*& listcauhoithitheomonhoc, string maMH, int& count) {
	if (rootCH == NULL) return;
	else {
		cauhoithi(rootCH->pLeft, listcauhoithitheomonhoc, maMH, count);
		if (maMH == rootCH->data.maMH) {
			listcauhoithitheomonhoc[count] = rootCH->data; ++count;
		}
		cauhoithi(rootCH->pRight, listcauhoithitheomonhoc, maMH, count);
	}
}
void inCauHoiThi(CAUHOI ch, int tdX, int tdY, int stt) {

	gotoxy(tdX, tdY); cout << "CAU THU: " << stt;
	gotoxy(tdX, tdY + 1); cout << "NOI DUNG: " << ch.ND;
	gotoxy(tdX, tdY + 3); cout << "A.  " << ch.A;
	gotoxy(tdX, tdY + 5); cout << "B.  " << ch.B;
	gotoxy(tdX, tdY + 7); cout << "C.  " << ch.C;
	gotoxy(tdX, tdY + 9); cout << "D.  " << ch.D;
	gotoxy(tdX, tdY + 11); cout << "DAP AN CUA BAN:  <-";
	gotoxy(tdX + 20, tdY + 11); cout << "->";
}
void inBaiThi(MONHOC mh, SINHVIEN& data) {
	
	Cursortype();
	for (nodeDIEMTHI* k = data.listDT.pHead; k != NULL; k = k->pNext) {
		if (k->data.maMH == mh.maMH) return;
	}

	Cursortype();
	int tongsocauhoi = 0; // dem cau hoi theo mon hoc
	demSoNodeCHtheoMH(rootCH, tongsocauhoi, mh.maMH); // dem so cau hoi theo mon hoc co trong FILE

	if (tongsocauhoi == 0) return;
	int socauhoithi;
	const int X = 30;
	const int Y = 10;
	int tdY = Y + 3;
	int n = 60;
	gotoxy(X + n, Y - 4); cout << "TEN MON THI : " << mh.tenMH;
	gotoxy(X + n, Y - 2); cout << "MA MON THI  : " << mh.maMH;
	nutEsc();
	// so cau hoi
	gotoxy(X - 14 + n, Y + 3); cout << "CAU HOI";
	box_hcn(X + n, Y + 2);
	gotoxy(X + 1 + n, Y + 3); cout << "<<";
	gotoxy(X + 27 + n, Y + 3); cout << ">>";

	// thoi gian thi
	gotoxy(X - 14 + n, Y + 5); cout << "THOI GIAN";
	box_hcn(X + n, Y + 4);
	gotoxy(X + n + 1, Y + 5); cout << "<<";
	gotoxy(X + 27 + n, Y + 5); cout << ">>";

	box_hcn(X + n, Y + 6); gotoxy(X + 1 + n, Y + 7); cout << "NHAN ENTER DE BAT DAU THI";
	int min = 1;
	int max = tongsocauhoi;
	gotoxy(X + 14 + n, Y + 3); cout << tongsocauhoi;
	int sttcauhoi = tongsocauhoi;

	int minTG = 1;
	int maxTG = 90;
	int tg = maxTG;
	gotoxy(X - 3 + n, tdY); cout << (char)219;
	while (1) {
		Nocursortype();
		char s;

		gotoxy(X + 14 + n, Y + 3); cout << sttcauhoi;
		gotoxy(X + 14 + n, Y + 5); cout << tg;
		if (_kbhit()) {
			s = _getch();

			gotoxy(X - 3 + n, tdY); cout << " ";


			if (s == Up) {
				if (tdY == Y + 3) tdY == Y + 5;
				else tdY = tdY - 2;
			}
			if (s == Down) {
				if (tdY == Y + 5) tdY = Y + 3;
				else tdY = tdY + 2;
			}

			gotoxy(X - 3 + n, tdY); cout << (char)219;


			if (s == Esc) {
				system("cls");
				return;
			}
			if (tdY == Y + 3) {
				if (s == Left) {
					if (sttcauhoi == min) sttcauhoi = tongsocauhoi;
					else --sttcauhoi;
				}
				else if (s == Right) {
					if (sttcauhoi == tongsocauhoi) sttcauhoi = min;
					else ++sttcauhoi;
				}
				gotoxy(X + 14 + n, Y + 3); cout << "     ";

			}

			else if (tdY == Y + 5) {
				if (s == Left) {
					if (tg == minTG) tg = maxTG;
					else --tg;
				}
				else if (s == Right) {
					if (tg == maxTG) tg = minTG;
					else ++tg;
				}
				gotoxy(X + 14 + n, Y + 5); cout << "      ";
			}
			if (s == Enter) {
				if (tg > 0 && n > 0) {
					socauhoithi = sttcauhoi;
					m = tg;
					break;
				}
			}


		}
	}

	thread clock = thread(nhapThoiGian);
	system("cls");

	// truong hop : cau hoi nhap vao lon hon cau hoi co trong FILE

	int count = 0; // so cau hoi theo mon hoc
	int Z = tongsocauhoi + 1;
	CAUHOI* listcauhoitheomonhoc = new CAUHOI[Z]; // tong so cau hoi theo mon hoc
	cauhoithi(rootCH, listcauhoitheomonhoc, mh.maMH, count);   // dua cau hoi vao mang listcauhoitheomonhoc


	// ranDom cau hoi 
	srand(time(NULL));
	max = count; // tong so cau hoi trong mon hoc
	min = 1;
	int N = max - min + 1;
	int soCH = count + 1;
	int* id = new int[soCH];
	int i;
	for (i = min; i <= max; i++) {
		id[i - min] = i;
	}
	random_shuffle(id, id + N);


	int stt = 1;
	int tongtrang = 1;
	int soCHtrong1trang = 1;

	if (socauhoithi % soCHtrong1trang != 0) {
		tongtrang = socauhoithi / soCHtrong1trang + 1;
	}
	else {
		tongtrang = socauhoithi / soCHtrong1trang;
	}

	bool check = 0;
	char temp[4] =
	{
		'A', 'B', 'C', 'D'
	};
	int soCHtheoMH = socauhoithi + 1; 
	char* listda = new char[soCHtheoMH];
	char* listdaDUNG = new char[soCHtheoMH];
	CAUHOI* listcauhoitheomonhoc_1 = new CAUHOI[soCHtheoMH];

	for (int i = 0; i < socauhoithi; i++) {
		listcauhoitheomonhoc_1[i] = listcauhoitheomonhoc[id[i] - 1];
	}

	for (int i = 0; i < socauhoithi; i++) {
		listdaDUNG[id[i] - 1] = listcauhoitheomonhoc_1[id[i] - 1].DA;
	}
	for (int i = 0; i < socauhoithi; i++) {
		listda[i] = ' ';
	}

	gotoxy(6, 15); cout << "===TIME===";
	box_hcn1(4, 16, 15);
	int tdX = 5;
	tdY = 20;
	i;
	for (i = 1; i < 59; i++) {
		gotoxy(tdX + 100, i); cout << "||";
		gotoxy(0, i); cout << "||";
		gotoxy(tdX + 101 * 2, i); cout << "||";
	}
	for (i = 1; i < tdX + 100 * 2; i++) {
		gotoxy(i, 0); cout << "=";
		gotoxy(i, 59); cout << "=";
	}

	box_hcn1(4, 16, 15);
	gotoxy(3, 1); cout << "===========";
	gotoxy(3, 2); cout << "====ESC====";
	gotoxy(3, 3); cout << "===========";

	gotoxy(tdX, 10); cout << "TEN MON HOC: " << mh.tenMH;
	gotoxy(tdX, 11); cout << "MA MON HOC: : " << mh.maMH;
	gotoxy(tdX, 12); cout << "SO CAU HOI: " << socauhoithi; // so cau hoi muuon thi
	gotoxy(tdX, 13); cout << "CAU THU " << stt << "/" << socauhoithi;
	int x = 1;

	gotoxy(tdX + 110, 3);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	gotoxy(tdX + 110, 4);   cout << "O                            DAP AN CUA BAN                              O";
	gotoxy(tdX + 110, 5);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";

	while (true) {

		//system("cls");
		for (int i = 0; i < 13; i++) {
			gotoxy(tdX, tdY + i); cout << "                                                                                    ";
		}
		int x = 1;
		int y = 5;
		int count_dapan = 0; // A,B,C,D
		for (int i = 0; i < socauhoithi; i++) {
			if (i % 25 == 0 && i != 0) {
				tdX = tdX + 40;
				y = 5;
			}
			gotoxy(tdX + 105 + 10, 5 + y); cout << "DAP AN cau thu " << x << ": " << listda[x - 1];
			y = y + 2;
			++x;
		}
		tdX = 5;

		// in 1 cau hoi 
		inCauHoiThi(listcauhoitheomonhoc_1[stt - 1], tdX, tdY, stt);


		gotoxy(tdX + 19, tdY + 11); cout << temp[0];



		while (1) {

			char s;

			if (_kbhit()) {
				s = _getch();
				if (s == Esc) {
					box_hcn1(20, 1, 80);
					gotoxy(21, 2);     cout << "BAN CO MUON KET THUC BAI THI ? , NHAN ENTER DE KET THUC, NHAN ESC DE QUAY LAI";

					char x = _getch();

					if (x == Esc) {
						gotoxy(18, 1); cout << "                                                                                       ";
						gotoxy(18, 2); cout << "                                                                                       ";
						gotoxy(18, 3); cout << "                                                                                       ";
					}
					else if (x == Enter) {

						check = 1;
						stop = 0;
						ClearConsoleToColors(15, 16);
						break;
					}
				}
				if (stt >= 1 && stt <= tongtrang) {
					if (s == Up) {
						if (stt <= 1) stt = tongtrang;
						else --stt;

						break;
					}
					else if (s == Down) {
						if (stt >= tongtrang) stt = 1;
						else ++stt;

						break;
					}
				}
				if (s == Left) {
					gotoxy(tdX + 21, tdY + 11); cout << " ";
					gotoxy(tdX + 17, tdY + 11); cout << (char)219;
					if (count_dapan == 0) count_dapan = 3;
					else count_dapan--;
				}
				else if (s == Right) {
					gotoxy(tdX + 17, tdY + 11); cout << " ";
					gotoxy(tdX + 21, tdY + 11); cout << (char)219;
					if (count_dapan >= 3) count_dapan = 0;
					else count_dapan++;
				}
				gotoxy(tdX + 19, tdY + 11); cout << temp[count_dapan];

				if (s == Enter) {
					listda[stt - 1] = temp[count_dapan];

					if (stt >= tongtrang) stt = 1;
					else ++stt;
					break;
				}
				//thanhsangmoi_hcn(tdX + 2, tdY + 11, " " + temp[count_dapan]);

			}
			if (stop == 0) {
				system("cls");
				check = 1;
				break;
			}
		}
		if (check == 1 || stop == 0) {
			system("cls");
			break;
		}
	}
	clock.join();

	system("cls");

	int socaudung = 0;
	for (int i = 0; i < socauhoithi; i++) {
		if (listda[i] == listdaDUNG[i]) ++socaudung;
	}

	float diemmoicau = (float)10 / socauhoithi;
	diemmoicau = roundf(diemmoicau * 10) / 10;
	float diem = diemmoicau * socaudung;

	nodeDIEMTHI* nodedt = new nodeDIEMTHI;
	nodedt->data.diem = diem;
	nodedt->data.maMH = mh.maMH;
	nodedt->pNext = NULL;
	

	// neu chua thi mon nay
	if (data.listDT.pHead == NULL) {
		data.listDT.pHead = data.listDT.pTail = nodedt;
	}
	else {
		bool checkthi = 0;
		for (nodeDIEMTHI* k = data.listDT.pHead; k != NULL; k = k->pNext) {
			if (k->data.maMH == mh.maMH) {
				checkthi = 1;
				k->data.diem = diem;
				break;
			}
		}
		if (checkthi == 0) {
			data.listDT.pTail->pNext = nodedt;
			data.listDT.pTail = nodedt;
		}
	}

	inCauHoiDaThiTheoMaMH(id, socauhoithi, listcauhoitheomonhoc, listda, mh, socaudung, data, diem);
	system("cls");
	
	delete[] listdaDUNG;
	listdaDUNG = nullptr;
	delete[] listda;
	listda = nullptr;
	delete[] listcauhoitheomonhoc;
	listcauhoitheomonhoc = nullptr;
	delete[] listcauhoitheomonhoc_1;
	listcauhoitheomonhoc_1 = nullptr;
	stop = 1;
	ClearConsoleToColors(15, 16);
}
void thiTracNghiemChoSV(SINHVIEN & data){
	system("cls");
	ClearConsoleToColors(15, 16);
	bool check = 0;
	const int x = 80, y = 3;
	int max = 5 + y;
	int min = max;
	int tdY = max;
	int tdX = x;
	int tdYcu = tdY;
	
	while (1) {
		khungmonhoc(x - 20, y - 2, y + listMH.soMH * 2 + 4, 100);
		Nocursortype();
		nutEsc();
		gotoxy(x, y); cout << "SO LUONG MON THI: ";
		gotoxy(x + 18, y); cout << listMH.soMH;
		gotoxy(x, y + 2); cout << "TEN MON HOC";
		gotoxy(x + 40, y + 2); cout << "MA MON HOC";
		max = 5 + y;
		for (int i = 0; i < listMH.soMH; i++) {
			gotoxy(x, max); cout << listMH.danhSach[i].tenMH;
			gotoxy(x + 40, max); cout << listMH.danhSach[i].maMH;
			max = max + 2;
		}
		thanhsangMoi(x, tdY, listMH.danhSach[(tdY - min) / 2].tenMH, listMH.danhSach[(tdY - min) / 2].maMH);
		while (1) {
			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2) tdY = min;
					else tdY = tdY + 2;
				}

				if (s == Esc) {
					check = 1;
					break;
				}
				if (s == Enter) {
					bool checkthi = 0;
					ClearConsoleToColors(15, 16);

					for (nodeDIEMTHI* k = data.listDT.pHead; k != NULL; k = k->pNext) {
						if ((listMH.danhSach[(tdY - min) / 2].maMH == k->data.maMH)) {
							
							gotoxy(80, 9);  cout << "oooooooooooooooooooooooooooooooooooooo";
							gotoxy(80, 10); cout << "O       BAN DA THI MON NAY ROI       O";
							gotoxy(80, 11); cout << "oooooooooooooooooooooooooooooooooooooo";
							checkthi = 1;
							break;
						}
					}
					if(checkthi == 1) {
						cout << "\n";
						system("pause");
						system("cls");
						break;
					}
				    if(checkthi == 0) inBaiThi(listMH.danhSach[(tdY - min) / 2], data);
					tdY = min;
					break;
				}

				Nocursortype();
				thanhsang_monhoc(x, tdY, tdYcu, min);
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
	ClearConsoleToColors(15, 16);
}


// thi trac nghiem giao vien
void inCauHoiDaThiTheoMaMH_GV(int* id, int socauhoithi, CAUHOI* listcauhoitheomonhoc, char* listda, MONHOC mh, int socaudung,float diem) {
	ClearConsoleToColors(15, 16);

	int stt = 1;
	int tongtrang = 1;
	int soCHtrong1trang = 3;

	if (socauhoithi % soCHtrong1trang != 0) {
		tongtrang = socauhoithi / soCHtrong1trang + 1;
	}
	else if (socauhoithi < 2) {
		tongtrang = 1;
	}
	else {
		tongtrang = socauhoithi / soCHtrong1trang;
	}


	bool check = 0;
	while (true) {

		ClearConsoleToColors(15, 16);

		int tdX = 5, tdY = 20;
		nutEsc();
		gotoxy(tdX + 60, 10); cout << "HO VA TEN SINH VIEN : GIAO VIEN";
		gotoxy(tdX + 60, 11); cout << "SO CAU DUNG         :" << socaudung;
		gotoxy(tdX + 60, 12); cout << "DIEM                :" << diem;

		gotoxy(tdX, 10); cout << "TEN MON HOC: " << mh.tenMH;
		gotoxy(tdX, 11); cout << "MA MON HOC: : " << mh.maMH;
		gotoxy(tdX, 12); cout << "SO CAU HOI: " << socauhoithi;
		gotoxy(tdX, 13); cout << "TRANG THU " << stt << "/" << tongtrang;

		
		thanhsangMoi_menu(tdX, 15, "DAP AN CUA BAN", 12);
		thanhsangMoi_menu(tdX, 17, "DAP AN CAU HOI", 8);


		for (int i = (stt - 1) * soCHtrong1trang; i < stt * soCHtrong1trang && i < socauhoithi; i++) {
			inThongTinCauHoiDaThi(listcauhoitheomonhoc[i], tdX, tdY, listda[i]);
			if (stt * soCHtrong1trang - (stt - 1) * soCHtrong1trang >= soCHtrong1trang / 2) {
				tdX = tdX + 80;
				tdY = 20;
			}
			else tdY = tdY + 9;
		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{
			case 27:
				system("cls");
				return;

			case 72:
				// Len
				if (stt >= 1) {
					stt--;
					flag = 1;
				}
				if (stt == 0) stt = tongtrang;
				break;

			case 80:
				// Xuong
				if (stt <= tongtrang) {
					stt++;
					flag = 1;
				}
				if (stt == tongtrang + 1) stt = 1;
				break;
			}

			if (flag) {
				check = 1;
				break;
			}
		}

	}
	ClearConsoleToColors(15, 16);
	delete[] listcauhoitheomonhoc;
} // in cac cau hoi da thi
void inBaiThi_GV(MONHOC mh) {

	Cursortype();
	int tongsocauhoi = 0; // dem cau hoi theo mon hoc
	demSoNodeCHtheoMH(rootCH, tongsocauhoi, mh.maMH); // dem so cau hoi theo mon hoc co trong FILE

	if (tongsocauhoi == 0) return;
	int socauhoithi;
	const int X = 30;
	const int Y = 10;
	int tdY = Y + 3;
	int n = 60;
	gotoxy(X + n, Y - 4); cout << "TEN MON THI : " << mh.tenMH;
	gotoxy(X + n, Y - 2); cout << "MA MON THI  : " << mh.maMH;
	nutEsc();
	// so cau hoi
	gotoxy(X - 14 + n, Y + 3); cout << "CAU HOI";
	box_hcn(X + n, Y + 2);
	gotoxy(X + 1 + n, Y + 3); cout << "<<";
	gotoxy(X + 27 + n, Y + 3); cout << ">>";

	// thoi gian thi
	gotoxy(X - 14 + n, Y + 5); cout << "THOI GIAN";
	box_hcn(X + n, Y + 4);
	gotoxy(X + n + 1, Y + 5); cout << "<<";
	gotoxy(X + 27 + n, Y + 5); cout << ">>";

	box_hcn(X + n, Y + 6); gotoxy(X + 1 + n, Y + 7); cout << "NHAN ENTER DE BAT DAU THI";
	int min = 1;
	int max = tongsocauhoi;
	gotoxy(X + 14 + n, Y + 3); cout << tongsocauhoi;
	int sttcauhoi = tongsocauhoi;

	int minTG = 1;
	int maxTG = 90;
	int tg = maxTG;
	gotoxy(X - 3 + n, tdY); cout << (char)219;
	while (1) {
		Nocursortype();
		char s;
		
		gotoxy(X + 14 + n, Y + 3); cout << sttcauhoi;
		gotoxy(X + 14 + n, Y + 5); cout << tg;
		if (_kbhit()) {
			s = _getch();

			gotoxy(X - 3 + n, tdY); cout << " ";


			if (s == Up) {
				if (tdY == Y + 3) tdY == Y + 5;
				else tdY = tdY - 2;
			}
			if (s == Down) {
				if (tdY == Y + 5) tdY = Y + 3;
				else tdY = tdY + 2;
			}

			gotoxy(X - 3 + n, tdY); cout << (char)219;


			if (s == Esc) {
				
				ClearConsoleToColors(15, 16);

				return;
			}
			if (tdY == Y + 3) {
				if (s == Left) {
					if (sttcauhoi == min) sttcauhoi = tongsocauhoi;
					else --sttcauhoi;
				}
				else if (s == Right) {
					if (sttcauhoi == tongsocauhoi) sttcauhoi = min;
					else ++sttcauhoi;
				}
				gotoxy(X + 14 + n, Y + 3); cout << "     ";

			}

			else if (tdY == Y + 5) {
				if (s == Left) {
					if (tg == minTG) tg = maxTG;
					else --tg;
				}
				else if (s == Right) {
					if (tg == maxTG) tg = minTG;
					else ++tg;
				}
				gotoxy(X + 14 + n, Y + 5); cout << "      ";
			}
			if (s == Enter) {
				if (tg > 0 && n > 0) {
					socauhoithi = sttcauhoi;
					m = tg;
					break;
				}
			}


		}
	}

	thread clock = thread(nhapThoiGian);
	system("cls");
	
	// truong hop : cau hoi nhap vao lon hon cau hoi co trong FILE

	int count = 0; // so cau hoi theo mon hoc

	CAUHOI* listcauhoitheomonhoc = new CAUHOI[tongsocauhoi + 1]; // tong so cau hoi theo mon hoc

	cauhoithi(rootCH, listcauhoitheomonhoc, mh.maMH, count);   // dua cau hoi vao mang listcauhoitheomonhoc



	// ranDom cau hoi 

	srand(time(NULL));
	max = count; // tong so cau hoi trong mon hoc
	min = 1;
	int N = max - min + 1;

	int* id = new int[count + 1];
	int i;
	for (i = min; i <= max; i++) {
		id[i - min] = i;
	}
	random_shuffle(id, id + N);


	int stt = 1;
	int tongtrang = 1;
	int soCHtrong1trang = 1;

	if (socauhoithi % soCHtrong1trang != 0) {
		tongtrang = socauhoithi / soCHtrong1trang + 1;
	}

	else {
		tongtrang = socauhoithi / soCHtrong1trang;
	}

	bool check = 0;
	char temp[4] =
	{
		'A', 'B', 'C', 'D'
	};

	char* listda = new char[socauhoithi + 1];
	char* listdaDUNG = new char[socauhoithi + 1];
	CAUHOI* listcauhoitheomonhoc_1 = new CAUHOI[socauhoithi + 1];

	for (int i = 0; i < socauhoithi; i++) {
		listcauhoitheomonhoc_1[i] = listcauhoitheomonhoc[id[i] - 1];
	}
	

	for (int i = 0; i < socauhoithi; i++) {
		listda[i] = NULL;
	}



	gotoxy(6, 15); cout << "===TIME===";
	box_hcn1(4, 16, 15);
	int tdX = 5;
	tdY = 20;
	i;
	for (i = 1; i < 59; i++) {
		gotoxy(tdX + 100, i); cout << "||";
		gotoxy(0, i); cout << "||";
		gotoxy(tdX + 101 * 2, i); cout << "||";
	}
	for (i = 1; i < tdX + 100 * 2; i++) {
		gotoxy(i, 0); cout << "=";
		gotoxy(i, 59); cout << "=";
	}

	box_hcn1(4, 16, 15);
	gotoxy(3, 1); cout << "===========";
	gotoxy(3, 2); cout << "====ESC====";
	gotoxy(3, 3); cout << "===========";

	gotoxy(tdX, 10); cout << "TEN MON HOC: " << mh.tenMH;
	gotoxy(tdX, 11); cout << "MA MON HOC: : " << mh.maMH;
	gotoxy(tdX, 12); cout << "SO CAU HOI: " << socauhoithi; // so cau hoi muuon thi
	gotoxy(tdX, 13); cout << "CAU THU " << stt << "/" << socauhoithi;
	int x = 1;

	gotoxy(tdX + 110, 3);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	gotoxy(tdX + 110, 4);   cout << "O                            DAP AN CUA BAN                              O";
	gotoxy(tdX + 110, 5);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";

	while (true) {

		//system("cls");
		for (int i = 0; i < 13; i++) {
			gotoxy(tdX, tdY + i); cout << "                                                                                    ";
		}
		int x = 1;
		int y = 5;
		int count_dapan = 0; // A,B,C,D
		for (int i = 0; i < socauhoithi; i++) {
			if (i % 25 == 0 && i != 0) {
				tdX = tdX + 40;
				y = 5;
			}
			gotoxy(tdX + 105 + 10, 5 + y); cout << "DAP AN cau thu " << x << ": " << listda[x-1];
			y = y + 2;
			++x;
		}
		tdX = 5;

		// in 1 cau hoi 
		inCauHoiThi(listcauhoitheomonhoc_1[stt - 1], tdX, tdY, stt);


		gotoxy(tdX + 19, tdY + 11); cout << temp[0];

		

		while (1) {

			char s;

			if (_kbhit()) {
				s = _getch();
				if (s == Esc) {
					box_hcn1(20, 1, 80);
					gotoxy(21, 2);     cout << "BAN CO MUON KET THUC BAI THI ? , NHAN ENTER DE KET THUC, NHAN ESC DE QUAY LAI";
					
					char x = _getch();
				
					if (x == Esc) {
						gotoxy(18, 1); cout << "                                                                                       ";
						gotoxy(18, 2); cout << "                                                                                       ";
						gotoxy(18, 3); cout << "                                                                                       ";
					}
					else if (x == Enter) {
						
						check = 1;
						stop = 0;
						ClearConsoleToColors(15, 16);
						break;
					}
					
				}
				if (stt >= 1 && stt <= tongtrang) {
					if (s == Up) {
						if (stt <= 1) stt = tongtrang;
						else --stt;

						break;
					}
					else if (s == Down) {
						if (stt >= tongtrang) stt = 1;
						else ++stt;

						break;
					}
				}
				if (s == Left) {
					gotoxy(tdX + 17, tdY + 11); cout << "          ";
					gotoxy(tdX + 17, tdY + 11); cout << "<- ->";
					if (count_dapan == 0) count_dapan = 3;
					else count_dapan--;
				}
				else if (s == Right) {
					gotoxy(tdX + 17, tdY + 11); cout << "          ";
					gotoxy(tdX + 17, tdY + 11); cout << "<- ->";
					if (count_dapan >= 3) count_dapan = 0;
					else count_dapan++;
				}
				gotoxy(tdX + 19, tdY + 11); cout << temp[count_dapan];

				if (s == Enter) {
					listda[stt-1] = temp[count_dapan];

					if (stt >= tongtrang) stt = 1;
					else ++stt;
					break;
				}
				//thanhsangmoi_hcn(tdX + 2, tdY + 11, " " + temp[count_dapan]);
				
			}
			if (stop == 0) {
				system("cls");
				check = 1;
				break;
			}
		}
		if (check == 1 || stop == 0) {
			system("cls");
			break;
		}
	}
	clock.join();

	system("cls");



	int socaudung = 0;
	for (int i = 0; i < socauhoithi; i++) {
		if (listda[i] == listcauhoitheomonhoc_1[i].DA) ++socaudung;
	}

	float diemmoicau = (float)10 / socauhoithi;
	diemmoicau = roundf(diemmoicau * 10) / 10;
	float diem = diemmoicau * socaudung;

	nodeDIEMTHI* nodedt = new nodeDIEMTHI;
	nodedt->data.diem = diem;
	nodedt->data.maMH = mh.maMH;
	nodedt->pNext = NULL;

	

	// neu chua thi mon nay
	

	inCauHoiDaThiTheoMaMH_GV(id, socauhoithi, listcauhoitheomonhoc_1, listda, mh, socaudung,diem);
	system("cls");

	delete[] listcauhoitheomonhoc_1;
	delete[] listdaDUNG;
	delete[] listda;
	delete[] listcauhoitheomonhoc;
	stop = 1;
	ClearConsoleToColors(15, 16);
}
void thiTracNghiemChoGV() {
	system("cls");
	ClearConsoleToColors(15, 16);
	bool check = 0;
	const int x = 80, y = 3;
	int max = 5 + y;
	int min = max;
	int tdY = max;
	int tdX = x;
	int tdYcu = tdY;
	
	while (1) {
		Nocursortype();
		nutEsc();
		khungmonhoc(x - 20, y - 2, y + listMH.soMH * 2 + 4, 100);
		gotoxy(x, y); cout << "SO LUONG MON HOC: ";
		gotoxy(x + 18, y); cout << listMH.soMH;
		gotoxy(x, y + 2); cout << "TEN MON HOC";
		gotoxy(x + 40, y + 2); cout << "MA MON HOC";
		max = 5 + y;
		for (int i = 0; i < listMH.soMH; i++) {
			gotoxy(x, max); cout << listMH.danhSach[i].tenMH;
			gotoxy(x + 40, max); cout << listMH.danhSach[i].maMH;
			max = max + 2;
		}
		thanhsangMoi(x, tdY, listMH.danhSach[(tdY - min) / 2].tenMH, listMH.danhSach[(tdY - min) / 2].maMH);
		while (1) {
			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2) tdY = min;
					else tdY = tdY + 2;
				}

				if (s == Esc) {
					check = 1;
					break;
				}
				if (s == Enter) {
					bool checkthi = 0;
					ClearConsoleToColors(15, 16);
					inBaiThi_GV(listMH.danhSach[(tdY - min) / 2]);
					tdY = min;
					break;
				}

				Nocursortype();
				thanhsang_monhoc(x, tdY, tdYcu, min);
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
	ClearConsoleToColors(15, 16);
}



// IN BANG DIEM CUA 1 LOP
void xoa_inThongTin_1_sinhvien_diemthi(int X, int Y) {
	int tdX = X - 15;
	int tdY = Y;
	int n = 5;
	for (int i = 0; i < 16; i++) {
		gotoxy(tdX + n - 2, tdY - 4 + i); cout << "                                                                            ";
	}
}
void inThongTin_1_sinhvien_diemthi(SINHVIEN sv, int X, int Y, string maMH) {
	bool check = 0;
	int tdX = X - 15;
	int tdY = Y;
	int n = 5;
	gotoxy(tdX + n, tdY - 4); cout << "======================================";
	gotoxy(tdX + n, tdY - 3); cout << "==========THONG TIN SINH VIEN=========";
	gotoxy(tdX + n, tdY - 2); cout << "======================================";
	box_dangnhap(tdX, tdY, 70);
	box_dangnhap(tdX, tdY + 4, 70);
	box_dangnhap(tdX, tdY + 6, 70);
	n = 17;
	gotoxy(tdX + 1, tdY + 2); cout << "Ma sinh vien"; gotoxy(tdX + n, tdY + 2); cout << sv.maSV;
	gotoxy(tdX + 1, tdY + 4); cout << "Ho va ten lot"; gotoxy(tdX + n, tdY + 4); cout << sv.ho;
	gotoxy(tdX + 1, tdY + 6); cout << "Ten"; gotoxy(tdX + n, tdY + 6); cout << sv.ten;
	gotoxy(tdX + 1, tdY + 8); cout << "Gioi tinh"; gotoxy(tdX + n, tdY + 8); cout << sv.gioiTinh;
	gotoxy(tdX + 1, tdY + 10); cout << "Diem Thi";
	for (nodeDIEMTHI* k = sv.listDT.pHead; k != NULL; k = k->pNext) {
		if (k->data.maMH == maMH) {
			check = 1;
			gotoxy(tdX + n, tdY + 10); cout << k->data.diem;
			break;
		}
	}
	if (check == 0) {
		gotoxy(tdX + n, tdY + 10); cout << "CHUA THI";
	}
}
void inDanhSachSinhVien_diemthi(SINHVIEN sv, int tdX, int& tdY, string maMH ) {
	bool check = 0;
	gotoxy(tdX + 5, tdY + 3); vietHoa(sv.maSV); cout << sv.maSV;
	gotoxy(tdX + 25, tdY + 3); vietHoa(sv.ho); cout << sv.ho;
	gotoxy(tdX + 45, tdY + 3); vietHoa(sv.ten); cout << sv.ten;
	for (nodeDIEMTHI* k = sv.listDT.pHead; k != NULL; k = k->pNext) {
		if (k->data.maMH == maMH) {
			check = 1;
			gotoxy(tdX + 65, tdY + 3); cout << k->data.diem;
			break;
		}
	}
	if (check == 0) {
		gotoxy(tdX + 65, tdY + 3); cout << "CHUA THI";
	}
}
void inSinhVien_diemthi(LOP& lop, MONHOC mh) {
	ClearConsoleToColors(15, 16);
	int tdX = 40, tdY = 20, tdYcu;
	int z = 2;
	int trang = 1;
	int soLuong = 15;

	listSINHVIENTHEOLOP* listSVTL = new listSINHVIENTHEOLOP; // chuyen qua mang 
	int i = 0;
	if (lop.ListSV.pHead == NULL) listSVTL->soSV = 0;
	else {
		for (nodeSINHVIEN* k = lop.ListSV.pHead; k != NULL; k = k->pNext) {
			listSVTL->Data[i] = k->data;
			++i; ++listSVTL->soSV;
		}
	}
	int tongsotrang = 1;
	if (listSVTL->soSV != 0) {
		if (listSVTL->soSV % soLuong == 0) {
			tongsotrang = listSVTL->soSV / soLuong;
		}
		else tongsotrang = listSVTL->soSV / soLuong + 1;
	}


	int min = 14; tdYcu = tdY;
	const int Y = tdY;
	bool check = 0;
	while (true) {
		

		Nocursortype();
		gotoxy(tdX + 15, 15); cout << "                  ";
		for (i = 23; i < 54; i = i + 2) {
			gotoxy(tdX, i); cout << "                                                                                     ";
		}
		tdY = 20;
		nutEsc();
		// hop tim sinh vien
		box_hcn(99, 0);
		gotoxy(100, 1); cout << "nhan TAB de tim SINH VIEN";

		gotoxy(tdX + 47, Y - 9); cout << "^";
		gotoxy(tdX + 40, Y - 8); cout << "UP:    |";
		gotoxy(tdX + 40, Y - 6); cout << "DOWN:  |";
		gotoxy(tdX + 47, Y - 5); cout << "v";

		gotoxy(tdX + 45 + 20, Y - 8); cout << "TEN MON HOC: " << mh.tenMH;
		gotoxy(tdX + 45 + 20, Y - 6); cout << "TEN MON HOC: " << mh.maMH;

		gotoxy(tdX + 5, Y - 8); cout << "TEN LOP: " << lop.tenLop;
		gotoxy(tdX + 5, Y - 7); cout << "MA LOP : " << lop.maLop;
		gotoxy(tdX + 5, Y - 6); cout << "SO SINH VIEN: " << listSVTL->soSV;
		gotoxy(tdX + 5, Y - 5); cout << "TRANG THU " << trang << "/" << tongsotrang;

		for (i = (trang - 1) * soLuong; i < trang * soLuong && i < listSVTL->soSV; i++) {

			gotoxy(tdX + 5, Y - 1); cout << "Ma Sinh Vien";
			gotoxy(tdX + 25, Y - 1); cout << "Ho va Ten lot";
			gotoxy(tdX + 45, Y - 1); cout << "Ten Chinh";
			gotoxy(tdX + 65, Y - 1); cout << "DIEM";
			inDanhSachSinhVien_diemthi(listSVTL->Data[i], tdX, tdY,mh.maMH);

			tdY = tdY + 2;

		}
		bool flag = 0;
		while (true) {
			char key = _getch();

			switch (key)
			{
			case Esc:

				system("cls");
				return;

			case Up:
				// Len
				if (trang >= 1) {

					trang--;
					flag = 1;
				}
				if (trang == 0) trang = tongsotrang;
				break;

			case Down:
				// Xuong
				if (trang <= tongsotrang) {

					trang++;
					flag = 1;
				}
				if (trang == tongsotrang + 1) trang = 1;
				break;

			case tab:

				Cursortype();

				// tim sinh vien

				string temp;
				string maLop;
				int tdX = 101;
				int tdY = 1;
				gotoxy(tdX - 1, tdY); cout << "                           ";
				gotoxy(tdX - 1, tdY);
				while (1) {
					char s;
					if (_kbhit()) {
						s = _getch();
						if (s == Left || s == Right || s == Up || s == Down) s = _getch();
						if (s >= 'A' && s <= 'z' || s >= '0' && s <= '9') {
							if (temp.length() < 15) {
								if (s >= 'a' && s <= 'z') s = s - 32;
								temp.push_back(s);
								gotoxy(tdX - 1, tdY); cout << s; ++tdX;
							}
						}
						else if (s == Backspace) {
							if (temp.length() > 0) {
								temp.erase(temp.length() - 1, 1);
								gotoxy(tdX - 1, tdY); cout << "\b \b"; --tdX;
							}
						}
						else if (s == Enter) {
						
							int tdX1 = 150, tdY1 = 25;
							int i;
							for (i = 0; i < listSVTL->soSV; i++) {
								if (temp == listSVTL->Data[i].maSV) {
									Nocursortype();
									inThongTin_1_sinhvien_diemthi(listSVTL->Data[i],tdX1,tdY1,mh.maMH);
									
									//flag = 1;
									break;
								}
							}
							
						}
						else if (s == Esc) {
							xoa_inThongTin_1_sinhvien_diemthi(145, 25);
							tdX = 101, tdY = 1;
							
							gotoxy(tdX, tdY); cout << "                ";
							flag = 1;
							break;
							
						}
					}
				}
			}
			if (flag) {
				check = 1;
				break;
			}
		}

	}
	delete[] listSVTL;
}
void inDanhSachLop_diemthi(MONHOC mh) {
	system("cls");
	ClearConsoleToColors(15, 16);
	bool check = 0;

	while (1) {
		khung();
		const int x = 80, y = 3;
		bool check = 0;
		nutEsc();
		khungmonhoc(x - 10, y - 2, y + listL.soLop * 2 + 4, 85);	
		gotoxy(x, y); cout << "SO LUONG LOP: ";
		gotoxy(x + 15, y); cout << listL.soLop;
		gotoxy(x, y + 2); cout << "TEN LOP";
		gotoxy(x + 40, y + 2); cout << "MA LOP";
		int max = 5;
		int min = max + y;
		int tdY = min;
		int tdX = x;
		int tdYcu = tdY;

		for (int i = 0; i < listL.soLop; i++) {
			gotoxy(x, y + max); cout << listL.Data[i].tenLop;
			gotoxy(x + 40, y + max); cout << listL.Data[i].maLop;
			max = max + 2;
		}

		string khoangtrang = "                   ";
		string lop[2];
		thanhsangMoi(x, tdY, listL.Data[0].tenLop, listL.Data[0].maLop);
		int flag = 0;
		while (1) {
			Nocursortype();
			char s;
			if (_kbhit()) {
				s = _getch();

				tdYcu = tdY;

				if (s == Up) {
					if (tdY == min) tdY = max + y - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2 + y) tdY = min;
					else tdY = tdY + 2;
				}
				flag = 1;
				if (s == Esc) {
					system("cls");
					ClearConsoleToColors(15, 16);
					check = 1;
					return;
				}
				if (s == Enter) {

					inSinhVien_diemthi(listL.Data[(tdY - min) / 2], mh);
					if (tdY >= min) {
						tdYcu = tdYcu - 2;
					}
					break;

				}
				thanhsang_lop(tdX, tdY, tdYcu, min);
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
}
void monHoc_diemthi() {
	system("cls");
	ClearConsoleToColors(15, 16);
	bool check = 0;
	const int x = 80, y = 3;
	int max = 5 + y;
	int min = max;
	int tdY = max;
	int tdX = x;
	int tdYcu = tdY;
	while (1) {
		khungmonhoc(x - 20, y - 2, y + listMH.soMH * 2 + 4, 85);
		Nocursortype();
		nutEsc();

		gotoxy(x, y); cout << "SO LUONG MON HOC: ";
		gotoxy(x + 18, y); cout << listMH.soMH;
		gotoxy(x, y + 2); cout << "TEN MON HOC";
		gotoxy(x + 40, y + 2); cout << "MA MON HOC";
		max = 5 + y;
		for (int i = 0; i < listMH.soMH; i++) {
			gotoxy(x, max); cout << listMH.danhSach[i].tenMH;
			gotoxy(x + 40, max); cout << listMH.danhSach[i].maMH;
			max = max + 2;
		}
		thanhsangMoi(x, tdY, listMH.danhSach[(tdY - min) / 2].tenMH, listMH.danhSach[(tdY - min) / 2].maMH);
		while (1) {
			char s;
			if (_kbhit()) {
				s = _getch();
				tdYcu = tdY;
				if (s == Up) {
					if (tdY == min) tdY = max - 2;
					else tdY = tdY - 2;
				}
				if (s == Down) {
					if (tdY == max - 2) tdY = min;
					else tdY = tdY + 2;
				}

				if (s == Esc) {
					check = 1;
					break;
				}
			
				if (s == Enter) {
					inDanhSachLop_diemthi(listMH.danhSach[(tdY-min)/2]);
					tdY = min;
					break;
				}

				Nocursortype();
				thanhsang_monhoc(x, tdY, tdYcu, min);
			}
		}
		if (check == 1) {
			system("cls");
			break;
		}
	}
}
void inBangDiemMonHocCua1Lop() {
	monHoc_diemthi();
}


// GHI FILE 
void demSoNodeCH(nodeCAUHOI* p, int& dem)
{
	if (p == NULL) return;
	else {
		if (p != NULL) {
			++dem;
			demSoNodeCH(p->pLeft, dem);
			demSoNodeCH(p->pRight, dem);
		}
	}

}
void demSoNodeCHtheoMH(nodeCAUHOI* p, int& dem, string maMH)
{
	if (p == NULL) return;
	else {
		if (p != NULL) {

			if (p->data.maMH == maMH) {
				++dem;
			}
			demSoNodeCHtheoMH(p->pLeft, dem, maMH);
			demSoNodeCHtheoMH(p->pRight, dem, maMH);
		}
	}

}
int demSoMonThi(listDIEMTHI listDT){
		int count = 0;
		if (listDT.pHead == NULL) return 0;
		if (listDT.pHead != NULL) {
			for (listDT.pHead; listDT.pHead != NULL; listDT.pHead = listDT.pHead->pNext) {
				++count;
			}
			return count;
		}
}
void ghiDiemSinhVien(ofstream & fileout, DIEMTHI dt)
{
		fileout << dt.maMH << endl;
		fileout << dt.diem << endl;
}
void ghiListDiem(ofstream & fileout, listDIEMTHI listDT)
{
		for (nodeDIEMTHI* k = listDT.pHead; k != NULL; k = k->pNext) {
			ghiDiemSinhVien(fileout, k->data);
		}
}
void ghiDanhSachSinhVien(ofstream & fileout, listSINHVIEN listSV)
{
	if (listSV.pHead == NULL) {
		fileout << 0 << endl;
	}
	else {
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
		// giai phong vung nho
		nodeSINHVIEN* k = NULL;
		while (listSV.pHead != NULL) {
			k = listSV.pHead;
			listSV.pHead = listSV.pHead->pNext;
			delete k;
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
void ghiMonHoc(ofstream & fileout, MONHOC mh)
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
void ghiThongTinCauHoi(ofstream & fileout, CAUHOI data)
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
void ghiCauHoi(ofstream & fileout, nodeCAUHOI * root)
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
			fileout.close();
			return;
		}
		else {
			fileout << soCH << endl;
			ghiCauHoi(fileout, rootCH);
		}
		fileout.close();
}
void ghiRandomID() {
	ofstream fileout;
	fileout.open("idRanDom.txt", ios_base::trunc);
	fileout << count_id << endl;
	int i;
	for (i = 0; i < count_id; i++) {
		fileout << id[i] << endl;
	}
	delete[] id;
	id = nullptr;
	fileout.close();
}
void ghiFile(){
	ghiRandomID();
	ghiListMonHoc();
	ghiListCauHoi();
	ghiFileLop();
}


	// CHUC NANG CUA GV
void menuGV(int tdX, int tdY, string temp[]) {

	int X = tdX - 10;
	gotoxy(X - 40, Y - 10); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	gotoxy(X-40, Y - 9);    cout << "oo                                                                                                       oo";
	gotoxy(X- 40, Y - 8);   cout << "oo                                        CAC CHUC NANG CUA GIAO VIEN                                    oo";
	gotoxy(X- 40, Y - 7);   cout << "oo                                                                                                       oo";
	gotoxy(X- 40, Y - 6);   cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	int max = -1;
	for (int i = 0; i < 7; i++) {
		box_hcn(X, Y + max);
		max = max + 2;
	}
	max = 0;
	for (int i = 0; i < 7; i++) {
		gotoxy(X, Y + max); cout << temp[i];
		max = max + 2;
	}
}
void GV() {
	system("cls");
	bool check = 0;
	string temp[7] = 
	{
			"THI TRAC NGHIEM"
			,"LOP"
			,"SINH VIEN"
			, "MON HOC"
			, "CAU HOI"
			,"IN BANG DIEM"
			,"THOAT"
	};

	
	while (1) {
		
		ClearConsoleToColors(15, 16);
		khung();
		const int x = 16;
		const int y = 9;
		int tdX = 100, tdY = 20;
		int tdYcu;
		const int X = tdX - 2, Y = tdY;
		
		int min = Y;
		int max = Y + 12;

		menuGV(tdX - 2, tdY, temp);
		if (tdY == min) {
			tdYcu = max;
		}
		else tdYcu = tdYcu - 2;
		int color = 8;
		tdX = tdX - 10;
		thanhsang_menu(tdX - 2, tdY, tdYcu, temp, min, color);
		bool flag = 0;
		
		while (1) {


			Nocursortype();
			char s;

			if (_kbhit()) {
			
				s = _getch();

				tdYcu = tdY;

				if (s == Up) {
				
					if (tdY == min) {
						tdY = max;
					}
					else tdY -= 2;
				}
				else if (s == Down) {
					
					if (tdY == max) {
						tdY = min;
					}
					else tdY += 2;

				}

				else if (s == Enter) {
					if (tdY == Y)           thiTracNghiemChoGV();
					if (tdY == Y + 2)       nhapLop();
					else if (tdY == Y + 4)  nhapSinhVien();
					else if (tdY == Y + 6)  monHoc();
					else if (tdY == Y + 8)  nhapCauHoi();
					else if (tdY == Y + 10) inBangDiemMonHocCua1Lop();
					if (tdY == Y + 12) check = 1;
					ClearConsoleToColors(15, 16);
					flag = 1;
				}
			
				thanhsang_menu(tdX - 2, tdY, tdYcu, temp, min, color);
				
				++color;
				if (color == 11) color = 12;
				if (color > 13) color = 8;
			
				
			}
			
			if (flag == 1) break;
		}
		if (check == 1) break;
	}
	ClearConsoleToColors(15, 16);
}


	// CHUC NANG SV
void SV(SINHVIEN & data){
	thiTracNghiemChoSV(data);
}
void logoPtit() {
	Nocursortype();
	setColor(15);
	int x = 85, y = 20;
	gotoxy(X - 30, Y - 11);  cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	gotoxy(X - 30, Y - 10);  cout << "oo                                                                                                      oo";
	gotoxy(X - 30, Y - 9);   cout << "oo                                DE TAI       : CHUONG TRINH THI TRAC NGHIEM                           oo";
	gotoxy(X - 30, Y - 8);   cout << "oo                                HO VA TEN    : LE DANG KHANH                                          oo";
	gotoxy(X - 30, Y - 7);   cout << "oo                                MA SINH VIEN : N19DCCN089                                             oo";
	gotoxy(X - 30, Y - 6);   cout << "oo                                                                                                      oo";
	gotoxy(X - 30, Y - 5);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	setColor(12);
	gotoxy(x, y + 0);  cout << "                                         \n";
	gotoxy(x, y + 1);  cout << "                                         \n";
	gotoxy(x, y + 2);  cout << "                          ,*//,          \n";
	gotoxy(x, y + 3);  cout << "                     .(##########(       \n";
	gotoxy(x, y + 4);  cout << "                  .*##/,     ,(####,     \n";
	gotoxy(x, y + 5);  cout << "                (*#(            /###     \n";
	gotoxy(x, y + 6);  cout << "             .#,(                *##,    \n";
	gotoxy(x, y + 7);  cout << "            /(/                   ##/    \n";
	gotoxy(x, y + 8);  cout << "          ,#,                     /#*    \n";
	gotoxy(x, y + 9);  cout << "         /#,                      *#.    \n";
	gotoxy(x, y + 10); cout << "        (#                        /#     \n";
	gotoxy(x, y + 11); cout << "       (#.                        #/     \n";
	gotoxy(x, y + 12); cout << "      ##*                     .   (      \n";
	gotoxy(x, y + 13); cout << "     (##                     .,  /       \n";
	gotoxy(x, y + 14); cout << "    *##.                    .*. ..       \n";
	gotoxy(x, y + 15); cout << "    ##/  ####### (######*./***/, ####### \n";
	gotoxy(x, y + 16); cout << "   (##   ##.  (##   ##   .*//,     /#(   \n";
	gotoxy(x, y + 17); cout << "  .###   ##(####*   ##  .*.*(,     /#(   \n";
	gotoxy(x, y + 18); cout << "  /###   ##,.       ##   .#*##     /#(   \n";
	gotoxy(x, y + 19); cout << "  ####   ##.        ##  *##*##     /#(   \n";
	gotoxy(x, y + 20); cout << "  ####   ..         . ,###/ .            \n";
	gotoxy(x, y + 21); cout << "  (###/             .####.               \n";
	gotoxy(x, y + 22); cout << "  .####(         .#####.                 \n";
	gotoxy(x, y + 23); cout << "   .#####,    .(####(                    \n";
	gotoxy(x, y + 24); cout << "    .(,,.,/######/                       \n";
	gotoxy(x, y + 25); cout << "       .*(((/,                           \n";
	gotoxy(x, y + 26); cout << ".,,,,,,,,,,,,,,,,,,/(/,,,,,,,,,,,,,,,,,,,\n";
	gotoxy(x, y + 27); cout << "*###################*###################(\n";
}
void dangNhap() {
	logoPtit();
	Sleep(1500);
	system("cls");
	SetColor(15);
	ClearConsoleToColors(15, 16);
	string tk, mk;
	bool check = 0;
	int tdX = 96, tdY = 20;
	int tdX1 = tdX;
	int tdX2 = tdX;
	while (1) {
	
		khung();
		gotoxy(X - 40, Y - 10); cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
		gotoxy(X - 40, Y - 9);  cout << "oo                                                                                                       oo";
		gotoxy(X - 40, Y - 8);  cout << "oo                                      CHUONG TRINH THI TRAC NGHIEM                                     oo";
		gotoxy(X - 40, Y - 7);  cout << "oo                                                                                                       oo";
		gotoxy(X - 40, Y - 6);  cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
		gotoxy(X, Y);     cout << "Tai khoan";
		gotoxy(X, Y + 2); cout << "Mat khau";
		box_hcn(X, Y + 3);
		gotoxy(X, Y + 4); cout << "Nhan Enter de dang nhap";
		nutEsc();


		box_dangnhap(X - 1, Y - 2, 50);
		gotoxy(X + 16, Y + 2); cout << mk;
		gotoxy(X + 16, Y); cout << tk;
	

		
		//gotoxy(tdX1, Y);
		while (1) {
		
			Cursortype();
			char s;
			if (_kbhit()) {   // bat su kien tu ban phim

				s = _getch();
				if (s == Esc) {
					check = 1;
					break;
				}
			
				if (s == Up) {
					if (tdY == Y) { tdY = Y; }
					else tdY-=2;
					gotoxy(tdX1, tdY);
				}
				else if (s == Down) {
					if (tdY == Y + 2) { tdY = Y + 2; }
					else tdY+=2;
					gotoxy(tdX2, tdY);
				}
				else if (s == Left || s == Right) {
					s = _getch();
				}

				else if (s == Backspace) {
					if (tk.length() > 0) {
						if (tdY == Y) {
							tk.erase(tk.length() - 1, 1); --tdX1;
							cout << "\b \b";
							
						}
					}
					if (mk.length() > 0) {
						if (tdY == Y + 2) {
							mk.erase(mk.length() - 1, 1); --tdX2;
							cout << "\b \b";
							tdX = tdX2;
						}
					}
				}

				else if (s >= 'A' && s <= 'z' || s >= '0' && s <= '9') {

					if (tdY == Y) { // tai khoan
						if (tk.length() >= 0 && tk.length() < 20) {
							if (s >= 'a' && s <= 'z') s = s - 32;
							tk.push_back(s);
							gotoxy(tdX1, tdY); cout << s;
							++tdX1;
							tdX = tdX1;
						}
				

					}

					else if (tdY == Y + 2) { // mat khau

						if (mk.length() >= 0 && mk.length() < 20) {
							if (s >= 'a' && s <= 'z') s = s - 32;
							mk.push_back(s);
							gotoxy(tdX2, tdY); cout << s; 
							Sleep(150);
							gotoxy(tdX2, tdY); cout << "*";
							++tdX2;
							tdX = tdX2;
						}
						
						else if (s == Esc) {
							check = 1;
							break;
						}

					}
				}
				
				if (s == Enter) {

					break;
				}
				

			    else if (s == Esc) {
				check = 1;
				break;
			    }
			}
		}
		
		if (check == 1) {
			system("cls");
			gotoxy(X - 30, Y - 11);  cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
			gotoxy(X - 30, Y - 10);  cout << "oo                                                                                                      oo";
			gotoxy(X - 30, Y - 9);   cout << "oo                            DE TAI : CHUONG TRINH THI TRAC NGHIEM                                     oo";
			gotoxy(X - 30, Y - 8);   cout << "oo                                  HO VA TEN : LE DANG KHANH                                           oo";
			gotoxy(X - 30, Y - 7);   cout << "oo                                  MA SINH VIEN : N19DCCN1089                                          oo";
			gotoxy(X - 30, Y - 6);   cout << "oo                                                                                                      oo";
			gotoxy(X - 30, Y - 5);   cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
			logoPtit();
			break;
		}
		bool checkdangnhap = 0;
		if (tk == "GV" && mk == "GV") {
			GV();
			checkdangnhap = 1;
			tdY = Y;
			tk = "GV", mk = "GV";
		
		}
		else if (1) {
			for (int i = 0; i < listL.soLop; i++) {
				for (nodeSINHVIEN* k = listL.Data[i].ListSV.pHead; k != NULL; k = k->pNext) {
					if (tk.length() < 1 || mk.length() < 1) {
						checkdangnhap = 0;
					}
					else {
						if (k->data.maSV == tk && k->data.password == mk) {
							system("cls");
							SV(k->data);
							checkdangnhap = 1;
							tdY = Y;
							tk = k->data.maSV;
							mk = k->data.password;
							
							break;
						}
					}
				}
			}
		}
		if(checkdangnhap == 0){
			tdY = Y;
			Nocursortype();
			gotoxy(X, Y + 6); cout << "Tai khoan hoac mat khau khong dung !, vui long nhap lai";
			Sleep(1000);
			gotoxy(X, Y + 6); cout << "                                                           ";
		}
	}
}


int main() {
	ClearConsoleToColors(15, 16);
	resizeConsole(1800,1000);
	
	LoadDuLieuTuFile();
	dangNhap();
	ghiFile();
	//thucHien();
	
}





