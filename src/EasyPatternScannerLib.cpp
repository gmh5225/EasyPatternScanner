#include "EasyPatternScannerLib.h"
#include "EasyPatternHelper.h"

namespace EasyPatternScannerLib {

void PatternScanner::SetReadCallback(pfnReadCallback Callback) {
  mReadCallback = Callback;
}

bool PatternScanner::SearchSig(unsigned int PID, void *StartAddr, size_t Size,
                               const char *Sig,
                               /*OUT*/ void **ResultAddr) {

  bool Ret = false;

  if (!StartAddr || !Size || !Sig || !ResultAddr) {
    return false;
  }

  if (nullptr == mReadCallback) {
    return false;
  }

  auto LocalBuf = malloc(Size);
  if (!LocalBuf) {
    return false;
  }

  do {

    Ret = mReadCallback(PID, StartAddr, LocalBuf, Size);
    if (!Ret) {
      break;
    }

    std::string StrSig(Sig);
    PatternArray pattern = PatternHelper::Transform(StrSig);

    long long FoundOffset = 0;
    Ret = PatternHelper::Find((unsigned char *)LocalBuf, Size, pattern,
                              FoundOffset);
    if (Ret) {
      if (ResultAddr) {
        *ResultAddr = (void *)((unsigned char *)StartAddr + FoundOffset);
      }
    }

  } while (0);

  if (LocalBuf) {
    free(LocalBuf);
  }

  return Ret;
}

} // namespace EasyPatternScannerLib
