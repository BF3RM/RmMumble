#include "RMMessage.h"
#include "RMSocket.h"

RMMessage::RMMessage(RMSocket* Socket, EMessageType Type) : m_Socket(Socket), m_MessageType(Type)
{
	m_Data = (char*)malloc(sizeof(uint32_t));
	AddData(&m_DataSize, sizeof(uint32_t));
	AddData(&m_MessageType, sizeof(EMessageType));
}

RMMessage::~RMMessage()
{
	free(m_Data);
}

void RMMessage::Send() 
{
	if (!m_Socket) return;
	auto Size = GetSize();
	memcpy(&m_Data[0], &Size, sizeof(uint32_t));
	m_Socket->AddMessageToPoll(this);
}

void RMMessage::AddData(void* Source, uint32_t Size)
{
	m_DataSize += Size;
	m_Data = (char*)realloc((void*)m_Data, m_DataSize);
	memcpy((void*)(m_Data + m_Offset), Source, Size);
	m_Offset += Size;
}
