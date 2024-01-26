# From:
# https://saturncloud.io/blog/bresenham-line-algorithm-a-powerful-tool-for-efficient-line-drawing/

def bresenham_line(x1: int, y1: int, x2: int, y2: int):
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    slope = dy > dx

    if slope:
        x1, y1 = y1, x1
        x2, y2 = y2, x2

    if x1 > x2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1

    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    error = dx // 2
    y = y1
    ystep = 1 if y1 < y2 else -1

    points = []
    for x in range(x1, x2 + 1):
        coord = (y, x) if slope else (x, y)
        points.append(coord)
        error -= dy
        if error < 0:
            y += ystep
            error += dx

    return points

if (__name__ == "__main__"):
    coordinates = bresenham_line(1, 1, 2, 10)
    for index, coor in enumerate(coordinates):
        print(f"Pixel {index}: {coor}\n")

