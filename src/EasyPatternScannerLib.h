#pragma once

namespace EasyPatternScannerLib {
using pfnReadCallback = bool (*)(unsigned int PID, void *BaseAddress,
                                 void *Buffer, size_t Size);
class PatternScanner {
private:
  pfnReadCallback mReadCallback = nullptr;

public:
  void SetReadCallback(pfnReadCallback Callback);
  bool SearchSig(unsigned int PID, void *StartAddr, size_t Size,
                 const char *Sig,
                 /*OUT*/ void **ResultAddr);
};

} // namespace EasyPatternScannerLib
