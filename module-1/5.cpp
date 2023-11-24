/*
5_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли
собраться вместе. Для этого в этот момент каждому из них должно было  уже
исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих
Людей. Необходимо получить максимальное количество современников. В день 18летия
человек уже может принимать участие в собраниях, а в день 80летия и в день
смерти уже не может.
*/

#include <functional>
#include <iostream>

struct Date {
  Date() : day_(0), month_(0), year_(0), start(true), target(true) {}
  explicit Date(int day, int month, int year, bool start);
  int day_, month_, year_;
  bool start, target;
};

Date::Date(int day, int month, int year, bool start) {
  day_ = day;
  month_ = month;
  year_ = year;
  start = true;
  target = true;
}

class DateComparator {
 public:
  bool operator()(const Date& first, const Date& second) {
    if (first.year_ < second.year_)
      return true;
    else if (first.year_ > second.year_)
      return false;

    if (first.month_ < second.month_)
      return true;
    else if (first.month_ > second.month_)
      return false;

    if (first.day_ < second.day_)
      return true;
    else if (first.day_ > second.day_)
      return false;

    return false;
  }
};

template <typename T, typename Comparator = std::less<T>>
void merge(T* first, int firstLen, T* second, int secondLen, T* result,
           Comparator cmp = Comparator()) {
  int i = 0;
  int j = 0;
  int resultLen = firstLen + secondLen;

  for (int k = 0; k < resultLen; k++) {
    if (j == secondLen) {
      result[k] = first[i];
      i++;
      continue;
    } else if (i == firstLen) {
      result[k] = second[j];
      j++;
    } else if (cmp(first[i], second[j])) {
      result[k] = first[i];
      i++;
      continue;
    } else if (cmp(second[j], (first[i]))) {
      result[k] = second[j];
      j++;
    } else if (second[j].start == true && first[i].start == false) {
      result[k] = first[i];
      i++;
    } else if (second[j].start == false && first[i].start == true) {
      result[k] = second[j];
      j++;
    } else {
      result[k] = second[j];
      j++;
    }
  }
}

template <typename T, typename Comparator = std::less<T>>
void mergeSort(T* arr, int length, Comparator cmp = Comparator()) {
  if (length <= 1) {
    return;
  }
  int firstLen = length / 2;
  int secondLen = length - firstLen;

  mergeSort(arr, firstLen, cmp);
  mergeSort(arr + firstLen, secondLen, cmp);

  T* result = new T[length];

  merge(arr, firstLen, arr + firstLen, secondLen, result, cmp);

  for (int i = 0; i < length; i++) {
    arr[i] = result[i];
  }

  delete[] result;
}

int getAge(Date start, Date end) {
  int age = end.year_ - start.year_ - 1;
  if (end.month_ > start.month_ ||
      (end.month_ == start.month_ && end.day_ >= start.day_))
    age++;
  return age;
}

int main(int argc, const char* argv[]) {
  int n = 0;
  std::cin >> n;
  int size = n * 2;
  DateComparator cmp;

  Date* dates = new Date[size];
  int i = 0;
  for (int i = 0; i < size; i++) {
    std::cin >> dates[i].day_ >> dates[i].month_ >> dates[i].year_;
    if (i % 2 == 0) {
      dates[i].start = true;
    }
    if (i % 2 == 1) {
      dates[i].start = false;
      int age = getAge(dates[i - 1], dates[i]);
      if (age >= 80) {
        dates[i].year_ -= (age - 80);
        dates[i].day_ = dates[i - 1].day_;
        dates[i].month_ = dates[i - 1].month_;
      }
      if (age < 18) {
        dates[i].target = false;
        dates[i - 1].target = false;
        continue;
      }
      if (age >= 18) {
        dates[i - 1].year_ += 18;
      }
    }
  }

  mergeSort<Date, DateComparator>(dates, size, DateComparator());


  int* counts = new int[size + 1]();
  int j = 1;
  for (int i = 0; i < size; i++) {
    if (dates[i].target) {
      if (dates[i].start == true)
        counts[j] = counts[j - 1] + 1;
      else
        counts[j] = counts[j - 1] - 1;
    }
    j++;
  }

  int maxCount = counts[0];
  for (int p = 0; p < size; p++) {
    if (counts[p] > maxCount) maxCount = counts[p];
  }

  std::cout << maxCount;

  delete[] dates;
  delete[] counts;
  return 0;
}