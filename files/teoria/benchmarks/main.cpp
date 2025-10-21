#include <_stdio.h>
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std::chrono;

#define MAXWORDCOUNT 1000000
#define MAXNUMBERCOUNT 10
#define MAXSTRLEN 32

#define INPUT_DATA_FILE "data.txt"
#define OUTPUT_DATA_FILE "output.txt"

#define START_TIMER() _start = high_resolution_clock::now()

#define TIMESTAMP(text)                                                        \
  _duration =                                                                  \
      duration_cast<milliseconds>(high_resolution_clock::now() - _start);      \
  std::cout << text << ": " << _duration.count() << " ms" << std::endl

int words_count, numbers_count;
char words[MAXWORDCOUNT][MAXSTRLEN];
int numbers[MAXNUMBERCOUNT];
time_point<high_resolution_clock> _start;
duration<long, std::milli> _duration;

inline static int scanInt(FILE *file = stdin) {
  int n = 0;
  int neg = 1;
  char c = getc_unlocked(file);
  if (c == '-')
    neg = -1;
  while (c < '0' || c > '9') {
    c = getc_unlocked(file);
    if (c == '-')
      neg = -1;
  }
  while (c >= '0' && c <= '9') {
    n = (n << 3) + (n << 1) + c - '0';
    c = getc_unlocked(file);
  }
  return n * neg;
}

inline static void writeInt(int v, FILE *file = stdout) {
  static char buf[14];
  int p = 0;
  if (v == 0) {
    putc_unlocked('0', file);
    return;
  }
  if (v < 0) {
    putc_unlocked('-', file);
    v = -v;
  }
  while (v) {
    buf[p++] = v % 10;
    v /= 10;
  }
  while (p--) {
    putc_unlocked(buf[p] + '0', file);
  }
}

inline static int getString(char *buf, FILE *file = stdin) {
  std::string s;
  int c = getc_unlocked(file);

  // Skip leading whitespace
  while (c != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'))
    c = getc_unlocked(file);

  // Read until next whitespace or EOF
  int index = 0;
  while (c != EOF && c != ' ' && c != '\n' && c != '\t' && c != '\r') {
    buf[index++] = static_cast<char>(c);
    c = getc_unlocked(file);
  }

  return index;
}

inline static void putString(const std::string &s, FILE *file = stdout) {
  for (size_t i = 0; i < s.size(); i++)
    putc_unlocked(s[i], file);
}

void generate_data(std::string &&file_name, int words_count,
                   int numbers_count) {
  START_TIMER();
  std::cout << "Generating test file with " << MAXWORDCOUNT << " words and "
            << MAXNUMBERCOUNT << " numbers..." << std::endl;
  std::ofstream out(file_name);

  out << words_count << " " << numbers_count << std::endl;
  for (int i = 0; i < words_count; i++)
    out << "word_" << i << std::endl;

  for (int i = 0; i < numbers_count; i++)
    out << i << std::endl;
  out.close();

  TIMESTAMP("✅Generated data in");
}

void ifstream_no_opt(std::string &&input_file, std::string &&output_file) {
  std::cout << std::endl
            << __FUNCTION__ << std::endl
            << "-----------------------------" << std::endl;

  START_TIMER();
  std::ifstream in(input_file);
  in >> words_count >> numbers_count;
  for (int i = 0; i < words_count; i++)
    in >> words[i];
  for (int i = 0; i < numbers_count; i++)
    in >> numbers[i];
  TIMESTAMP("read");

  START_TIMER();
  std::ofstream out(output_file);
  for (int i = 0; i < words_count; i++)
    out << words[i] << std::endl;
  for (int i = 0; i < numbers_count; i++)
    out << numbers[i] << std::endl;
  TIMESTAMP("write");

  in.close();
  out.close();
}

void ifstream_with_opt(std::string &&input_file, std::string &&output_file) {
  std::cout << std::endl
            << __FUNCTION__ << std::endl
            << "-----------------------------" << std::endl;

  START_TIMER();
  std::ifstream in(input_file);
  in.sync_with_stdio(false);
  in.tie(nullptr);

  in >> words_count >> numbers_count;
  for (int i = 0; i < words_count; i++)
    in >> words[i];
  for (int i = 0; i < numbers_count; i++)
    in >> numbers[i];
  TIMESTAMP("read");

  START_TIMER();
  std::ofstream out(output_file);
  out.sync_with_stdio(false);
  out.tie(nullptr);

  for (int i = 0; i < words_count; i++)
    out << words[i] << std::endl;
  for (int i = 0; i < numbers_count; i++)
    out << numbers[i] << std::endl;
  TIMESTAMP("write");

  in.close();
  out.close();
}

void file_pointer(std::string &&input_file, std::string &&output_file) {
  std::cout << std::endl
            << __FUNCTION__ << std::endl
            << "-----------------------------" << std::endl;

  START_TIMER();
  FILE *in = fopen(input_file.c_str(), "r");
  fscanf(in, "%d %d", &words_count, &numbers_count);

  for (int i = 0; i < words_count; i++)
    fscanf(in, "%s", words[i]);

  for (int i = 0; i < numbers_count; i++)
    fscanf(in, "%d", &numbers[i]);
  TIMESTAMP("read");

  START_TIMER();
  FILE *out = fopen(output_file.c_str(), "w");

  for (int i = 0; i < words_count; i++)
    fprintf(out, "%s", words[i]);

  for (int i = 0; i < numbers_count; i++)
    fprintf(out, "%d", numbers[i]);

  TIMESTAMP("write");

  fclose(in);
}

void fast_io(std::string &&input_file, std::string &&output_file) {
  std::cout << std::endl
            << __FUNCTION__ << std::endl
            << "-----------------------------" << std::endl;

  START_TIMER();
  FILE *in = fopen(input_file.c_str(), "r");
  words_count = scanInt(in);
  numbers_count = scanInt(in);

  for (int i = 0; i < words_count; i++)
    getString(words[i], in);
  for (int i = 0; i < numbers_count; i++)
    numbers[i] = scanInt(in);

  TIMESTAMP("read");

  START_TIMER();

  FILE *out = fopen(output_file.c_str(), "w");
  for (int i = 0; i < words_count; i++)
    putString(words[i], out);

  for (int i = 0; i < numbers_count; i++)
    writeInt(numbers[i], out);

  TIMESTAMP("write");
}

int main(int argc, char *argv[]) {

  generate_data(INPUT_DATA_FILE, MAXWORDCOUNT, MAXNUMBERCOUNT);

  ifstream_no_opt(INPUT_DATA_FILE, OUTPUT_DATA_FILE);

  ifstream_with_opt(INPUT_DATA_FILE, OUTPUT_DATA_FILE);

  file_pointer(INPUT_DATA_FILE, OUTPUT_DATA_FILE);

  fast_io(INPUT_DATA_FILE, OUTPUT_DATA_FILE);
}
