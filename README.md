# Fast colortheif

A Python module for selecting most dominant colors in the image. Based on https://github.com/fengsp/color-thief-py, but is much (~20x times) faster.

## Installation
```
pip install fast_colorthief
```

## Example
```
import fast_colorthief

image_path = 'image.jpg'

dominant_color = fast_colorthief.get_dominant_color(image_path)
color_palette = fast_colorthief.get_palette(image_path)
```

## How does it work
Backend is written in C++ for better performance.

Uses Modified Median Cut Quantization algorithm.
