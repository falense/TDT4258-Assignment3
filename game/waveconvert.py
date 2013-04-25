import wave, sys
from struct import unpack, pack
if (len(sys.argv) < 3):
	print "usage python waveconvert.py inputfile outputfile"
	exit(0)

inputfile = sys.argv[1]
outputfile = sys.argv[2]

f = wave.open(inputfile,"r")
fout = open(outputfile,"wb")

print "Channels: ", f.getnchannels()
print "Sample width: ", f.getsampwidth()
print "Sample rate: ", f.getframerate()
print "Sample count: ", f.getnframes()
fout.write(pack(">I",int(f.getnframes())))

for x in xrange(f.getnframes()):
	sample = unpack("<H",f.readframes(1))[0]
	sample = sample/256 - 128
	fout.write(pack("<b",int(sample)))
f.close()
fout.close()
