#pragma once
#include "Actor.h"

class CTextUIComponent;

class CUI : public CActor
{
public:
	explicit CUI() = default;
	virtual ~CUI() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;


	void SetInitNumberUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextUIComponent, 
		std::wstring _wstrText, const std::wstring& _wstrTextureFileName, const float& _iScaleX, 
		const float& _iScaleY, const float& _iPositionX, const float& _iPositionY);
	
	void SetBeginPlayNumberUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextUIComponent, 
		std::wstring _wstrText, const std::wstring& _wstrTextureFileName);
	
	void SetInitTextUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextUIComponent, 
		std::wstring _wstrText, std::wstring _wstrKey, const std::wstring& _wstrTextureFileName, const float& _iScaleX,
		const float& _iScaleY, const float& _iPositionX, const float& _iPositionY);
	
	void SetBeginPlayTextUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextUIComponent, 
		std::wstring _wstrText, std::wstring _wstrKey, const std::wstring& _wstrTextureFileName);


private:
	//std::vector<std::weak_ptr<CTextUIComponent>> m_vecTextUIComponent;

};


