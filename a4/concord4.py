import sys
import re

#define constants
FRONT_LINE_LEN = 20
BACK_LINE_LEN = 30+1

class concord:
    '''
    Class that creates a full concordance from text input.
    '''

    def __init__(self, input=None, output=None):
        '''
        Concord class constructor that initializes attributes:
            self.input: path to the input file or stdin
            self.output: path to the output file or None
            self.all_lines: list of all lines in input
        
        Writes to the output file if one is provided.
        '''
        self.input = input
        self.all_lines = self.__get_all_lines(self.input)
        self.output = output
        if(self.output != None):
            self.__output_to_file()

    def __output_to_file(self):
        '''
        Writes the results of full_concordance to the given file.
        '''
        f = open(self.output, "w")
        if(f == None):
            print("Did not open file correctly")
            exit()
        results = self.full_concordance()
        [f.write(each + "\n") for each in results]
        f.close()

    def __get_all_lines(self, input):
        '''
        Returns a list of all lines in either the input file or stdin if no file is given.
        '''
        all_lines = []
        if(input == None):
            for each in sys.stdin:
                all_lines.append(each.strip())
        else:
            f = open(input, "r")
            if(f == None):
                print("Did not open file correctly")
                exit()
            lines = f.readlines()
            f.close()
            for each in lines:
                all_lines.append(each.strip())
        if(all_lines[0] == "1"):
                print("Input is version 1, concord2.py expected version 2")
                exit()
        return all_lines

    def __get_input_lines(self):
        '''
        Returns a list of all lines to index from the input.
        '''
        index = self.all_lines.index("\"\"\"\"")
        input_lines = self.all_lines[index+1:]
        return input_lines

    def __get_excl_words(self):
        '''
        Returns a list of all the exclusion words from the input.
        '''
        index = self.all_lines.index("\"\"\"\"")
        excl_words = self.all_lines[2:index]
        return excl_words

    def __check_excl(self, excl, word):
        '''
        Checks if a given word is in the list of exclusion words.
        '''
        for each in excl:
            m = re.match(word, each, re.IGNORECASE)
            if m:
                return False
        return True

    def __get_index_words(self, lines, excl):
        '''
        For each word in each line of the provided lines, checks if it is an exclusion word.
        If it is not, adds it to a list and returns this list once all words have been checked.
        '''
        index_words = []
        for each_line in lines:
            temp_line = each_line.split(" ")
            [index_words.append(each.upper()) for each in temp_line if self.__check_excl(excl, each)]
        index_words = set(index_words)
        index_words = list(index_words)
        index_words.sort()
        return index_words

    def __format_line(self, word, line, word_pattern):
        '''
        Splits line into three parts, removes extra words from the front and back part, 
        adds spaces to the front part, joins the parts into one string, and returns the formatted string.
        '''
        match = re.search(r"^(.*)" + word + "(.*)$", line, re.IGNORECASE)
        front_line = match.group(1)
        while(len(front_line) > FRONT_LINE_LEN):
            front_line = re.sub(r"^\w+ ", "", front_line)
        front_line = "".join([" "*(10+FRONT_LINE_LEN-len(front_line)-1), front_line])
        back_line = match.group(2)
        while((len(back_line)+len(word)) > BACK_LINE_LEN):
            back_line = re.sub(r" \w+$", "", back_line)
        output = "".join([front_line, word, back_line])
        return output

    def __output_lines(self, word, lines):
        '''
        Given a word, searches for it in each element of lines.
        Returns a list of strings for each time word appears in a line.
        '''
        output = []
        word_pattern = re.compile(r"\b" + re.escape(word) + r"\b", re.I)
        for each_line in lines:
            m = word_pattern.search(each_line)
            if m:
                output.append(self.__format_line(word, each_line, word_pattern))
        return output

    def full_concordance(self):
        '''
        Gets lists of exclusion words, input lines, and words to index.
        Returns a list of strings (the concordance).
        '''
        output_lines = []
        excl_words = self.__get_excl_words()
        input_lines = self.__get_input_lines()
        index_words = self.__get_index_words(input_lines, excl_words)
        [output_lines.extend(self.__output_lines(each, input_lines)) for each in index_words]
        return output_lines
