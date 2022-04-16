#pragma once

namespace EasyPatternScannerLib {
using pfnRPMCallback = bool (*)(unsigned int PID, void *BaseAddress,
                                void *Buffer, size_t Size);
class PatternScanner {
private:
  pfnRPMCallback mPfnRPMCallback = nullptr;

public:
  void SetRPMCallback(pfnRPMCallback Callback);
  bool SearchSig(unsigned int PID, void *StartAddr, size_t Size, char *Sig,
                 /*OUT*/ void **ResultAddr);
};

} // namespace EasyPatternScannerLib
