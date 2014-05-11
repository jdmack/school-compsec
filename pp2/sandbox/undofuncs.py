#Undo the xor_field function in cmdb_generate. 
#Literally a direct translation of original C function to Python
def undo_xor(field, field_len, xor_key, xor_key_len):

    if (field_len % xor_key_len != 0):
        print "undo_xor error"
        return
  
    for keyItr in range (0,  field_len / xor_key_len): 
        base = keyItr * xor_key_len;  
        for index in range (0, xor_key_len): 
            field[base + index] = field[base+index] ^ xor_key[index]
    return field
    


#Undo permute_field
def undo_permute(field, fieldLen, perm, permLen):

    tmp = [0 for i in range(permLen)]

    if(fieldLen % permLen != 0):
        print "undo_permute error"
        return
    for permItr in range( 0,fieldLen / permLen): 
        base = permItr * permLen  

        #copy into tmp
        for index in range(0,permLen):
            tmp[perm[index]] = field[index]
            
        #copy back into field
        for index2 in range(0,permLen):
            field[base+index2] = tmp[index2]
    return field

def run_test():
  
    testfield = [1,2,3,4,5,6]
    testkey = [3,2,1]

    print "orig"

    for i in range (0,6):
        print testfield[i]

    undo_xor (testfield,6,testkey,3)

    print "encrypted"

    for i in range (0,6):
        print testfield[i]
    
    print "decrypted"

    undo_xor (testfield,6,testkey,3)
    for i in range (0,6):
        print testfield[i]
    #############################################
    
    testfield2 = [10,5,7,10,5,7,10,5,7]
    perm = [1,2,0]
    print "orig w/o perm"
    for i in range(0,len(testfield2)):
        print testfield2[i]

    print "undo_perm"
    undo_permute(testfield2,len(testfield2),perm,len(perm))
    for i in range(0,len(testfield2)):
        print testfield2[i]
        
    testfield3 = [1,2,3,4,5]
    perm3 = [2,4,1,0,3]
    print "orig w/o perm3"
    for i in range(0,len(testfield3)):
        print testfield3[i]

    print "undo_perm3"
    undo_permute(testfield3,len(testfield3),perm3,len(perm3))
    for i in range(0,len(testfield3)):
        print testfield3[i]
    
    
        


#run_test()
       

  
