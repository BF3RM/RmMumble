#ifndef RMMESSAGE_H
#define RMMESSAGE_H

#include <QTcpSocket> 

enum class EMessageType : uint8_t
{
	Default = 100,
	UpdateData = 120,
	StopTalking = 121,
	Talking = 122,
	Uuid = 123,
	Ping = 124,
	MuteAndDeaf = 125,
};

typedef std::function<void(class RMMessage*)> OnMessageCallback;

class RMMessage
{
public:
	RMMessage(QTcpSocket* Socket, EMessageType Type) : m_Socket(Socket), m_MessageType(Type)
	{
		m_Data = (char*)malloc(sizeof(uint32_t));
		AddData(&m_DataSize, sizeof(uint32_t));
		AddData(&m_MessageType, sizeof(EMessageType));
	}

    ~RMMessage()
    {
        free(m_Data);
    }

    void Send()
    {
        if (!m_Socket) return;
		auto Size = GetSize();
		memcpy(&m_Data[0], &Size, sizeof(uint32_t));
        m_Socket->write(&m_Data[0], m_DataSize);
    }

	void AddData(void* Source, uint32_t Size)
	{
		m_DataSize += Size;
		m_Data = (char*)realloc((void*)m_Data, m_DataSize);
		memcpy((void*)(m_Data + m_Offset), Source, Size);
		m_Offset += Size;
	}

	void* GetData()
	{
		return &m_Data[sizeof(uint32_t) + sizeof(EMessageType)];
	}

	EMessageType GetMessageType()
	{
		return (EMessageType)m_Data[sizeof(uint32_t)];
	}

	uint32_t GetRealSize()
	{
		return m_DataSize;
	}

	uint32_t GetSize()
	{
		return m_DataSize - sizeof(uint32_t);
	}
public:
    char* m_Data = nullptr;
protected:
	QTcpSocket* m_Socket = nullptr;
	uint32_t m_DataSize = 0;
	uint32_t m_Offset = 0;
	EMessageType m_MessageType = EMessageType::Default;
};

#endif