# Fast colortheif

A Python module for selecting most dominant colors in the image. Based on https://github.com/fengsp/color-thief-py, but is much faster.

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

## Benchmark
1200 x 1200 jpg image


| Algorithm | Time per image |
| ----------| -------------- |
| Fast colorthief (input numpy array) | 0.0012s |
| Fast colorthief (input filename) | 0.034s | 
| Reference (https://github.com/fengsp/color-thief-py) (input filename) | 0.509s |
 
## How does it work
Backend is written in C++ for better performance.

Uses Modified Median Cut Quantization algorithm.
