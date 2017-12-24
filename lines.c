#include <stdio.h> 
/* scans input from a file and prints it line by line with
   the width of the line */
int main (void) { 
  int width = 0; 
  int pos = 0; 
  char c = 'a'; 
  char ch[1024];
  /* while it is not at the end of the file */
  while (!feof(stdin)) {
    width = 0;
    scanf ("%c", &c);
    /* if the first character is not at the end of the line */
    if (c != '\n') {
      ch[pos] = c; /* puts first character in array */
      while (ch[pos] != '\n') { /* while current character is not 
				   end of line */
	if (ch[pos] == '\t') {
	  width += (8 - (width % 8)); /* width with tab character by 
					 calculating how far it is from 8 */
	}else {
	  width++;
	}
	pos++;
	scanf ("%c", &c); /* scans the next character */
	ch[pos] = c; /* puts the characters in the array */
      }
    }
    c = '\n'; /* after line set last character to a new line */
    ch[pos] = c;
    if (!(feof(stdin)) && width <= 80) {
      printf ("  %4d> ", width);
    } else if (width > 80) {
      printf ("X %4d> ", width);
    }
    pos = 0;
    /* prints characters in array while not at the end 
       of the line */
    while (!(feof(stdin)) && ch[pos] != '\n') { 
      printf ("%c", ch[pos]);
      pos++;
    }
    pos = 0;
    /* if not at the end of the file print a new line */
    if (!feof(stdin)) { 
      printf ("\n");
    }
  }
  return 0;
}
