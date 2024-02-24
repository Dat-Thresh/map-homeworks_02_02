//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <vector>
//#include <random>
//#include <mutex>
//
//using namespace std::chrono_literals;
//std::mutex m,m1;
//int N = 5;
//int bar_size = 13;
//
//void progress(int i) {
//	
//	
//	std::cout <<"\n"<< i + 1 << "\t" << std::this_thread::get_id() << "\t\t";
//	//std::lock_guard<std::mutex> guard(m1);
//	auto start = std::chrono::steady_clock::now();
//	for (int j = 0; j < bar_size; j++) {
//	
//		std::cout << "X";
//		std::this_thread::sleep_for(30ms);
//	}
//	
//	auto finish = std::chrono::steady_clock::now();
//	std::chrono::duration<double> dur = finish - start;
//	std::cout << " " << dur.count() << std::endl;
//	
//	
//}
//
//void task() {
//	std::thread* th = new std::thread[N];
//	//std::lock_guard<std::mutex> g(m);
//	for (int i = 0; i < N; i++) {
//		
//		th[i] = std::thread(progress, std::ref(i));
//	}
//	for (int i = 0; i < N; i++) {
//		th[i].join();
//	}
//}
//
//int main_01() {
//	std::cout << "#\tid\t\tProgress bar\tTime";
//	std::lock_guard<std::mutex> g(m);
//	task();
//	
//	return 0;
//}