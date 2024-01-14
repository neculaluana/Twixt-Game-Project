#ifdef GAMELOGIC_EXPORTS
#define BRIDGE_API _declspec(dllexport)
#else
#define BRIDGE_API _declspec(dllimport)
#endif // GAMELOGIC_EXPORTS

#pragma once
#include "Point.h" 
class BRIDGE_API Bridge
{
public:
	Bridge(Point startPoint, Point endPoint);
	Bridge(const Bridge& other);
	Bridge(Bridge&& other)noexcept;
	Bridge() = default;

	Bridge& operator=(const Bridge& other);
	Bridge& operator=(Bridge&& other)noexcept;
	friend bool operator==(const Bridge& b1, const Bridge& b2);
	friend bool operator!=(const Bridge& b1, const Bridge& b2);
	void serialize(json& j) const;
	void deserialize(const json& j);
	Point::Color getColor() const;
	Point getStartPoint() const;
	Point getEndPoint() const;
	
	void setStartPoint(Point p);
	void setEndPoint(Point p);
	void setColor(Point::Color c);

	~Bridge() = default;

private:
	Point m_startPoint;
	Point m_endPoint;
	Point::Color m_color;
};