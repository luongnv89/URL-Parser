with open('generic.txt') as old:
	for line in old:
		line.strip()
		mlength = len(line)-1
		with open('generic-'+str(mlength)+'.txt', 'a') as new:
			new.write(line)