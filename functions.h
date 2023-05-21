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
        cout << "Програма завершила роботу." << endl;
        break;
    default:
        cout << "Невірний вибір. Спробуйте ще раз." << endl;
        break;
    }



}


void controlMenu() {
    char choice;

    cout << "Меню:" << endl;
    cout << "a. Створити нову базу даних" << endl;
    cout << "b. Додати запис" << endl;
    cout << "c. Виконати запит" << endl;
    cout << "d. Пошук за ключем" << endl;
    cout << "f. Вивести базу даних" << endl;
    cout << "q. Вийти з програми" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;

}



void createDatabase() {
    ofstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "Створено нову базу даних." << endl;
        file.close();
    }
    else {
        cout << "Помилка при створенні бази даних." << endl;
    }
}

void addRecord() {
    Building record;
    cout << "Введіть дані нового запису:" << endl;
    cout << "Будівля: ";
    cin.ignore();
    cin.getline(record.subcontra, N);
    cout << "Тип будівлі: ";
    cin >> record.buildingType;
    cout << "Вартість: ";
    cin >> record.price;
    cout << "Відсоток за кредит: ";
    cin >> record.cust.creditInterest;
    cout << "Сума вкладу: ";
    cin >> record.cust.depositAmount;
    record.cust.creditBalance = 0.0;

    ofstream file("database.bin", ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(Building));
        cout << "Запис успішно додано до бази даних." << endl;
        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
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

        cout << "Невиплачена сума всіх клієнтів: " << totalUnpaidAmount << endl;

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}

void searchByKey() {
    int key;
    cout << "Введіть ключ для пошуку за типом будівлі: ";
    cin >> key;

    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            if (record.buildingType == key) {
                cout << "Знайдено запис:" << endl;
                cout << "Будівля: " << record.subcontra << endl;
                cout << "Тип будівлі: " << record.buildingType << endl;
                cout << "Вартість: " << record.price << endl;
                cout << "Відсоток за кредит: " << record.cust.creditInterest << endl;
                cout << "Сума вкладу: " << record.cust.depositAmount << endl;
                cout << "Невиплачена сума: " << record.cust.creditBalance << endl;
                cout << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Записів з таким ключем не знайдено." << endl;
        }

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}

void displayDatabase() {
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "Записи бази даних:" << endl;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            cout << "Будівля: " << record.subcontra << endl;
            cout << "Тип будівлі: " << record.buildingType << endl;
            cout << "Вартість: " << record.price << endl;
            cout << "Відсоток за кредит: " << record.cust.creditInterest << endl;
            cout << "Сума вкладу: " << record.cust.depositAmount << endl;
            cout << "Невиплачена сума: " << record.cust.creditBalance << endl;
            cout << endl;
        }

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}
