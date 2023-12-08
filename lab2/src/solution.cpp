#include "../include/solution.h"

void lab2::solution(std::vector<std::string>& vec, uint32_t threads_count) {
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  std::vector<WorkerResult> res_vec; // guarded by mutex

  pthread_t* threads = static_cast<pthread_t*>(malloc(threads_count * sizeof(pthread_t)));
  MessageToThread* msgs = static_cast<MessageToThread*>(malloc(threads_count * sizeof(MessageToThread)));

  clock_t begin = clock();
  auto start = std::chrono::steady_clock::now();

  size_t left = 0;
  for (size_t i = 0; i < threads_count; ++i) {
    size_t right = left + (vec.size() + threads_count - 1) / threads_count;
    
    if (right >= vec.size()) {
      right -= right - vec.size();
    }

    msgs[i].left = left;
    msgs[i].right = right;
    msgs[i].res_vec = &res_vec;
    msgs[i].vec = &vec;
    msgs[i].mutex = &mutex;

    left = right;

    if (pthread_create(&threads[i], NULL, lab2::worker_func, (void*)&msgs[i]) != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < threads_count; ++i) {
    if (pthread_join(threads[i], NULL) < 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  pthread_mutex_destroy(&mutex);
  free(threads);
  free(msgs);

  clock_t end = clock();
  auto chrono_end = std::chrono::steady_clock::now();

  int64_t chrono_time = std::chrono::duration_cast<std::chrono::milliseconds>(chrono_end - start).count();
  double clock_time = static_cast<double>((end - begin) / CLOCKS_PER_SEC * 1000);

  std::cout << "Elapsed time in milliseconds(clock): " << clock_time << " ms" << std::endl;

  std::cout << "Elapsed time in milliseconds(chrono): " << chrono_time << " ms" << std::endl;

  lab2::save_metrics("/home/b_eli/Desktop/MAI_OS/lab2/analytics/metrics.txt",
   chrono_time,
   clock_time,
   threads_count);

  std::string arithmetic_mean = lab2::calculate_arithmetic_mean(res_vec, vec.size());
  std::cout << arithmetic_mean << std::endl;
}

void lab2::save_metrics(const std::string& file_name, const auto& elapsed_time_chrono, auto& elapsed_time_clock, uint64_t worker_count) {
  std::ofstream file(file_name, std::ios::app);
  file << elapsed_time_chrono << ' ' <<  elapsed_time_clock << ' ' << worker_count << std::endl;
}

void* lab2::worker_func(void* args) {
  MessageToThread* msg = static_cast<MessageToThread*>(args);
  std::string sum = "0";

  for (size_t i = msg->left; i < msg->right; ++i) {
    sum = calculate_sum(sum, msg->vec->at(i));
  }

  WorkerResult res;
  res.sum = sum;

  pthread_mutex_lock(msg->mutex);
  msg->res_vec->push_back(res);
  pthread_mutex_unlock(msg->mutex);

  pthread_exit(NULL);
}

std::string lab2::calculate_sum(const std::string& str1, const std::string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();

    int maxLength = (len1 > len2) ? len1 : len2;

    std::string paddedStr1(maxLength - len1, '0');
    std::string paddedStr2(maxLength - len2, '0');
    paddedStr1 += str1;
    paddedStr2 += str2;

    std::string result;
    int carry = 0;

    for (int i = maxLength - 1; i >= 0; --i) {
        int digit1 = charToDigit(paddedStr1[i]);
        int digit2 = charToDigit(paddedStr2[i]);

        if (digit1 == -1 || digit2 == -1) {
            return "Error: Invalid input";
        }

        int sum = digit1 + digit2 + carry;
        carry = sum / 16;
        result = digitToChar(sum % 16) + result;
    }

    if (carry > 0) {
        result = digitToChar(carry) + result;
    }

    return result;
}

int lab2::charToDigit(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
      return 10 + (c - 'A');
  } else if (c >= 'a' && c <= 'f') {
      return 10 + (c - 'a');
  } else {
      return -1;
  }
}

char lab2::digitToChar(int digit) {
  if (digit >= 0 && digit <= 9) {
    return static_cast<char>(digit + '0');
  } else {
    return static_cast<char>(digit - 10 + 'A');
  }
}

std::string lab2::calculate_arithmetic_mean(const std::vector<WorkerResult>& vec, size_t size) {
  std::string sum = "0";

  for (auto& e : vec) {
    sum = calculate_sum(sum, e.sum);
  }

  return sum;
}
