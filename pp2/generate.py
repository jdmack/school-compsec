#!/usr/bin/python
import random

fsid = open("SID",'r')
lines = fsid.readlines()
lines = [line for line in lines if line.strip()]
sid = lines[0].strip()
fsid.close()
if len(sid) < 8:
    print "Please put your student ID and name in the SID file."
    exit(1)
else:
    print "Using SID: \""+lines[0].strip()+"\""

random.seed(sid)

# C function which puts a set of bytes in a blender. Moves the perm[i]-th byte
# to the i-th position. Operates on blocks that are the width of the
# permutation.
permuteCCode = """
// Precondition: permLen | fieldLen
void permute_field(char* field, const int fieldLen, const int* perm,
    const int permLen) {
  if (fieldLen % permLen != 0) {
    fprintf(stderr, "Error: permutation length does not divide field length.");
  }
  int index;  // Index in current field. 
  int base;  // Base index of the current permutation. 
  int permItr;  // Permutation iteration we're on. 
  char* tmp = malloc(permLen);  // A temporary field for our permutation.
  // For each time we are performing our permutation.
  for (permItr = 0; permItr < fieldLen / permLen; permItr++) { 
    base = permItr * permLen;  
    // tmp[i] gets field[perm[i]].
    for (index = 0; index < permLen; index++) {
      tmp[index] = field[base + perm[index]];
    }
    // field[i] gets field[perm[i]].
    for (index = 0; index < permLen; index++) {
      field[base + index] = tmp[index];
    }
  }
}
"""

# C code which applies an XOR key to a field. Operates on blocks the width of
# the xor key. 
xorCCode = """
void xor_field(char* field, const int fieldLen, const char* key,
    const int keyLen) {
  if (fieldLen % keyLen != 0) {
    fprintf(stderr, "Error: key length does not divide field length.");
  }
  int index;  // Index in current field. 
  int base;  // Base index of the current permutation. 
  int keyItr;  // Key iteration we're on. 
  // For each time we use the xor key. 
  for (keyItr = 0; keyItr < fieldLen / keyLen; keyItr++) { 
    base = keyItr * keyLen;  
    for (index = 0; index < keyLen; index++) {
      field[base + index] ^= key[index];
    }
  }
}
"""

# Exponential prime factorization method. Clearly okay for n<10 bit field
# lengths.  Used in getting xor key lengths and permutation lengths. 
def getPrimes(n):
    primfac = []
    d = 2
    while d*d <= n:
        while (n % d) == 0:
            primfac.append(d)
            n /= d
        d += 1
    if n > 1:
       primfac.append(n)
    return primfac

def generate_read_code(st_el,l):
    s = "  puts(\""+st_el+"?\\n\");\n"
    s = s+"  rd = get_line(tmp,"+str(l).strip()+");\n"
    s = s+"  memset(&(tmp[rd]),'\\0',"+str(l).strip()+"-rd);\n"
    s = s+"  memcpy(&(ce->"+st_el+"),tmp,"+str(l).strip()+");\n\n"
    return s

def trans_none(st_el,l):
    assign = "";
    # assign  = st_el+" = "+st_el+";"
    return ("char "+st_el+"["+str(l)+"];",assign)



def generate_xor(l):
    """ Generates an xor key up to length l that divides l, and returns a 
    C-style literal that can be used as a const char* for that key."""
    primes = getPrimes(l);
    keyLen = 1; 
    for i in range(0, len(primes)): 
        coin = random.randrange(0,2)
        if coin == 1: 
          keyLen *= primes[i]
    keyStr = "";
    for i in range(0, keyLen): 
      byteVal = random.randrange(0,256)
      byteStr = "\\x" + "{0:0{1}x}".format(byteVal, 2)
      keyStr += byteStr 
    return (keyLen, keyStr)

def trans_xor(st_el,l):
    """Xor a field by a given key."""
    (keyLen, key) = generate_xor(l)
    assign  = "char key"+st_el+"[" + str(l) + "] = \"" + key + "\";\n"
    assign += "  xor_field(ce->"+st_el+", "+str(l)+", "+"key"+st_el+", "+str(keyLen)+ ");"
    return ("char "+st_el+"["+str(l)+"];",assign)

def generate_perm(l):
    """Generates a blender permutation up to length l that divides l, and 
    returns a C-style literal that can be uased as a const int[] for that 
    permutation."""
    primes = getPrimes(l);
    permLen = 1; 
    for i in range(0, len(primes)): 
        coin = random.randrange(0,2)
        if coin == 1: 
          permLen *= primes[i]
    perm = range(0, permLen)
    random.shuffle(perm)
    return (permLen, '{' + str(perm)[1:-1] + '}')

def trans_reorder(st_el,l):
    """Uses a permutation from above, and "blends" a C field."""
    # If we are updating a "long", cast to char* and use its address. 
    (permLen, perm) = generate_perm(l)
    assign  = "int perm"+st_el+"[" + str(l) + "] = " + perm + ";\n"
    assign += "  permute_field(ce->"+st_el+", "+str(l)+", "+"perm"+st_el+", "+str(permLen)+");"
    return ("char "+st_el+"["+str(l)+"];",assign)

struct_elements = [("Title",500),
                   ("Director",300),
                   ("Writer",300),
                   ("Star_1",300),
                   ("Star_2",300),
                   ("Star_3",300),
                   ("Star_4",300),
                   ("Star_5",300),
                   ("Summary",2000),
                   ("Country",30), # Validated?
                   ("Budget",80),
                   ("Opening_Weekend",80),
                   ("Gross",80),
                   ("Runtime",80),
                   ("Aspect",40), # Validated?
                   ("Composer",300),
                   ("Average_Rating",3)]

element_transforms = [trans_xor,trans_reorder,trans_none,trans_xor,trans_reorder]

def generate_code():
    output_struct = "#ifndef _CMDB_STRUCT_H_\n#define _CMDB_STRUCT_H_\nstruct __attribute__((__packed__)) cmdb_entry{\n"
    output_assigns = ""
    output_reads = "#include <stdlib.h>\n#include \"cmdb_generate.h\"\n#include \"cmdb.h\"\nvoid new_entry(struct cmdb_entry* ce){\n  char tmp[2048];\n  int rd;\n"
    for (el,l) in struct_elements:

        # We never randomize title, cause it needs to be deleteable!
        if el == "Title":
            trans = 2
        else:
            trans = random.randrange(0,len(element_transforms))
        (o_s,o_a) = element_transforms[trans](el,l)
        output_struct = output_struct + o_s +"\n"
        output_assigns = output_assigns + "  " +o_a +"\n"

        output_reads = output_reads + generate_read_code(el,l)
    #TODO update the assigns
    output_assigns = output_reads + "\n" + output_assigns
    output_assigns = output_assigns + "}"
    output_struct = output_struct + "};\n#endif /*_CMDB_STRUCT_H_*/"
    return (output_struct,output_assigns)


(os,oa) = generate_code()
f_s = open("cmdb_struct.h",'w')
f_a = open("cmdb_generate.c",'w')
f_s.write(os);
f_a.write(oa);
f_a.write(permuteCCode);
f_a.write(xorCCode);
f_s.close();
f_a.close();
#print os
#print oa
#print permuteCCode
#print xorCCode
