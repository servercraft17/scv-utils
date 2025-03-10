from __future__ import annotations
from typing import overload
import math

CMP_EPSILON: float = 0.00001

def ___clamp(n: float, _min: float, _max: float) -> float:
    return min(max(n, _min), _max)

def ___snapped(v: float, step: float) -> float:
    return v if step == 0 else math.floor(val/step+0.5)*step

class Vector2:
    def __init__(self, x: float, y: float = None) -> None:
        if y is None:
            self.x = x
            self.y = x
        else:
            self.x = x
            self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"
    
    def __repr__(self) -> str:
        return f"Vector2(x={self.x}, y={self.y})"

    @overload
    def __eq__(self, other: Vector2) -> bool: return NotImplemented
    @overload
    def __eq__(self, other: float) -> bool: return NotImplemented
    def __eq__(self, other: object) -> bool:
        if isinstance(other, Vector2):
            return self.x == other.x and self.y == other.y
        elif isinstance(other, (int, float)):
            return self.x == other and self.y == other
        return NotImplemented
    
    @overload
    def __lt__(self, other: Vector2) -> bool: return NotImplemented
    @overload
    def __lt__(self, other: float) -> bool: return NotImplemented
    def __lt__(self, other: object) -> bool:
        if isinstance(other, Vector2):
            return self.len() < other.len()
        elif isinstance(other, (int, float)):
            return self.len() < other
        return NotImplemented
    
    @overload
    def __gt__(self, other: Vector2) -> bool: return NotImplemented
    @overload
    def __gt__(self, other: float) -> bool: return NotImplemented
    def __gt__(self, other: object) -> bool:
        if isinstance(other, Vector2):
            return self.len() > other.len()
        elif isinstance(other, (int, float)):
            return self.len() > other
        return NotImplemented
    
    @overload
    def __le__(self, other: Vector2) -> bool: return NotImplemented
    @overload
    def __le__(self, other: float) -> bool: return NotImplemented
    def __le__(self, other: object) -> bool:
        if isinstance(other, Vector2):
            return self.len() <= other.len()
        elif isinstance(other, (int, float)):
            return self.len() <= other
        return NotImplemented
    
    @overload
    def __ge__(self, other: Vector2) -> bool: return NotImplemented
    @overload
    def __ge__(self, other: float) -> bool: return NotImplemented
    def __ge__(self, other: object) -> bool:
        if isinstance(other, Vector2):
            return self.len() >= other.len()
        elif isinstance(other, (int, float)):
            return self.len() >= other
        return NotImplemented
    
    def __neg__(self) -> Vector2: return Vector2(-self.x, -self.y)
    def __pos__(self) -> Vector2: return Vector2(+self.x, +self.y)
    def __invert__(self) -> Vector2: return self*-1
    def __pow__(self, other: float) -> Vector2: return Vector2(self.x**other, self.y**other)
    
    @overload
    def __add__(self, other: Vector2) -> Vector2: return NotImplemented
    @overload
    def __add__(self, other: float) -> Vector2: return NotImplemented
    def __add__(self, other: object) -> Vector2:
        if isinstance(other, Vector2):
            return Vector2(self.x + other.x, self.y + other.y)
        elif isinstance(other, (int, float)):
            return Vector2(self.x + other, self.y + other)
        return NotImplemented
    
    @overload
    def __sub__(self, other: Vector2) -> Vector2: return NotImplemented
    @overload
    def __sub__(self, other: float) -> Vector2: return NotImplemented
    def __sub__(self, other: object) -> Vector2:
        if isinstance(other, Vector2):
            return Vector2(self.x - other.x, self.y - other.y)
        elif isinstance(other, (int, float)):
            return Vector2(self.x - other, self.y - other)
        return NotImplemented
    
    @overload
    def __mul__(self, other: Vector2) -> Vector2: return NotImplemented
    @overload
    def __mul__(self, other: float) -> Vector2: return NotImplemented
    def __mul__(self, other: object) -> Vector2:
        if isinstance(other, Vector2):
            return Vector2(self.x * other.x, self.y * other.y)
        elif isinstance(other, (int, float)):
            return Vector2(self.x * other, self.y * other)
        return NotImplemented
    
    @overload
    def __truediv__(self, other: Vector2) -> Vector2: return NotImplemented
    @overload
    def __truediv__(self, other: float) -> Vector2: return NotImplemented
    def __truediv__(self, other: object) -> Vector2:
        if isinstance(other, Vector2):
            return Vector2(self.x / other.x, self.y / other.y)
        elif isinstance(other, (int, float)):
            return Vector2(self.x / other, self.y / other)
        return NotImplemented

    def dot(self, other: Vector2) -> float: return self.x*other.x + self.y*other.y
    def len(self) -> float: return math.sqrt(self.x*self.x + self.y*self.y)
    def len2(self) -> float: return self.x*self.x + self.y*self.y
    
    def move_towards(self, dest: Vector2, speed: float, delta: float = None) -> Vector2:
        dst: Vector2 = dest - self
        l: float = dst.len()
        if delta is None:        
            return dest if l < CMP_EPSILON else self+((dst/l)*speed)
        return dest if l <= delta or l < CMP_EPSILON else self+((dst/l)*(speed*delta+delta))

    def distance_from(self, to: Vector2) -> float:
        return math.sqrt((to.x-self.x)*(to.x-self.x)+(to.y-self.y)*(to.y-self.y))
    def distance2_from(self, to: Vector2) -> float:
        return math.sqrt((to.x-self.x)*(to.x-self.x)+(to.y-self.y)*(to.y-self.y))

    def direction_from(self, to: Vector2) -> Vector2:
        return (to-self).normalized()

    def rotated(self, by: float) -> Vector2:
        sine: float = math.sin(by)
        cos: float = math.cos(by)
        return Vector2(self.x*cos-self.y*sine, self.x*sine+self.y*cos)

    def project(self, to: Vector2) -> Vector2:
        return to * (self.dot(to) / to.len2())
    
    def clamp(self, min: Vector2, max: Vector2) -> Vector2:
        return Vector2(___clamp(self.x, min.x, max.x), ___clamp(self.y, min.y, max.y))

    def snapped(self, step: Vector2) -> Vector2:
        return Vector2(___snapped(self.x, step.x), ___snapped(self.y, step.x))
    
    def slide(self, normal: Vector2) -> Vector2:
        return self - (normal * self.dot(normal))
    
    def reflect(self, normal: Vector2) -> Vector2:
        return ((normal*2)*self.dot(normal)) - self
    
    def bounce(self, normal: Vector2) -> Vector2:
        return -self.reflect(normal)
    
    def normalize(self) -> None:
        l: float = self.len2()
        if not l == 0:
            l=math.sqrt(l)
            self.x /= l
            self.y /= l

    def normalized(self) -> Vector2:
        l: float = self.len2()
        if not l == 0:
            l=math.sqrt(l)
            return Vector2(self.x/l, self.y/l)
        return ZeroDivisionError

    def is_normalized(self) -> bool:
        return self.len() == 1
