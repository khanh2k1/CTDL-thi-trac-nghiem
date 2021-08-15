#include"LoadFile.h"

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
	int* idMH = new int[max + 10];
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