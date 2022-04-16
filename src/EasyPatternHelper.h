#pragma once
#include <string>
#include <vector>

struct Item {
  int Data;
  bool Wildcard;
};

struct TUChar {
  Item Item1;
  Item Item2;
};

typedef std::vector<TUChar> PatternArray;
class PatternHelper {
public:
  static std::string Format(const std::string &data);
  static PatternArray Transform(const std::string &data);

  static bool Find(const unsigned char *data, size_t length,
                   const PatternArray &_pattern, long long &offsetFound);
  static bool Find(const unsigned char *data, size_t length,
                   const PatternArray &_pattern) {
    long long FoundOffset;
    return Find(data, length, _pattern, FoundOffset);
  }
  static bool Find(const std::string &data, const PatternArray &_pattern,
                   long long &offsetFound) {
    return Find((const unsigned char *)data.c_str(), data.length(), _pattern,
                offsetFound);
  }
  static bool Find(const std::string &data, const PatternArray &_pattern) {
    long long FoundOffset;
    return Find(data, _pattern, FoundOffset);
  }

private:
  static int HexChToInt(const unsigned char ch) {
    if (ch >= '0' && ch <= '9')
      return ch - '0';
    else if (ch >= 'A' && ch <= 'F')
      return ch - 'A' + 10;
    else if (ch >= 'a' && ch <= 'f')
      return ch - 'a' + 10;
    return -1;
  }

  static bool MatchByte(const unsigned char b, const TUChar &p) {
    int N1, N2;

    if (!p.Item1.Wildcard) {
      N1 = b >> 4;
      if (N1 != p.Item1.Data)
        return false;
    }

    if (!p.Item2.Wildcard) {
      N2 = b & 0xF;
      if (N2 != p.Item2.Data)
        return false;
    }

    return true;
  }
};
