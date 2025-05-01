#include "CBuffEntry.h"

#include "Engine.h"

BYTE CBuffEntry::GetBuffType() {
	return *(BYTE*)((DWORD)this + oBuffType);
}

bool CBuffEntry::IsBuffEmpty() {
	return strptr == 0;
}

bool CBuffEntry::IsAlive() {
	auto time = Engine::GetGameTime();
	return this->GetBuffStartTime() < time && time < this->GetBuffEndTime();
}

bool CBuffEntry::IsValid() {
	if (this == NULL || (DWORD)this <= 0x1000)
		return false;

	return strcmp(GetBuffName(), "NULL") && GetBuffCountAlt() > 0;
}

float CBuffEntry::GetBuffStartTime() {
	return *(float*)((DWORD)this + O_BUFFMGR_STARTTIME);
}

float CBuffEntry::GetBuffEndTime() {
	return *(float*)((DWORD)this + O_BUFFMGR_ENDTIME);
}

int CBuffEntry::GetBuffCountAlt() {
	return (*(int*)((DWORD)this + oBuffCountAlt) - *(int*)((DWORD)this + oBuffCountAlt2)) >> 3;
}

float CBuffEntry::GetBuffCountFloat() {
	return *(float*)((DWORD)this + O_BUFFMGR_flBUFFCOUNT);
}

int CBuffEntry::GetBuffCountInt() {
	return *(int*)((DWORD)this + O_BUFFMGR_iBUFFCOUNT);
}

char* CBuffEntry::GetBuffName() {
	DWORD aux = *(DWORD*)((DWORD)this + O_BUFFMGR_BUFFNAME);
	if (aux == NULL)
		return "NULL";

	if (*(DWORD*)(aux + O_BUFFMGR_BUFFNAME) == NULL)
		return "NULL";

	return (char*)(aux + O_BUFFMGR_BUFFNAME);
}
