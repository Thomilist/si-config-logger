# si-config-logger

A small utility program for logging of information from [SPORTident Config+](https://www.sportident.com/products/96-software/156-sportident-config-plus.html).
It reads values from the interface using optical character recognition with [Tesseract OCR](https://github.com/tesseract-ocr/tesseract), allowing the user to more easily gather data on SPORTident devices.

## Motivation

Maintenance of SPORTident stations regularly involves checking the clocks and batteries.
Noting down the battery states is essential to fascilitate the relevant maintenance, but unfortunately, SPORTident Config+ only has limited logging features, and manual logging for each station by hand is slow and error-prone. 
This tool reduces the manual effort of reading and logging the relevant information to a few hotkey interactions.
