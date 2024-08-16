#pragma once

template<typename T>
void SAFE_DELETE(T& _ptr)
{
	if (nullptr != _ptr)
	{
		delete _ptr;
		_ptr = nullptr;
	}
}

template<typename T>
void SAFE_DELETE_ARRAY(T& _ptr)
{
	if (nullptr != _ptr)
	{
		delete[] _ptr;
		_ptr = nullptr;
	}
}

template<typename T>
unsigned long SAFE_RELEASE(T& _ptr)
{
	unsigned int iReferenceCount = 0;
	if (nullptr != _ptr)
	{
		iReferenceCount = _ptr->Release();
		if (iReferenceCount == 0)
		{
			_ptr = nullptr;
		}
	}
	return iReferenceCount;
}

class TAG_FINDER_FUNCTOR final
{
public:
	explicit TAG_FINDER_FUNCTOR(const wchar* _pTag) : m_pTag(_pTag) {}
	~TAG_FINDER_FUNCTOR() = default;

public:
	template<typename T>
	bool operator()(const T& _pair)
	{
		lstrcmpW(m_pTag, _pair.first) == 0 ? true : false;
	}

private:
	const wchar* m_pTag = nullptr;
};

class DELETE_OBJECT_FUNCTOR final
{
public:
	explicit DELETE_OBJECT_FUNCTOR() = default;
	~DELETE_OBJECT_FUNCTOR() = default;

public:
	template <typename T>
	void operator() (T& _ptr)
	{
		unsigned int iReferenceCount = 0;
		iReferenceCount = _ptr->Release();

		if (0 == iReferenceCount)
		{
			_ptr = nullptr;
		}
	}
};

class DELETE_MAP_FUNCTOR final
{
public:
	explicit DELETE_MAP_FUNCTOR() = default;
	~DELETE_MAP_FUNCTOR() = default;

public:
	template <typename T>
	void operator() (T& _pair)
	{
		unsigned int iReferenceCount = 0;
		iReferenceCount = _pair.second->Release();

		if (iReferenceCount == 0)
		{
			_pair.second = nullptr;
		}	
	}
};
