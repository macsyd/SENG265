#!/usr/bin/env python3

import sys

def check_excl(line, excl_words):
	index_words = []
	temp = line.split(" ")
	for each_word in temp:
		is_excl = False
		for excl_word in excl_words:
			if(each_word == excl_word):
				is_excl = True
				break
		if(not is_excl):
			index_words.append(each_word)
	
	return index_words

def print_line(line, index):
	line[index] = line[index].upper()
	out_line = " ".join(line)
	#out_line = out_line.split("")
	output = []
	for i in range(70):
		output.append(" ")
	ind = 30-1
	for each in line[index]:
		output[ind] = each
		ind += 1
	print(output)
	#print(out_line)

def find_indexes(index_word, index_lines):
	for each_line in index_lines:
		temp_line = each_line.split(" ")
		for each_word in temp_line:
			if(each_word == index_word):
				print_line(temp_line, temp_line.index(index_word))
		

def main():
	all_input = []
	excl_words = []
	index_lines = []
	words_to_index = []
	
	#read in input
	for each_line in sys.stdin:
		line = each_line.strip()
		all_input.append(line)
	
	if(all_input[0] == "1"):
		print("Input is version 1, concord2.py expected version 2")
		sys.exit()
	
	divider = all_input.index("\"\"\"\"")
	excl_words = all_input[2:divider]
	index_lines = all_input[divider+1:]
	
	#find words to index
	for each in index_lines:
		words_to_index.extend(check_excl(each, excl_words))
	
	#sort list of index words & remove duplicates
	words_to_index = set(words_to_index)
	words_to_index = list(words_to_index)
	words_to_index.sort()
	
	#output each index word in the line it is found in
	for each_word in words_to_index:
		find_indexes(each_word, index_lines)


if __name__ == "__main__":
	main()
