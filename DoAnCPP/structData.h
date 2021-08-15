#pragma once
#include<string>
using namespace std;
// danh sach mon hoc
struct CAUHOI {	
	int id = -1;
	string maMH;
	string ND;
	string A;
	string B;
	string C;
	string D;
	char DA = NULL;
};

struct nodeCAUHOI 
{
	CAUHOI data;
	nodeCAUHOI* pLeft;
	nodeCAUHOI* pRight;
	
}; 

struct MONHOC 
{
	string maMH;
	string tenMH;
};

struct listMONHOC
{
	const int maxSize = 27;
	int soMH = 0;
	MONHOC* danhSach = new MONHOC[maxSize]; // MONHOC danhSach[maxSize];
	int soCH = 0;
};

struct DIEMTHI
{
	string maMH;
	float diem = -1;
};

struct nodeDIEMTHI
{
	DIEMTHI data;
	nodeDIEMTHI* pNext;
};

struct listDIEMTHI
{
	nodeDIEMTHI* pHead;
	nodeDIEMTHI* pTail;
};

struct SINHVIEN
{
	string ho;
	string ten;
	string gioiTinh;
	string maSV;
	string password;
	listDIEMTHI listDT;
};

struct nodeSINHVIEN
{
	SINHVIEN data;
	nodeSINHVIEN* pNext;;
};

struct listSINHVIEN
{
	nodeSINHVIEN* pHead;
	nodeSINHVIEN* pTail;
};

struct LOP
{
	string maLop;
	string tenLop;
	listSINHVIEN ListSV;
};

struct listLOP
{
	const int maxSize = 25;
	LOP* Data = new LOP[maxSize];
	int soLop = 0;
};

struct DAPAN {
	CAUHOI data;
	char DA_USER = NULL;
};

struct listDAPAN {
	const int max = 10000;
	DAPAN* da = new DAPAN[max];
	int socauthi = 0;
};


struct listSINHVIENTHEOLOP {
	const int max = 10000;
	SINHVIEN* Data = new SINHVIEN[max];
	int soSV = 0;
};



