#pragma once
#include "ActorComponent.h"

class CActor;

class CBlackBoardComponent : public CActorComponent
{
public:
	explicit CBlackBoardComponent() = default;
	virtual ~CBlackBoardComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

/********************
	Methods
********************/
public:
	void ClearValue(const std::wstring& _wstrKey);
	void RemoveValue(const std::wstring& _wstrKey);

	bool GetValueAsBool(const std::wstring& _wstrKey);
	void SetValueAsBool(const std::wstring& _wstrKey, bool _bValue);

	float GetValueAsFloat(const std::wstring& _wstrKey);
	void SetValueAsFloat(const std::wstring& _wstrKey, float _fValue);

	int GetValueAsInt(const std::wstring& _wstrKey);
	void SetValueAsInt(const std::wstring& _wstrKey, int _iValue);

	std::wstring GetValueAsWstring(const std::wstring& _wstrKey);
	void SetValueAsWstring(const std::wstring& _wstrKey, const std::wstring& _wstrValue);

	FVector3 GetValueAsFVector3(const std::wstring& _wstrKey);
	void SetValueAsFVector3(const std::wstring& _wstrKey, const FVector3& _vValue);

	std::shared_ptr<CActor> GetValueAsActor(const std::wstring& _wstrKey);
	void SetValueAsActor(const std::wstring& _wstrKey, std::weak_ptr<CActor> _wpActor);

/********************
	Data Members
********************/
private:
	std::unordered_map<std::wstring, bool> m_umapBoolValues;
	std::unordered_map<std::wstring, int32> m_umapIntValues;
	std::unordered_map<std::wstring, float> m_umapFloatValues;
	std::unordered_map<std::wstring, std::wstring> m_umapWstringValues;
	std::unordered_map<std::wstring, FVector3> m_umapFVector3Values;
	std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_umapActorValues;
};

