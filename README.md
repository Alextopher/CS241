## Notes from the future:

This is an archive of a piece of software I wrote for my Computer Organization course at Clarkson University in Spring of 2020. It is basically an implementation of the lz77 compression scheme. The original problem statement can be found [here](https://lin-web.clarkson.edu/class/cs241/as2.5-s20.html). I will work on creating an archive of the assignment. I've cleaned up the README but otherwise the software is unchanged.

Jabber is encode

Wocky is decode

atob converts "ASCII" to "Binary". Where binary is made up of ascii "0"s and "1"s.

btoa reverses atob.

# Jabberwocky

My implementations for jabber and wocky use a nice fact about our compression table. Every prefix we add to the table is a single bit appended to some previously seen prefix. This can be represented with some nice data structures.

## Jabber

TJ had the idea to use a labeled binary tree that we can descend while reading in the prefix. Reading in a zero means descending left and reading a one descends right. Once we reach a leaf node we print it's label in binary and we add a new child node in the direction of the next bit, labeled with tree size + 1.

![](tree.png)

Using a binary tree in this way means the time complexity for reading in a prefix is proportional to the length of the prefix and not directly related to the size of the tree. 

Ryan and I worked together on implementing Jabber but we wrote our own code.

## Wocky

I wrote wocky alone and once again used the "each prefix = some previous prefix + 1 bit" property. Since at each step we read an index (integer) and find the prefix (string) at that index an array of cstrings would be sufficent. `char ** table = malloc(size * sizeof(char*))`. However, we can be better. Instead of storing cstrings I store a pointer to the previous prefix and 1 character representing the 1 new bit. 

![](table.png)

Printing becomes a little more complicated since we can no longer just fprintf a cstring. All it requires is a little bit of recursive decent, unfortunately this can't be written tail recursively. 

## atob and btoa

I tried to optimize as much as possible without digging into assembly and calculating running times. They use lots of bit wise opperators. 
