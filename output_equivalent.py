import sys

if len(sys.argv) != 3:
	usage()
	exit(1)

file_a = open(sys.argv[1], 'r')
file_b = open(sys.argv[2], 'r')

a_lines = file_a.readlines()
b_lines = file_b.readlines()

found = False

for a_line in a_lines:
	for b_line in b_lines:
		if a_line == b_line:
			found = True
			break
	if not found:
		print('The files have a difference')
		exit(1)
print('The files are the same')
exit(0)


def usage():
	print('Usage: python output_equivalent.py <file_a> <file_b>')

