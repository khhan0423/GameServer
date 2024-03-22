#pragma once

#define OUT
#define IN


//__COUNTER__ 컴파일시마다 유니크한 정수값 제공
//_T 유니코드일때는 L로 치환되어 wide string 이라는 의미로 쓰인다. 멀티바이트일때는 무시 된다.
//__FILE__ 소스 파일 이름
//__LINE__ 소스 파일 라인
//## 연결 a##b -> ab
//#pragma message  컴파일타임에 IDE 출력창에 메시지 전달.

#include <assert.h>
#ifndef _DEBUG
#define ASSERT_REPORT(exp, msg)
#else
#define ASSERT_REPORT(exp, msg) _wassert(_CRT_WIDE(#exp), _CRT_WIDE(__FILE__), __LINE__)
#endif

#define MAKE_PAIR(a, b)											a##b
#define MAKE_UNIQUE_VALUE(c)									MAKE_PAIR(__unique_value, c)
#define MAKE_TEMP_VALUE											MAKE_UNIQUE_VALUE(__COUNTER__)

#ifndef _DEBUG
#define ASSERT(exp)
#define ASSERT_MSG(exp, msg)
#else
#define ASSERT(exp)												{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); } }
#define ASSERT_MSG(exp, msg)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)##msg); } }
#endif

#define VERIFY(exp)												{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); } }
#define VERIFY_CONTINUE(exp)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); continue; } }
#define VERIFY_BREAK(exp)										{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); break; } }
#define VERIFY_RETURN(exp)										{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return; } }
#define VERIFY_RETURN_TRUE(exp)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return true; } }
#define VERIFY_RETURN_FALSE(exp)								{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return false; } }
#define VERIFY_RETURN_NULL(exp)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return NULL; } }
#define VERIFY_RETURN_ZERO(exp)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return 0; } }
#define VERIFY_RETURN_EOF(exp)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return -1; } }
#define VERIFY_RETURN_VALUE(exp, returnValue)					{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); return returnValue; } }
#define VERIFY_IF_REAL(exp, c)									const bool MAKE_UNIQUE_VALUE(c) = (!!(exp)); if(!(MAKE_UNIQUE_VALUE(c))) { ASSERT_REPORT(exp, _T(#exp)); } if((MAKE_UNIQUE_VALUE(c)))
#define VERIFY_IF(exp)											VERIFY_IF_REAL(exp, __COUNTER__)
#define VERIFY_FAILED_REAL(exp, c)								const bool MAKE_UNIQUE_VALUE(c) = (!!(exp)); if(!(MAKE_UNIQUE_VALUE(c))) { ASSERT_REPORT(exp, _T(#exp)); } if(!(MAKE_UNIQUE_VALUE(c)))
#define VERIFY_FAILED(exp)										VERIFY_FAILED_REAL(exp, __COUNTER__)
#define VERIFY_DELETE_CONTINUE(exp, p)							{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } continue; } }
#define VERIFY_DELETE_BREAK(exp, p)								{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } break; } }
#define VERIFY_DELETE_RETURN(exp, p)							{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } return; } }
#define VERIFY_DELETE_RETURN_TRUE(exp, p)						{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } return true; } }
#define VERIFY_DELETE_RETURN_FALSE(exp, p)						{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } return false; } }
#define VERIFY_DELETE_RETURN_NULL(exp, p)						{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } return NULL; } }
#define VERIFY_DELETE_RETURN_VALUE(exp, p, returnValue)			{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); if(p) { delete (p); (p) = nullptr; } return returnValue; } }

