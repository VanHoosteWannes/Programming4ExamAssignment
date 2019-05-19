#pragma once
#include "Singleton.h"

class PointsManager : public dae::Singleton<PointsManager>
{
public:
	void AddPoints(int points) { m_Points += points; };
	int GetPoints() { return m_Points; }
	void ResetPoints() { m_Points = 0; };
	PointsManager();
	~PointsManager() = default;

private:
	int m_Points = 0;
};

