import subprocess
from PIL import Image
path = raw_input("path: ")
output = raw_input("output path: ")
file = Image.open(path)
pixels = file.convert("RGBA")
w = input("width: ")
h = input("height: ")
pixelArray = [[0 for y in range(h)] for x in range(w)]
for one in range(w):
	for two in range(h):
		r,g,b,a = pixels.getpixel((one,two))
		pixelArray[one][two] = str(r) + " " + str(g) + " " + str(b) + " " + str(a) + " "
file2 = open(output,"w")
for a in range(w):
	for b in range(h):
		file2.write(pixelArray[a][b])
file2.close()
subprocess.check_call(["editFile.exe", str(output), str(w), str(h)])
