import wave
from struct import unpack, pack

f = wave.open("./resources/sounds/success.wav","r")

print "Channels: ", f.getnchannels()
print "Sample width: ", f.getsampwidth()
print "Sample rate: ", f.getframerate()
print "Sample count: ", f.getnframes()

fout = open("out.dat","wb")
fout.write(pack("<I",int(f.getnframes())))
print pack("<I",f.getnframes())
d = pack("<I",f.getnframes())
print unpack("<I",d)
for x in xrange(f.getnframes()):
	sample = unpack("<H",f.readframes(1))[0]
	sample = sample/256 - 128
	#print sample
	
	fout.write(pack("<b",int(sample)))
f.close()
fout.close()
