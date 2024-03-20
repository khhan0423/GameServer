#pragma once

//https://en.cppreference.com/w/cpp/language/bit_field 비트필드 관련 레퍼런스
//https://en.cppreference.com/w/cpp/chrono/c/time Epoch 타임스템프 관련 레퍼런스
//https://www.epochconverter.com/ Epoch 타임스템프 변환테스트
struct SerialDetail
{
	//■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
	__int64		m_CategoryID : 6;

	//□□□□□□■■■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
	__int64		m_ServerID : 8;

	//□□□□□□□□□□□□□□■■■■■■■■■■■■■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
	__int64		m_Sequence : 18;

	//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	__int64		m_Time : 32; //Epoch 타임 스템프 초 단위라 32비트 영역으로 죽을 때 까지 커버가능
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

