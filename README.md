# EasyPatternScanner

## Example
```C++
EasyPatternScannerLib::PatternScanner PS;
PS.SetReadCallback(Your ReadProcessMemory Function);
void* ResultAddr = nullptr;
bool Find = PS.SearchSig(PID, 0x401000, 0x1000, "33??C300", &ResultAddr);
if(Find) {
  printf("ResultAddr=%p\n");
}
```
