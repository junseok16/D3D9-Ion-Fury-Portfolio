#pragma once

class CLevel;

class CWindow
{
public:
	explicit CWindow() = default;
	virtual ~CWindow() = default;

public:
	virtual void Initialize(std::weak_ptr<CLevel> _wpLevel);
	virtual void BeginPlay();
	virtual int32 Update(const float& _fDeltaSeconds);
	virtual int32 LateUpdate(const float& _fDeltaSeconds);
	virtual void Render();
	virtual void EndPlay();
	virtual void Release();
};

