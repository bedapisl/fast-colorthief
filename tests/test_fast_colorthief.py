import fast_colorthief
import numpy as np
import cv2
import colorthief
import PIL
import time


def test_some_output_returned():
    result = fast_colorthief.get_dominant_color('tests/veverka_lidl.jpg', 10)
    assert result == (132, 124, 90)


def test_same_output():
    image_path = 'tests/veverka_lidl.jpg'

    fast_palette = fast_colorthief.get_palette(image_path, 5, 10)
    colorthief_orig = colorthief.ColorThief(image_path)
    original_palette = colorthief_orig.get_palette(5, 10)

    assert (fast_palette == original_palette)


def print_speed():
    image = cv2.imread('tests/veverka_lidl.jpg')
    image = PIL.Image.open('tests/veverka_lidl.jpg')
    image = image.convert('RGBA')
    image = np.array(image).astype(np.uint8)

    start = time.time()

    for i in range(1):
        fast_colorthief.get_palette(image, 5, 10)

    print(f'CPP {time.time() - start}')

    colorthief_orig = colorthief.ColorThief('tests/veverka_lidl.jpg')
    start = time.time()

    for i in range(1):
        colorthief_orig.get_palette(5, 10)

    print(f'Python {time.time() - start}')


if __name__ == '__main__':
    print_speed()
