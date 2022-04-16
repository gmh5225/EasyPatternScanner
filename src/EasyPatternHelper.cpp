#include "EasyPatternHelper.h"

std::string PatternHelper::Format(const std::string &str) {
  std::string tempRes;
  size_t len = str.length();
  for (size_t i = 0; i < len; i++) {
    char ch = str[i];
    if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') ||
        (ch >= 'a' && ch <= 'f') || (ch == '?'))
      tempRes = tempRes + ch;
  }

  return tempRes;
}

PatternArray PatternHelper::Transform(const std::string &str) {
  std::string _pattern = Format(str);
  size_t _length = _pattern.length();

  if (_length == 0)
    return PatternArray();

  PatternArray tempRes;

  if (_length % 2 != 0) {
    _pattern = _pattern + '?';
    _length++;
  }

  TUChar newbyte;
  size_t j = 0;

  for (size_t idx = 0; idx < _length; idx++) {
    char ch = _pattern[idx];

    if (ch == '?') {
      if (j == 0)
        newbyte.Item1.Wildcard = true;
      else
        newbyte.Item2.Wildcard = true;
    } else {
      if (j == 0) {
        newbyte.Item1.Wildcard = false;
        newbyte.Item1.Data = (HexChToInt(ch) & 0xF);
      } else {
        newbyte.Item2.Wildcard = false;
        newbyte.Item2.Data = (HexChToInt(ch) & 0xF);
      }
    }

    j++;
    if (j == 2) {
      j = 0;
      tempRes.push_back(newbyte);
    }
  }

  return tempRes;
}

bool PatternHelper::Find(const unsigned char *Data, size_t length,
                         const PatternArray &_pattern, long long &offsetFound) {
  offsetFound = -1;

  if (Data == NULL || _pattern.empty())
    return false;

  size_t patternSize = _pattern.size();
  if (length == 0 || patternSize == 0)
    return false;

  size_t i = 0, pos = 0;
  while (i < length) {
    if (MatchByte(Data[i], _pattern[pos])) {
      pos++;
      if (pos == patternSize) {
        offsetFound = i - patternSize + 1;
        return true;
      }
    } else {
      i -= pos;
      pos = 0;
    }

    i++;
  }

  return false;
}
