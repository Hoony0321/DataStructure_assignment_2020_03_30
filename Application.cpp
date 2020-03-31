#include "Application.h"



void Application::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:		// �� ������ �Է� �޾� ����Ʈ�� �߰�
			AddItem();
			break;
		case 2:		// ���� ������ȣ�� �Է� �޾� ����Ʈ���� ����
			DeleteMusic();
			break;
		case 3:		// �� ������ �Է� �޾Ƽ� ����Ʈ���� �ش� �� ������ ����			
			ReplaceMusic();
			break;
		case 4:		// �Էµ� ������ ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���				
			RetrieveMusic();
			break;
		case 5:		// ����Ʈ�� ����� ��� ���� ȭ�鿡 ���
			DisplayAllMusic();
			break;
		case 6: 		// ����Ʈ�� �Էµ� ��� ���� ����
			MakeEmpty();
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Delete item" << endl;
	cout << "\t   3 : Replace item" << endl;
	cout << "\t   4 : Retrieve item" << endl;
	cout << "\t   5 : Print all on screen" << endl;
	cout << "\t   6 : Make empty list" << endl;
	cout << "\t   7 : Get from file" << endl;
	cout << "\t   8 : Put to file " << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// Add new record into list.
int Application::AddItem()
{
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (m_List.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	m_List.Add(item);

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Display all records in the list on screen.
void Application::DisplayAllMusic()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;
	cout << "\t-----------------------" << endl;
	if (m_List.IsEmpty()) {
		cout << "\tList is Empty." << endl;
		return;
	}
	// list�� ��� �����͸� ȭ�鿡 ���
	m_List.ResetList();
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.DisplayRecordOnScreen();
		curIndex = m_List.GetNextItem(data);
	}
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char* fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_InFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char* fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_OutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// �б�� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�

	// array�� ������ ����ִ� structure ����
	while (!m_InFile.eof()) {
		// ���Ͽ��� ���� �о����
		data.ReadDataFromFile(m_InFile);
		// ������ ���ڿ����� �Ǵ� �� while�� ����
		if (m_InFile.eof()) break;
		// ����Ʈ�� �ش� ���� �߰�
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	m_List.ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}

int Application::RetrieveMusic() {
	ItemType selectItem;
	selectItem.SetNumFromKB();

	//������ �������
	if (m_List.Get(selectItem)) {
		cout << "\t-----Search-----" << endl;
		selectItem.DisplayRecordOnScreen();
		return 1;
	}
	else {
		//������ �������
		cout << "\n\t�ش� Number�� ������ �������� �ʽ��ϴ�.";
		return 0;
	}
}

int Application::DeleteMusic() {
	ItemType selectItem;
	selectItem.SetNumFromKB();

	if (m_List.Delete(selectItem)) {
		cout << "\n\t������ ���������� �����Ͽ����ϴ�.";
		return 1;
	}
	else {
		//������ �������
		cout << "\n\t�ش� Number�� ������ �������� �ʽ��ϴ�.";
		return 0;
	}
}

int Application::ReplaceMusic() {
	ItemType selectItem;
	selectItem.SetRecordFromKB();

	if (m_List.Replace(selectItem)) {
		cout << "\n\t������ ���������� �����Ͽ����ϴ�.";
		return 1;
	}
	else {
		//������ �������
		cout << "\n\t�ش� Number�� ������ �������� �ʽ��ϴ�.";
		return 0;
	}
}

void Application::MakeEmpty() {
	m_List.MakeEmpty();
}

