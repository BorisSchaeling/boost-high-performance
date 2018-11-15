#include <windows.h>
#include <vector>
#include <ostream>
#include <iostream>

std::ostream &operator<<(std::ostream &os, PROCESSOR_CACHE_TYPE &type)
{
	os << "Cache type: ";
	switch (type)
	{
	case CacheUnified: os << "Unified\n"; break;
	case CacheInstruction: os << "Instructions\n"; break;
	case CacheData: os << "Data\n"; break;
	case CacheTrace: os << "Traces\n"; break;
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, _CACHE_DESCRIPTOR &descriptor)
{
	os << "Cache level: " << static_cast<int>(descriptor.Level) << '\n';
	os << "Cache line size: " << descriptor.LineSize << '\n';
	os << "Cache size: " << descriptor.Size << '\n';
	os << descriptor.Type;
	return os;
}

int main()
{
	DWORD size;
	GetLogicalProcessorInformation(nullptr, &size);
	std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> infos;
	infos.resize(size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
	GetLogicalProcessorInformation(infos.data(), &size);
	for (int i = 0; i < size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i)
	{
		if (infos[i].Relationship == RelationCache)
		{
			std::cout << infos[i].Cache;
			std::cout << "----------\n";
		}
	}
}
