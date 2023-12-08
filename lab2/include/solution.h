#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>

namespace lab2 {

struct WorkerResult {
  std::string sum;
};

struct MessageToThread {
  std::vector<std::string>* vec;
  std::vector<WorkerResult>* res_vec; // guarded by mutex
  pthread_mutex_t* mutex;
  size_t left;
  size_t right;
};

int charToDigit(char c);

char digitToChar(int digit);

std::string calculate_arithmetic_mean(const std::vector<WorkerResult>& vec, size_t size);

void solution(std::vector<std::string>& arr, uint32_t threads_count);

std::string calculate_sum(const std::string& str1, const std::string& str2);

void* worker_func(void* args);

void save_metrics(const std::string& file_name, const auto& elapsed_time_chrono, auto& elapsed_time_clock, uint64_t worker_count);

} // namespace lab2

#endif // ifndef SOLUTION_H_INCLUDED