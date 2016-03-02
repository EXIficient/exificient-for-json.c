#!/bin/sh
cd Debug && make && ./exificient-for-json.exe && cd .. && cd Release && make && ./exificient-for-json.exe 