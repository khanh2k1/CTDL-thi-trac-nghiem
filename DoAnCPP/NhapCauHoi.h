#include"LoadFile.h"
#pragma once

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