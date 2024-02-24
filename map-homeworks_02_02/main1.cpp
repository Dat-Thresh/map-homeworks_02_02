#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <mutex>
#include <sstream>
#include <atomic>

using namespace std::chrono_literals;
std::mutex m, m1;
int N = 5;
int bar_size = 13;

class table {
private:
	std::string* table_ptr;//��������� �� �������
	int check = 0;//������� ����������� �������

public:
	//�����������
	table() {
		table_ptr = new std::string[N + 1];
		table_ptr[0] = "#\tid\t\tProgress bar\tTime\n";
	}

	//����� ������� ����������� �������
	void raise_if_ready() {
		check++;
	}
	//���������� �������� ��������� �������
	int get_check() {
		return check;
	}
	//���������� � ������� ������
	void remember(int i, std::string s) {
		table_ptr[i] += s;
	}
	//�������� �������
	void print_table() {
		for (int i = 0; i < N + 1; i++) {
			std::cout << table_ptr[i]<<std::endl;
		}
	}
	void free_table() {
		delete[] table_ptr;
	}
	/*~table() {
		free_table();
	}*/
};

//��������� ������ ������� ��������� ���������
void progress(int i, table& table) {
	std::stringstream str;
	{
		//���������� ����� �� ������� � ���� ������
		str << std::to_string(i) << "\t" << std::this_thread::get_id() << "\t\t";
		table.remember(i, str.str()); 
	}
	//��������� �����
	auto start = std::chrono::steady_clock::now();
	for (int j = 0; j < bar_size; j++) {
		m.lock();
		table.remember(i, "X");		
		std::this_thread::sleep_for(80ms* (0.5 + rand() % 5 ));
		m.unlock();
		
	}

	//��������� �����
	auto finish = std::chrono::steady_clock::now();
	std::chrono::duration<double> dur = finish - start;
	table.remember(i, " " + std::to_string(dur.count()));
	//����� ������� ����������� �������
	table.raise_if_ready();
	//table.remember(i,"   "+ std::to_string(table.get_check()) + ": check was set");

}
//�������� ������� � ��������� �����, �� ��� ���, ���� �� ��� ������ ���������
void print_while_progress(table& table) {
	while (true) {
		std::this_thread::sleep_for(50ms);
		system("cls");
		table.print_table();
		//std::cout << "Now check is  " << table.get_check() << std::endl;
		if (table.get_check() == N) {
			break;
		}
	}
}

//��������� ������ � ��������� �������� � ������� ������
void task(table& table) {
	std::thread* th = new std::thread[N];
	//m1.lock();
	for (int i = 0; i < N; ++i) {	
		std::this_thread::sleep_for(100ms);

		th[i] = std::thread(progress, std::ref(i), std::ref(table));

	}
	//m1.unlock();
	std::thread pr_th(print_while_progress,std::ref(table));
	
	for (int i = 0; i < N; i++) {
		th[i].join();
	}
	pr_th.join();
	
}

int main() {
	table table;
	//std::cout << "#\tid\t\tProgress bar\tTime";
	task(table);
	//system("cls");
	//table.print_table();
	table.free_table();

	return 0;
}