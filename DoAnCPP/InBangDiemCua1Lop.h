#include"LoadFile.h"
#pragma once

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