#define VERIFY_MSG(exp, msg)									{ if(!(exp)) { ASSERT_REPORT(exp, msg); } }
#define VERIFY_MSG_CONTINUE(exp, msg)							{ if(!(exp)) { ASSERT_REPORT(exp, msg); continue; } }
#define VERIFY_MSG_BREAK(exp, msg)								{ if(!(exp)) { ASSERT_REPORT(exp, msg); break; } }
#define VERIFY_MSG_RETURN(exp, msg)								{ if(!(exp)) { ASSERT_REPORT(exp, msg); return; } }
#define VERIFY_MSG_RETURN_TRUE(exp, msg)						{ if(!(exp)) { ASSERT_REPORT(exp, msg); return true; } }
#define VERIFY_MSG_RETURN_FALSE(exp, msg)						{ if(!(exp)) { ASSERT_REPORT(exp, msg); return false; } }
#define VERIFY_MSG_RETURN_NULL(exp, msg)						{ if(!(exp)) { ASSERT_REPORT(exp, msg); return NULL; } }
#define VERIFY_MSG_RETURN_ZERO(exp, msg)						{ if(!(exp)) { ASSERT_REPORT(exp, msg); return 0; } }
#define VERIFY_MSG_RETURN_EOF(exp, msg)							{ if(!(exp)) { ASSERT_REPORT(exp, msg); return -1; } }
#define VERIFY_MSG_RETURN_VALUE(exp, msg, returnValue)			{ if(!(exp)) { ASSERT_REPORT(exp, msg); return returnValue; } }
#define VERIFY_MSG_IF_REAL(exp, msg, c)							const bool MAKE_UNIQUE_VALUE(c) = (!!(exp)); if(!(MAKE_UNIQUE_VALUE(c))) { ASSERT_REPORT(exp, msg); } if((MAKE_UNIQUE_VALUE(c)))
#define VERIFY_MSG_IF(exp, msg)									VERIFY_MSG_IF_REAL(exp, msg, __COUNTER__)
#define VERIFY_MSG_FAILED_REAL(exp, msg, c)						const bool MAKE_UNIQUE_VALUE(c) = (!!(exp)); if(!(MAKE_UNIQUE_VALUE(c))) { ASSERT_REPORT(exp, msg); } if(!(MAKE_UNIQUE_VALUE(c)))
#define VERIFY_MSG_FAILED(exp, msg)								VERIFY_MSG_FAILED_REAL(exp, msg, __COUNTER__)
#define VERIFY_MSG_DELETE_CONTINUE(exp, msg, p)					{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } continue; } }
#define VERIFY_MSG_DELETE_BREAK(exp, msg, p)					{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } break; } }
#define VERIFY_MSG_DELETE_RETURN(exp, msg, p)					{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } return; } }
#define VERIFY_MSG_DELETE_RETURN_TRUE(exp, msg, p)				{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } return true; } }
#define VERIFY_MSG_DELETE_RETURN_FALSE(exp, msg, p)				{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } return false; } }
#define VERIFY_MSG_DELETE_RETURN_NULL(exp, msg, p)				{ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } return NULL; } }
#define VERIFY_MSG_DELETE_RETURN_VALUE(exp, msg, p, returnValue){ if(!(exp)) { ASSERT_REPORT(exp, msg); if(p) { delete (p); (p) = nullptr; } return returnValue; } }

#define NEVER_GET_HERE									ASSERT_REPORT(0, _T("ASSERT : NEVER GET HEAR"))

//SAFE 매크로
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#endif
#ifndef SAFE_CLOSE
#define SAFE_CLOSE(p) { if(p != INVALID_HANDLE_VALUE) { CloseHandle(p); (p) = INVALID_HANDLE_VALUE; } }
#endif

//TODO 매크로
//사용법 : #pagma TODO("이곳에 앞으로 해야 할 목록을 작성하면 컴파일시에 출력창을 통해 출력이 된다")
//#pragma message 기능을 확장
#ifndef _QUOTE
#define _QUOTE(x) # x
#endif
#ifndef QUOTE
#define QUOTE(x) _QUOTE(x)
#endif
#ifndef __FILE__LINE__
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "
#endif
#ifndef TODO
#define TODO(x) message( __FILE__LINE__ " TODO : "x"\n")
#endif
#ifndef FIXME
#define FIXME(x) message(__FILE__LINE__ " FIXME : "x"\n")
#endif