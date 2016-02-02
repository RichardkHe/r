from subprocess import call, Popen, PIPE
import re

K_vals = [0, 1, 2,10,40,100,400,1000]
errors = [0.0001, 0.0003, 0.0005, 0.0007,  0.001]

for e in errors:
	print("="*100)
	print("e = " + str(e))
	for k in K_vals	:
		command= ["./esim", "B", "50", str(k), "4000", str(e), "0", "0" ,"5000000", "5", "1534546", "2133323" ,"377" ,"456548" ,"59998"]
		#call(["./esim", "I", "50", str(k), "4000", str(e), "0", "0" ,"5000000", "5", "1534546", "2133323" ,"377" ,"456548" ,"59998"])
		p = Popen(command, stdout=PIPE)
		text = p.stdout.read()
		#retcode = p.wait()
		#m = re.match("(*)", text)
		print(text)

