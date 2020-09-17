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

    iterations = 10

    start = time.time()

    for i in range(iterations):
        fast_colorthief.get_palette(image)

    print(f'CPP numpy {(time.time() - start) / iterations}')

    start = time.time()

    for i in range(iterations):
        fast_colorthief.get_palette('tests/veverka_lidl.jpg')

    print(f'CPP image path {(time.time() - start) / iterations}')

    start = time.time()

    for i in range(iterations):
        colorthief_orig = colorthief.ColorThief('tests/veverka_lidl.jpg')
        colorthief_orig.get_palette()

    print(f'Python image path {(time.time() - start) / iterations}')


if __name__ == '__main__':
    print_speed()
