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
	//list가 Full이 아닐 경우 add 후 m_Length 증가.
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
	//Pointer를 -1로 바꿈. 그래야 GetNextItem에서 첫번째 아이템 가리킴.
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int ArrayList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

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
			// parameter data에 해당 아이템 정보를 넣음.
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
		//특정 data를 찾으면, 그 뒤 데이터 한칸씩 앞으로 이동.
		else {
			m_Array[m_CurPointer - 1] = m_Array[m_CurPointer];
		}
	}
	
	//m_Length 감소(데이터 하나 삭제됨)
	m_Length--;
	if (isFind) return 1;
	else return -1;
}

//number가 같은 item의 정보를 바꿈.
int ArrayList::Replace(ItemType data) {
	for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
		if (data == m_Array[m_CurPointer]) {
			m_Array[m_CurPointer] = data;
			return 1;
		}
	}
	return -1;
}
