#include "ArrayList.h"

void ArrayList::MakeEmpty() {
	m_Length = 0;
}

int ArrayList::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
bool ArrayList::IsFull()
{
	if (m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}


// add a new data into list.
int ArrayList::Add(ItemType inData)
{
	//list�� Full�� �ƴ� ��� add �� m_Length ����.
	if (!IsFull())
	{
		m_Array[m_Length] = inData;
		m_Length++;
	}
	else
		return 0;

	return 1;
}


// Initialize list iterator.
void ArrayList::ResetList()
{
	//Pointer�� -1�� �ٲ�. �׷��� GetNextItem���� ù��° ������ ����Ŵ.
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int ArrayList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer ����
	if (m_CurPointer == MAXSIZE)	// end of list�̸� -1�� ����
		return -1;
	data = m_Array[m_CurPointer];	// ���� list pointer�� ���ڵ带 ����

	return m_CurPointer;
}


bool ArrayList::IsEmpty() {
	if (m_Length == 0)
		return true;
	return false;
}


int ArrayList::Get(ItemType& data) {
	for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
		if (data == m_Array[m_CurPointer]) {
			// parameter data�� �ش� ������ ������ ����.
			data = m_Array[m_CurPointer];
			return 1;
		}
	}
	return 0;
}

int ArrayList::Delete(ItemType data) {
	bool isFind = false;
	for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
		if (!isFind) {
			if (data == m_Array[m_CurPointer]) {
				isFind = true;
			}
		}
		//Ư�� data�� ã����, �� �� ������ ��ĭ�� ������ �̵�.
		else {
			m_Array[m_CurPointer - 1] = m_Array[m_CurPointer];
		}
	}
	
	//m_Length ����(������ �ϳ� ������)
	m_Length--;
	if (isFind) return 1;
	else return -1;
}

//number�� ���� item�� ������ �ٲ�.
int ArrayList::Replace(ItemType data) {
	for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
		if (data == m_Array[m_CurPointer]) {
			m_Array[m_CurPointer] = data;
			return 1;
		}
	}
	return -1;
}
