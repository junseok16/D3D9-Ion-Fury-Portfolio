#pragma once

/********************
	상수 매크로
********************/
const int32 CIWINCX = 1280;
const int32 CIWINCY = 720;
const float CFWINCX = 1280.0F;
const float CFWINCY = 720.0F;

/********************
	디버그 매크로
********************/
#define MESSAGE_BOX(_message)							\
		MessageBox(NULL, _message, L"Error", MB_OK)		\

// 불 반환 값을 확인합니다.
#define CHECK(_expression)								\
		assert(_expression);							\

#define CHECKF(_expression, _message)					\
		if (!(_expression))								\
		{												\
			MESSAGE_BOX(_message);						\
			assert(_expression);						\
		}												\

// HRESULT 반환 값을 확인합니다.
#define ENSURE(_hr)										\
		assert(SUCCEEDED(_hr));							\

#define ENSUREF(_hr)									\
		if (!SUCCEEDED(_hr))							\
		{												\
			MESSAGE_BOX(_message);						\
			ENSURE(_hr);								\
		}												\

/********************
	싱글턴 매크로
********************/
#define DELETE_COPY(classType)								\
		public:												\
		classType() = default;								\
		~classType() = default;								\
															\
		classType(const classType&) = delete;				\
		classType(classType&&) = delete;					\
															\
		classType& operator=(const classType&) = delete;	\
		classType& operator=(classType&&) = delete;			\


#define DECLARE_SINGLETON(classType)						\
		DELETE_COPY(classType)								\
		private:											\
		static std::unique_ptr<classType> m_upInstance;		\
															\
		public:												\
		static std::unique_ptr<classType>& GetInstance();	\


#define IMPLEMENT_SINGLETON(classType)									\
		std::unique_ptr<classType> classType::m_upInstance = nullptr;	\
																		\
		std::unique_ptr<classType>& classType::GetInstance()			\
		{																\
			if (m_upInstance == nullptr)								\
			{															\
				m_upInstance = std::make_unique<classType>();			\
			}															\
			return m_upInstance;										\
		}