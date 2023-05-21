#pragma once



void  choice_v() {
    
    char choice;

    switch (choice) {
    case 'a':
        createDatabase();
        break;
    case 'b':
        addRecord();
        break;
    case 'c':
        query();
        break;
    case 'd':
        searchByKey();
        break;
    case 'f':
        displayDatabase();
        break;
    case 'q':
        cout << "�������� ��������� ������." << endl;
        break;
    default:
        cout << "������� ����. ��������� �� ���." << endl;
        break;
    }



}


void controlMenu() {
    char choice;

    cout << "����:" << endl;
    cout << "a. �������� ���� ���� �����" << endl;
    cout << "b. ������ �����" << endl;
    cout << "c. �������� �����" << endl;
    cout << "d. ����� �� ������" << endl;
    cout << "f. ������� ���� �����" << endl;
    cout << "q. ����� � ��������" << endl;
    cout << "��� ����: ";
    cin >> choice;

}



void createDatabase() {
    ofstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "�������� ���� ���� �����." << endl;
        file.close();
    }
    else {
        cout << "������� ��� �������� ���� �����." << endl;
    }
}

void addRecord() {
    Building record;
    cout << "������ ��� ������ ������:" << endl;
    cout << "������: ";
    cin.ignore();
    cin.getline(record.subcontra, N);
    cout << "��� �����: ";
    cin >> record.buildingType;
    cout << "�������: ";
    cin >> record.price;
    cout << "³������ �� ������: ";
    cin >> record.cust.creditInterest;
    cout << "���� ������: ";
    cin >> record.cust.depositAmount;
    record.cust.creditBalance = 0.0;

    ofstream file("database.bin", ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(Building));
        cout << "����� ������ ������ �� ���� �����." << endl;
        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}

void query() {
    float totalUnpaidAmount = 0.0;
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            totalUnpaidAmount += record.cust.creditBalance;
        }

        cout << "����������� ���� ��� �볺���: " << totalUnpaidAmount << endl;

        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}

void searchByKey() {
    int key;
    cout << "������ ���� ��� ������ �� ����� �����: ";
    cin >> key;

    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            if (record.buildingType == key) {
                cout << "�������� �����:" << endl;
                cout << "������: " << record.subcontra << endl;
                cout << "��� �����: " << record.buildingType << endl;
                cout << "�������: " << record.price << endl;
                cout << "³������ �� ������: " << record.cust.creditInterest << endl;
                cout << "���� ������: " << record.cust.depositAmount << endl;
                cout << "����������� ����: " << record.cust.creditBalance << endl;
                cout << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "������ � ����� ������ �� ��������." << endl;
        }

        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}

void displayDatabase() {
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "������ ���� �����:" << endl;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            cout << "������: " << record.subcontra << endl;
            cout << "��� �����: " << record.buildingType << endl;
            cout << "�������: " << record.price << endl;
            cout << "³������ �� ������: " << record.cust.creditInterest << endl;
            cout << "���� ������: " << record.cust.depositAmount << endl;
            cout << "����������� ����: " << record.cust.creditBalance << endl;
            cout << endl;
        }

        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}
