#pragma once

class CObject : public std::enable_shared_from_this<CObject>
{
public:
	explicit CObject() = default;
	virtual ~CObject() = default;
};