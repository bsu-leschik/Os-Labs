#include <Windows.h>
#include <iostream>

#define BUFFER_SIZE 512

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hNamedPipe;
	char buffer[BUFFER_SIZE];

	DWORD cRead, cWrite;

	hNamedPipe = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\$MyPipe$"),
		PIPE_ACCESS_DUPLEX, //������ � ������
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE, BUFFER_SIZE, 20, NULL);


	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "������ �������� ������ !!!" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "������ �������. �������� ����������....\n\n";

	BOOL connect = ConnectNamedPipe(hNamedPipe, NULL);

	if (!connect) {
		std::cout << "������ ���������� � �������\n\n";
		system("pause");
		return 1;
	}

	while (connect) {
		std::cout << "���������� ������������. �������� ������...\n\n";
		while (true) {
			if (ReadFile(hNamedPipe, buffer, BUFFER_SIZE, &cRead, NULL)) {
				if (!WriteFile(hNamedPipe, buffer, strlen(buffer) + 1, &cWrite, NULL)) {
					break;
				}

				printf("�������: <%s>\n", buffer);

				if (!strcmp("�����", buffer)) {
					char text[] = "������� �����: ";
					WriteFile(hNamedPipe, text, strlen(text) + 1, &cWrite, NULL);

					ReadFile(hNamedPipe, buffer, BUFFER_SIZE, &cRead, NULL);

					float sum = 0.0f;
					char* token = strtok(buffer, " ");
					while (token != nullptr) {
						sum += atof(token);
						token = strtok(NULL, " ");
					}

					sprintf(buffer, "%f", sum);
					WriteFile(hNamedPipe, buffer, strlen(buffer) + 1, &cWrite, NULL);
				}

				if (!strcmp("�����", buffer)) {
					std::cout << "������ ����������.\n\n";
					DisconnectNamedPipe(hNamedPipe);
					break;
				}
					
			}
			else {
				std::cout << "������ ����������.\n\n";
				DisconnectNamedPipe(hNamedPipe);
				break;
			}
		}
		connect = ConnectNamedPipe(hNamedPipe, NULL);
	}

	CloseHandle(hNamedPipe);
	return 0;
}