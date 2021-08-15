#include"LoadFile.h"
#include"FormatText.h"
#pragma once

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