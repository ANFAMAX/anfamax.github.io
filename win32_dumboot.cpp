/*  Alex-Famlonga 2020 : H2T  */

#include <stdint.h>
#include <stdlib.h>
typedef  uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef  int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;
typedef float  F32;
typedef double F64;
typedef U32 B32;

#include <cstdio>
void print(U8* Msg) {printf((char*)Msg);}

#include "C:\\code\\h2_transpiler\\build\\windows_h2_library.h"



U64 Kilobytes(U64 Bytes);
void Fatal(U8* Msg);
U64 EndianMirror(U32 Bytes, U32 Value);
U32 StrLen(U8* String);
U8* GetSectorAddress(void* Base, U32 Sector);

U64 Kilobytes(U64 Bytes) {
U64 __17;
{
U64 __18;
__18 = (U64)1024;
__17 = (Bytes * __18);
}
return __17;
}

void Fatal(U8* Msg) {
{
print(Msg);
print((U8*)"\n");
exit(1);
}
}

U64 EndianMirror(U32 Bytes, U32 Value) {
U64 __20;
{
U64 result;
U64 mask;
U32 shift;
result = Value;
mask = 255;
U32 __21;
U32 __22;
__22 = (U32)16;
__21 = (Bytes * __22);
U32 __23;
__23 = (U32)8;
shift = (__21 - __23);
{
I64 it;
it = 0;
__19:;
U64 __25;
I64 __26;
__26 = (I64)Bytes;
__25 = (it < __26);
if (__25)
{
U64 __27;
U64 __28;
U64 __29;
__29 = (U64)Value;
__28 = (__29 & mask);
U64 __30;
__30 = (U64)shift;
__27 = (__28 << __30);
result = (result | __27);
U64 __31;
__31 = (U64)8;
mask = (mask << __31);
U32 __32;
__32 = (U32)16;
shift = (shift - __32);
it = (it + 1);
goto __19;
}
}
__24:;
__20 = result;
}
return __20;
}

U32 StrLen(U8* String) {
U32 __34;
{
U32 it;
{
it = 0;
__33:;
U64 __36;
U8 __37;
__37 = String[it];
U8 __38;
__38 = (U8)0;
__36 = (__37 != __38);
if (__36)
{
U32 __39;
__39 = (U32)1;
it = (it + __39);
goto __33;
}
}
__35:;
__34 = it;
}
return __34;
}

U8* GetSectorAddress(void* Base, U32 Sector) {
U8* __40;
{
U8* result;
U8* __41;
__41 = (U8*)Base;
U64 __42;
U64 __43;
__43 = (U64)Sector;
__42 = (2048 * __43);
result = (__41 + __42);
__40 = result;
}
return __40;
}


U32 Argc;
U8** Argv;
void* inHandle;
void* outHandle;
U64 size;
U8* imageBuffer;

