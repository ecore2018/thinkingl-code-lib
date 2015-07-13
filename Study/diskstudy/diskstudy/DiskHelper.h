#pragma once

#include <vector>
#include <string>

typedef _int64 i64;

class CDiskHelper
{
public:
	CDiskHelper();
	~CDiskHelper();



};

// ��ȡϵͳ�еĴ����б�.
typedef std::wstring CLogicalVol;
typedef std::vector< CLogicalVol > CLogicalVolList;
bool GetLogicalVolList(CLogicalVolList& diskList);

typedef std::wstring CPhysicalDrive;
typedef std::vector< CPhysicalDrive > CPhysicalDriveList;
bool GetPhysicalDriveList(CPhysicalDriveList& physicalDriveList);

// ͨ���߼���������ȡ������̺�.
// �ɹ�����������������, ʧ�ܷ���-1.
typedef std::wstring CLogicalVolName;
int GetPhysicalDriveNumberByLogicalVolName(const CLogicalVolName& name);

CPhysicalDrive GetPhysicalDriveName(int physicalDriveNumber);

enum EDiskMediaType
{
	DiskMediaTypeInvalid,
	DiskMediaTypeFixHardDisk,
	DiskMediaTypeRemovableMedia,
	DiskMediaTypeUnknown,
};
// ��ȡ������Ϣ.
struct TDiskInfo
{
	// �����ܴ�С(�ֽ�)
	i64 m_diskSize;

	// Cylinders��Ŀ
	i64 m_cylinders;

	// Media type. FixedMedia : �̶�Ӳ��. RemovableMedia:���Ƴ���ý��
	EDiskMediaType m_mediaType;
	int m_mediaTypeRaw;

	// 
	unsigned int m_sectorsPerTrack;

	//
	unsigned int m_bytesPerSector;

	// SMART�汾��Ϣ. https://msdn.microsoft.com/en-us/library/windows/hardware/ff554977(v=vs.85).aspx
	//BYTE     bVersion;               // Binary driver version.
	//BYTE     bRevision;              // Binary driver revision.
	//BYTE     bReserved;              // Not used.
	//BYTE     bIDEDeviceMap;          // Bit map of IDE devices.
	//DWORD   fCapabilities;          // Bit mask of driver capabilities.
	unsigned char bIDEDeviceMap;	// IDE��Ϣ.
	unsigned int fCapabilities;		// ������������Bit mask.

	// �¶�.
	float m_diskTemperature;
};

bool GetDiskInfo(const CPhysicalDrive& drive, TDiskInfo& diskInfo);