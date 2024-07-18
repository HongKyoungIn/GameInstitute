#pragma once
#include <d2d1.h>

class AABB {
public:
    AABB() : mCenter{ 0 }, mExtent{ 0 } { }
    AABB(const D2D1_RECT_F& bounds)
        : mCenter{ (bounds.right + bounds.left) / 2, (bounds.bottom + bounds.top) / 2 },
        mExtent{ (bounds.right - bounds.left) / 2, (bounds.bottom - bounds.top) / 2 } { }

    D2D1_POINT_2F GetCenter() const { return mCenter; }
    D2D1_POINT_2F GetExtent() const { return mExtent; }
    D2D1_RECT_F GetBounds() const {
        return D2D1::RectF(
            mCenter.x - mExtent.x,
            mCenter.y - mExtent.y,
            mCenter.x + mExtent.x,
            mCenter.y + mExtent.y
        );
    }

    void SetCenter(float x, float y) { mCenter = { x, y }; }
    void SetExtent(float x, float y) { mExtent = { x, y }; }

    bool Intersects(const AABB& other) const {
        return !(
            (mCenter.x + mExtent.x < other.mCenter.x - other.mExtent.x) ||
            (mCenter.x - mExtent.x > other.mCenter.x + other.mExtent.x) ||
            (mCenter.y + mExtent.y < other.mCenter.y - other.mExtent.y) ||
            (mCenter.y - mExtent.y > other.mCenter.y + other.mExtent.y)
            );
    }

private:
    D2D1_POINT_2F mCenter;
    D2D1_POINT_2F mExtent;
};
