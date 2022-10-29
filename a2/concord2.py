#!/usr/bin/env python3

import sys

def read_input():#all_input, excl_words, index_lines):
	for each_line in sys.stdin:
		line = each_line.strip()
		all_input.append(line)
	
	if(all_input[0] == "1"):
		print("Input is version 1, concord2.py expected version 2")
		sys.exit()
	
	divider = all_input.index("\"\"\"\"")
	excl_words = all_input[2:divider]
	index_lines = all_input[divider+1:]
	
def get_words_to_index(line):#, words_to_index, excl_words):
	line.split()
	for each_word in line:
		print(each_word)
		is_excl = False
		for excl_word in excl_words:
			if(each_word == excl_word):
				is_excl = True
				#break
		if(not(is_excl)):
			words_to_index.append(each_word)
		

def main():
	all_input = []
	excl_words = []
	index_lines = []
	words_to_index = []
	print("reading")
	read_input()#all_input, excl_words, index_lines)
	print("got input")
	print(len(index_lines))
	for each in index_lines:
		#look for words to index
		temp_line = each[:]
		get_words_to_index(temp_line)#, words_to_index, excl_words)
		
	print("hello")
	print(len(words_to_index))
	for each in words_to_index:
		print(each)
		print("a word")
	
	for each in index_lines:
		print(each)
	#hello

if __name__ == "__main__":
	main()
