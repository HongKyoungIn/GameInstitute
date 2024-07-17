#pragma once
#include <d2d1.h>

class AABB {
public:
	AABB() : m_Center{ 0 }, m_Extent{ 0 } { }

	D2D1_POINT_2F m_Center; // �߾�
	D2D1_POINT_2F m_Extent; // x,y�� Ȯ�尪	

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { m_Center = { x, y }; }
	void SetExtent(float x, float y) { m_Extent = { x, y }; }
	float GetMinX() { return m_Center.x - m_Extent.x; }
	float GetMaxX() { return m_Center.x + m_Extent.x; }
	float GetMinY() { return m_Center.y - m_Extent.y; }
	float GetMaxY() { return m_Center.y + m_Extent.y; }

	bool CheckIntersect(const AABB& other) const {
		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;

		float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
		float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
		float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
		float BoxB_ymax = other.m_Center.y + other.m_Extent.y;

		if(BoxA_xmax < BoxB_xmin || BoxA_xmin > BoxB_xmax || BoxA_ymax < BoxB_ymin || BoxA_ymin > BoxB_ymax) {
			return false;
		}

		return true;
	}
};
