#ifndef RMMESSAGE_H
#define RMMESSAGE_H

#include <cstdint>
#include <functional>

enum class EMessageType : uint8_t
{
	Default = 100,
	UpdatePlayersList = 117,
	Shutdown = 118,
	IdentityRequest = 119,
	UpdateData = 120,
	StopTalking = 121,
	Talking = 122,
	Uuid = 123,
	Ping = 124,
	MuteAndDeaf = 125,
};

class RMSocket;
typedef std::function<void(class RMMessage*)> OnMessageCallback;

class RMMessage
{
public:
	RMMessage(RMSocket* Socket, EMessageType Type);

	~RMMessage();

	void Send();

	void AddData(const void* Source, const uint32_t Size);

	inline void* GetData() const { return &m_Data[sizeof(uint32_t) + sizeof(EMessageType)]; }

	inline EMessageType GetMessageType() const { return (EMessageType)m_Data[sizeof(uint32_t)]; }

	inline uint32_t GetRealSize() const { return m_DataSize; }

	inline uint32_t GetSize() const { return m_DataSize - sizeof(uint32_t); }
public:
    char* m_Data = nullptr;
protected:
	RMSocket* m_Socket = nullptr;
	uint32_t m_DataSize = 0;
	uint32_t m_Offset = 0;
	EMessageType m_MessageType = EMessageType::Default;
};

#endif