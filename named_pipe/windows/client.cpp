#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <cstring>

#define BUFFER_SIZE 512

int main() {

    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hNamedPipe;
	DWORD cRead, cWrite;

	char buffer[BUFFER_SIZE];

	hNamedPipe = CreateFile(TEXT("\\\\.\\pipe\\$MyPipe$"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);


	while (hNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "��� ������������ ������. \n\n";
		if (!WaitNamedPipe(TEXT("\\\\.\\pipe\\$MyPipe$"), NMPWAIT_USE_DEFAULT_WAIT)) {
			std::cout << "������ �������� ������!!!\n\n";
			system("pause");
			return 1;
		}

		hNamedPipe = CreateFile(TEXT("\\\\.\\pipe\\$MyPipe$"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	}
	std::cout << "����� �������. �������� ������...\n\n";

	while (true) {
		std::cout << "������� �������: ";
		std::cin.getline(buffer, BUFFER_SIZE);

		if (!WriteFile(hNamedPipe, buffer, strlen(buffer) + 1, &cWrite, NULL)) {
			break;
		}

		if (!ReadFile(hNamedPipe, buffer, BUFFER_SIZE, &cRead, NULL)) {
			std::cout << "������ �������!!!\n\n";
			break;
		}
		else {
			printf("����� �� �������: <%s>\n", buffer);
		}

		if (!strcmp("�����", buffer)) {
			ReadFile(hNamedPipe, buffer, BUFFER_SIZE, &cRead, NULL);
			printf("����� �������: %s", buffer);

			std::cin.getline(buffer, BUFFER_SIZE);
			WriteFile(hNamedPipe, buffer, strlen(buffer) + 1, &cWrite, NULL);

			ReadFile(hNamedPipe, buffer, BUFFER_SIZE, &cRead, NULL);
			printf("���������: %s\n", buffer);
		}

		if (!strcmp("�����", buffer)) {
			break;
		}
	}

	CloseHandle(hNamedPipe);
	system("pause");
	return 0;
}