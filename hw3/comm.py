#!/usr/bin/python
import sys, argparse, string

class comm:
     def __init__(self, file1, file2):
        if (file1 == "-"):
           self.line1 = sys.stdin.readLines()
        else:
            f1 = open(file1, 'r')
            self.line1 = f1.readlines()
            f1.close()
        if (file2 == "-"):
            self.line2 = sys.stdin.readlines()
        else:
           f2 = open(file2, 'r')
           self.line2 = f2.readlines()
           f2.close()


     def sortedc(self, op1, op2, op3):
         i, j = 0, 0
         while i in range(len(self.line1)) and j in range(len(self.line2)):
             if self.line1[i] < self.line2[j]:
                self.printc(self.line1[i], 1, op1, op2, op3)
                i += 1

             elif self.line1[i] == self.line2[j]:
                 self.printc(self.line1[i], 3, op1, op2, op3)
                 i += 1
                 j += 1

             elif self.line2[j] < self.line1[i]:
                self.printc(self.line2[j], 2, op1, op2, op3)
                j += 1
         
         while i in range(len(self.line1)):
                self.printc(self.line1[i], 1, op1, op2, op3)
                i += 1
         while j in range(len(self.line2)):
                self.printc(self.line2[j], 2, op1, op2, op3)
                j += 1


     def unsortedc(self, op1, op2, op3):
      self.line1[len(self.line1)-1] = self.line1[len(self.line1)-1].strip('\n')
      self.line2[len(self.line2)-1] = self.line2[len(self.line2)-1].strip('\n')
      self.line1[len(self.line1)-1] += '\n'
      self.line2[len(self.line2)-1] += '\n'
      for i in self.line1:
        if i not in self.line2:
           self.printc(i, 1, op1, op2, op3)
        else:
           self.printc(i, 3, op1, op2, op3)
           self.line2.remove(i)

      
      for j in self.line2:
           self.printc(j, 2, op1, op2, op3)
      


     def printc(self, line, c, op1, op2, op3):
        if c == 1:
           if op1:
              return
           elif not op1:
              sys.stdout.write("{0}".format(line))
        elif c == 2:
           if op2:
               return
           elif not op2:
                if not op1:
                   sys.stdout.write("{0}{1}".format('	', line))
                elif op1:
                   sys.stdout.write("{0}".format(line))
        elif c == 3:
           if op3:
                return
           elif not op3:
                if not op1:
                   if not op2:
                     sys.stdout.write("{0}{1}".format('		', line))
                   elif op2:
                     sys.stdout.write("{0}{1}".format('	', line))
                elif op1:
                    if not op2:
                      sys.stdout.write("{0}{1}".format('	', line))
                    elif op2:
                      sys.stdout.write("{0}".format(line))

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

Compare the lines in FILE1 and FILE2."""

    parser = argparse.ArgumentParser(description='Compare Files')
    parser.add_argument('file1')
    parser.add_argument('file2')
    parser.add_argument('-1', dest='suppresscol1', action='store_true',
                  default=False, help='suppress the output unique to file1')
    parser.add_argument('-2', dest='suppresscol2', action='store_true',
                  default=False, help='suppress the output unique to file2')
    parser.add_argument('-3', dest='suppresscol3', action='store_true',
         default=False, help='suppress the output duplicated in both files')
    parser.add_argument('-u', dest='unsorted', action='store_true',
                  default=False, help='do compare for unsorted files')
    args = parser.parse_args()
    try:
        op1 = bool(args.suppresscol1)
        op2 = bool(args.suppresscol2) 
        op3 = bool(args.suppresscol3)
        unsort = bool(args.unsorted)
    except:
        parser.error("invalid option")
    
    input_file1 = args.file1
    input_file2 = args.file2

    try:
        compare = comm(input_file1, input_file2)
        if unsort == True:
            compare.unsortedc(op1, op2, op3)
        else:
            compare.sortedc(op1, op2, op3)
    except (OSError) as err:
           parser.error("OSError")
if __name__ == "__main__":
    main() 
