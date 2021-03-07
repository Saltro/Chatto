class Position:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def __repr__(self):
        return '({0}, {1})'.format(self.x, self.y)

    def __add__(self, other):
        if isinstance(other, Position):
            return Position(self.x + other.x, self.y + other.y)
        else:
            return self + Position(other[0], other[1])

    def __iadd__(self, other):
        return self + other

    def __eq__(self, other):
        if isinstance(other, Position):
            return True if self.x == other.x and self.y == other.y else False
        else:
            return self == Position(other[0], other[1])


if __name__ == '__main__':
    a = Position(1, 2)
    b = Position(3, 4)
    c = (0, -1)
    a+=b
    print(a)
    b+=c
    print(b.y)