void main(U32 argc, U8** argv)
{
Argc = argc;
Argv = argv;

U64 __44;
U32 __45;
__45 = (U32)3;
__44 = (Argc != __45);
if (__44)
{
Fatal((U8*)"Invalid arguments: dumboot expects an input name and an output name.");
}
U8* __46;
__46 = Argv[1];
inHandle = Win32CreateFile(__46, GENERIC_READ, 0, OPEN_EXISTING);
U8* __47;
__47 = Argv[2];
outHandle = Win32CreateFile(__47, GENERIC_WRITE, 0, CREATE_ALWAYS);
size = Win32GetFileSize(inHandle);
U32 __48;
U32 __49;
__49 = Win32IsHandleValid(inHandle);
__48 = !(__49);
if (__48)
{
Fatal((U8*)"File could not be opened.");
}
U32 __50;
U32 __51;
__51 = Win32IsHandleValid(outHandle);
__50 = !(__51);
if (__50)
{
Fatal((U8*)"Output file could not be created.");
}
U64 __52;
__52 = (size > 2048);
if (__52)
{
Fatal((U8*)"File too big, the maximum size of the bootloader is 2048 bytes.");
}
void* __53;
__53 = Win32VirtualAlloc(43008);
imageBuffer = (U8*)__53;
{
U8* __7;
__7 = GetSectorAddress(imageBuffer, 16);
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__7 + 1);
localStr = (U8*)"CD001";
strLen = StrLen(localStr);
I64 __54;
__54 = (I64)strLen;
remaining = (5 - __54);
U64 __55;
U32 __56;
__56 = (U32)5;
__55 = (strLen > __56);
if (__55)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__8:;
U64 __58;
I64 __59;
__59 = (I64)strLen;
__58 = (it < __59);
if (__58)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __8;
}
}
__57:;
}
{
U8* writeAddress;
U8* __60;
__60 = (__7 + 6);
writeAddress = (U8*)__60;
*writeAddress = 1;
}
{
U8* writeAddress;
U8* __61;
__61 = (__7 + 0);
writeAddress = (U8*)__61;
*writeAddress = 1;
}
{
U64* writeAddress;
U8* __62;
__62 = (__7 + 80);
writeAddress = (U64*)__62;
*writeAddress = EndianMirror(4, 21);
}
{
U32* writeAddress;
U8* __63;
__63 = (__7 + 120);
writeAddress = (U32*)__63;
*writeAddress = EndianMirror(2, 1);
}
{
U32* writeAddress;
U8* __64;
__64 = (__7 + 124);
writeAddress = (U32*)__64;
*writeAddress = EndianMirror(2, 1);
}
{
U32* writeAddress;
U8* __65;
__65 = (__7 + 128);
writeAddress = (U32*)__65;
*writeAddress = EndianMirror(2, 2048);
}
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__7 + 318);
localStr = (U8*)"ANFAMAX_DUMBOOT";
strLen = StrLen(localStr);
I64 __66;
__66 = (I64)strLen;
remaining = (128 - __66);
U64 __67;
U32 __68;
__68 = (U32)128;
__67 = (strLen > __68);
if (__67)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__9:;
U64 __70;
I64 __71;
__71 = (I64)strLen;
__70 = (it < __71);
if (__70)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __9;
}
}
__69:;
}
{
U8* writeAddress;
U8* __72;
__72 = (__7 + 881);
writeAddress = (U8*)__72;
*writeAddress = 1;
}
}
{
U8* __10;
__10 = GetSectorAddress(imageBuffer, 17);
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__10 + 1);
localStr = (U8*)"CD001";
strLen = StrLen(localStr);
I64 __73;
__73 = (I64)strLen;
remaining = (5 - __73);
U64 __74;
U32 __75;
__75 = (U32)5;
__74 = (strLen > __75);
if (__74)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__11:;
U64 __77;
I64 __78;
__78 = (I64)strLen;
__77 = (it < __78);
if (__77)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __11;
}
}
__76:;
}
{
U8* writeAddress;
U8* __79;
__79 = (__10 + 6);
writeAddress = (U8*)__79;
*writeAddress = 1;
}
{
U8* writeAddress;
U8* __80;
__80 = (__10 + 0);
writeAddress = (U8*)__80;
*writeAddress = 0;
}
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__10 + 7);
localStr = (U8*)"EL TORITO SPECIFICATION";
strLen = StrLen(localStr);
I64 __81;
__81 = (I64)strLen;
remaining = (32 - __81);
U64 __82;
U32 __83;
__83 = (U32)32;
__82 = (strLen > __83);
if (__82)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__12:;
U64 __85;
I64 __86;
__86 = (I64)strLen;
__85 = (it < __86);
if (__85)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __12;
}
}
__84:;
}
{
U32* writeAddress;
U8* __87;
__87 = (__10 + 71);
writeAddress = (U32*)__87;
*writeAddress = 19;
}
}
{
U8* __13;
__13 = GetSectorAddress(imageBuffer, 18);
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__13 + 1);
localStr = (U8*)"CD001";
strLen = StrLen(localStr);
I64 __88;
__88 = (I64)strLen;
remaining = (5 - __88);
U64 __89;
U32 __90;
__90 = (U32)5;
__89 = (strLen > __90);
if (__89)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__14:;
U64 __92;
I64 __93;
__93 = (I64)strLen;
__92 = (it < __93);
if (__92)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __14;
}
}
__91:;
}
{
U8* writeAddress;
U8* __94;
__94 = (__13 + 6);
writeAddress = (U8*)__94;
*writeAddress = 1;
}
{
U8* writeAddress;
U8* __95;
__95 = (__13 + 0);
writeAddress = (U8*)__95;
*writeAddress = 255;
}
}
{
U8* __15;
__15 = GetSectorAddress(imageBuffer, 19);
{
U8* writeAddress;
U8* __96;
__96 = (__15 + 0);
writeAddress = (U8*)__96;
*writeAddress = 1;
}
{
U8* writeAddress;
U8* __97;
__97 = (__15 + 1);
writeAddress = (U8*)__97;
*writeAddress = 0;
}
{
U8* writeAddress;
U8* localStr;
U32 strLen;
I64 remaining;
writeAddress = (__15 + 4);
localStr = (U8*)"DUMBOOT";
strLen = StrLen(localStr);
I64 __98;
__98 = (I64)strLen;
remaining = (24 - __98);
U64 __99;
U32 __100;
__100 = (U32)24;
__99 = (strLen > __100);
if (__99)
{
Fatal((U8*)"String field was too long.");
}
{
I64 it;
it = 0;
__16:;
U64 __102;
I64 __103;
__103 = (I64)strLen;
__102 = (it < __103);
if (__102)
{
writeAddress[it] = localStr[it];
it = (it + 1);
goto __16;
}
}
__101:;
}
{
U16* writeAddress;
U8* __104;
__104 = (__15 + 28);
writeAddress = (U16*)__104;
*writeAddress = 28278;
}
{
U8* writeAddress;
U8* __105;
__105 = (__15 + 30);
writeAddress = (U8*)__105;
*writeAddress = 85;
}
{
U8* writeAddress;
U8* __106;
__106 = (__15 + 31);
writeAddress = (U8*)__106;
*writeAddress = 170;
}
{
U8* writeAddress;
U8* __107;
__107 = (__15 + 32);
writeAddress = (U8*)__107;
*writeAddress = 136;
}
{
U16* writeAddress;
U8* __108;
__108 = (__15 + 38);
writeAddress = (U16*)__108;
*writeAddress = 4;
}
{
U32* writeAddress;
U8* __109;
__109 = (__15 + 40);
writeAddress = (U32*)__109;
*writeAddress = 20;
}
}
U8* __110;
__110 = GetSectorAddress(imageBuffer, 20);
U32 __111;
__111 = (U32)size;
Win32ReadFile(inHandle, __110, __111);
Win32WriteFile(outHandle, imageBuffer, 43008);
Win32VirtualFree(imageBuffer);
Win32CloseHandle(inHandle);
Win32CloseHandle(outHandle);
}
