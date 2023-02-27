import sys

if len(sys.argv) != 3:
	usage()
	exit(0)

file_a = open(sys.argv[1], 'r')
file_b = open(sys.argv[2], 'r')

a_lines = file_a.readlines()
b_lines = file_b.readlines()

if len(a_lines) != len(b_lines):
	print('The files have different line counts')
	exit(0)

found = False

for a_line in a_lines:
	for b_line in b_lines:
		if a_line == b_line:
			found = True
			break
	if not found:
		print('The files have a difference')
		exit(0)
print('The files are the same')
exit(0)


def usage():
	print('Usage: python output_equivalent.py <file_a> <file_b>')

