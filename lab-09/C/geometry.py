import math

class Point:

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%r, %r)" % (self.x, self.y)

    def delta_x(self, dx):
        return Point(self.x+dx, self.y)

    def delta_y(self, dy):
        return Point(self.x, self.y+dy)

    def translate(self, dx, dy):
        return Point(self.x+dx, self.y+dy)

class Circle:

    def __init__(self, center, radius):
        self.center = center
        self.radius = radius

    def __repr__(self):
        return "Circle(%s, %r)" % (self.center, self.radius)

    def area(self):
        return math.pi * self.radius ** 2

    def perimeter(self):
        return math.pi * self.radius * 2

    def translate(self, dx, dy):
        return Circle(self.center.translate(dx, dy), self.radius)
