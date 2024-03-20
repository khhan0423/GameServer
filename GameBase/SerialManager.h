#pragma once

//https://en.cppreference.com/w/cpp/language/bit_field ��Ʈ�ʵ� ���� ���۷���
//https://en.cppreference.com/w/cpp/chrono/c/time Epoch Ÿ�ӽ����� ���� ���۷���
//https://www.epochconverter.com/ Epoch Ÿ�ӽ����� ��ȯ�׽�Ʈ
struct SerialDetail
{
	//�����������������������������������������������������������������
	__int64		m_CategoryID : 6;

	//�����������������������������������������������������������������
	__int64		m_ServerID : 8;

	//�����������������������������������������������������������������
	__int64		m_Sequence : 18;

	//�����������������������������������������������������������������
	__int64		m_Time : 32; //Epoch Ÿ�� ������ �� ������ 32��Ʈ �������� ���� �� ���� Ŀ������
};

union SerialData
{
	SerialDetail	m_detail;
	__int64			m_SerialNo;

	SerialData()
	{
		m_SerialNo = 0;
	}
};

