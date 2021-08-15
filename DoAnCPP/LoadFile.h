#pragma once

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

#define Enter 13
#define Left 75
#define Right 77
#define Up 72
#define Down 80
#define Space 32
#define Backspace 8
#define Spacebar 32
#define Esc 27
const int chieuDai = 8;
const int MAX_MENU_GV = 10;
const int MAX_MENU_SV = 3;
using namespace std;

//
// Khai bao bien toan cuc
//

listLOP listL;
listMONHOC listMH;
nodeCAUHOI* rootCH;
listSINHVIENDATHI listSVDT;

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