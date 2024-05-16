#!/usr/bin/python3

##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-jules.gresset
## File description:
## Main
##

import socket
import sys
import time
from signal import signal, SIGPIPE, SIG_DFL
signal(SIGPIPE,SIG_DFL)

class Player:
    """! Player class
    """
    def __init__(self, port, name, machine = "127.0.0.1"):
        """! Player class initializer

        @param port The port to which the player connects
        @param name The team name of the player
        @param machine The machine to which the player connects, defaults to "localhost"

        @return An instance of the Player class initialized with the specified port, name and machine
        """
        self.teamName = name
        self.port = port
        self.machine = machine
        self.sock = None
        self.requirements = [{}, { "nbPlayer": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0 }, { "nbPlayer": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0 }, { "nbPlayer": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0 }, { "nbPlayer": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0 }, { "nbPlayer": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0 }, { "nbPlayer": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0 }, { "nbPlayer": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1 }]
        self.level = 1
        self.intervals = [(0, 0), (1, 3), (4, 8), (9, 15), (16, 24), (25, 36), (37, 51), (52, 69), (70, 90)]
        self.inventory = { "food": 1260, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0 }
        self.available = None
        self.mapSize = None
        self.isChief = False

    def connect(self):
        """! Connects to the server
        """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect((self.machine, self.port))
        except Exception as e:
            print(f"Error in \"connect\": {e}")
            raise e

    def close(self):
        """! Closes the connection with the server
        """
        self.sock.close()

    def sendMsg(self, s):
        """! Sends a message to the server

        @param s The message to send to the srever
        """
        self.sock.send((s + "\n").encode())

    def recvMsg(self):
        """! Receives messages from the server

        @return The message that has been received
        """
        return self.sock.recv(8192).decode()

    def verifyMsg(self, s):
        """! Verifies messages

        @param s The message to verify

        @return The message after verification
        """
        ret = ""

        for m in s.split("\n")[:-1]:
            if m == "dead":
                print("This AI is dead")
                self.close()
                exit(0)
            elif m.split()[0] == "message" and not self.isChief:
                orient = int(m.split()[1][:-1])
                text = m.split()[2].split('_')
                if text[0] == "Start" and int(text[1]) == self.level:
                    if text[2] == self.teamName:
                        self.joinIncantation(orient)
                        ret = "ok"
                    else:
                        ret = "skip"
                elif text[0] == "Win":
                    if text[1] == self.teamName:
                        self.close()
                        exit(0)
                    else:
                        self.close()
                        exit(0)
            else:
                ret = m
        return ret


    def preparePlayer(self):
        """! Prepare the player after connection
        """
        self.recvMsg()
        self.sendMsg(self.teamName)
        msg = self.recvMsg().split('\n')
        self.available = int(msg[0])
        size = [int(i) for i in msg[1].split()]
        self.mapSize = (size[0], size[1])
        if self.available == 0:
            self.forkPlayer()
            self.forkPlayer()
            self.isChief = True

    def goForward(self):
        """! Command to move forward

        @return The value received from the server
        """
        self.sendMsg("Forward")
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        return ret

    def turnLeft(self):
        """! Command to turn left

        @return The value received from the server
        """
        self.sendMsg("Left")
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        return ret

    def turnRight(self):
        """! Command to turn right

        @return The value received from the server
        """
        self.sendMsg("Right")
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        return ret

    def look(self):
        """! Command to look around

        @return The value received from the server
        """
        self.sendMsg("Look")
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret != "" and (ret == "skip" or (ret[0] == "[" and len(ret) > 5)):
                return ret[1:-2]
        obj = ret[1:-1]
        return obj

    def getInventory(self):
        """! Command to get the inventory of the player

        @return The value received from the server
        """
        try:
            self.sendMsg("Inventory")
            self.inventory['food'] -= 1
            while 1:
                ret = self.verifyMsg(self.recvMsg())
                if ret != "" and (ret[0] == "[" and len(ret) > 5):
                    break
            obj = ret[1:-1]
            return obj
        except:
            return "ko"

    def broadcastMsg(self, msg):
        """! Command to broadcast a message

        @param msg The message to broadcast

        @return The value received from the server
        """
        self.sendMsg("Broadcast " + msg)
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        return ret

    def connectNbr(self):
        """! Command to get the number of unused slots in the team

        @return The value received from the server
        """
        self.sendMsg("Connect_nbr")
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if int(ret) in range(50):
                break
        return ret

    def forkPlayer(self):
        """! Command to lay an egg

        @return The value received from the server
        """
        self.sendMsg("Fork")
        self.inventory['food'] -= 42
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok"]:
                break
        return ret

    def ejectPlayers(self):
        """! Command to eject players

        @return The value received from the server
        """
        self.sendMsg("Eject")
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        return ret

    def takeObject(self, obj):
        """! Command to take an object on the ground

        @param obj The object to take

        @return The value received from the server
        """
        self.sendMsg("Take " + obj)
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        if ret == "ok":
            self.inventory[obj] += 126 if obj == "food" else 1
        return ret

    def setObject(self, obj):
        """! Command to set an object on the ground

        @param obj The object to set

        @return The value received from the server
        """
        self.sendMsg("Set " + obj)
        self.inventory['food'] -= 7
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["ok", "ko", "skip"]:
                break
        if ret == "ok":
            self.inventory[obj] -= 1
        return ret

    def incantation(self, starter):
        """! Command to start incantation

        @return The value received from the server
        """
        if starter:
            self.sendMsg("Incantation")
        self.inventory['food'] -= 300
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in ["Elevation underway", "ko"]:
                break
        while 1:
            ret = self.verifyMsg(self.recvMsg())
            if ret in [f"Current level: {self.level + 1}", "ko", "skip"]:
                break
        self.level += 1
        print(f"Team {self.teamName}: A player is now level {self.level}")
        return ret

    def takeAll(self):
        """! Take every elemnts on the ground
        """
        objSeen = self.look().lstrip().rstrip()
        for obj in objSeen.split(',')[0].split():
            if obj == "player":
                pass
            else:
                self.takeObject(obj)

    def getRequiredResources(self):
        """! List of the resources needed to level up

        @return A list of tuple or None
        """
        needed = []
        for key in self.requirements[self.level].keys():
            if key == "nbPlayer":
                pass
            elif self.requirements[self.level][key] > self.inventory[key]:
                needed.append((key, self.requirements[self.level][key] - self.inventory[key]))
        if needed != []:
            return needed
        return None

    def searchForFood(self):
        """! Move to the tile with the most food in vision

        """
        objSeen = self.look().lstrip().rstrip().split(',')
        count = [0] * len(objSeen)
        for i in range(len(objSeen)):
            count[i] = objSeen[i].count('food')
        index = count.index(max(count))
        if index == 0:
            self.takeAll()
            self.goForward()
            return
        for i in range(len(self.intervals)):
            if self.intervals[i][0] <= index <= self.intervals[i][1]:
                self.goToTile(i, index - (self.intervals[i][0] + i))
                break
        self.takeAll()

    def findStone(self, index):
        """! Go to the index and get stones
        """
        if index == 0:
            self.takeAll()
            self.goForward()
            return
        for i in range(len(self.intervals)):
            if self.intervals[i][0] <= index <= self.intervals[i][1]:
                self.goToTile(i, index - (self.intervals[i][0] + i))
                break
        self.takeAll()

    def searchForStone(self, neededStones):
        """! Search the stones required to level up

        @param neededStones List of the stones needed
        """
        if not neededStones:
            return
        for stone, nb in neededStones:
            objSeen = self.look().lstrip().rstrip().split(',')
            count = [0] * len(objSeen)
            for i in range(len(objSeen)):
                count[i] = objSeen[i].count(stone)
            index = count.index(max(count))
            while nb > 0:
                self.findStone(index)
                nb -= count[index]

    def setAllObjects(self):
        """! Set the objects on the ground to level up"""
        for key in self.requirements[self.level].keys():
            if key == "nbPlayer":
                pass
            else:
                for i in range(self.requirements[self.level][key]):
                    self.setObject(key)

    def getNbPlayersOnTile(self):
        tile = self.look().lstrip().rstrip().split(',')[0]
        return tile.count('player')

    def startIncantation(self):
        self.takeAll()
        self.setAllObjects()
        self.incantation(True)

    def findPlayers(self, looked):
        looked = looked.lstrip().rstrip().split(',')
        count = [0] * len(looked)
        for i in range(1, len(looked)):
            count[i] = looked[i].count('player')
        index = count.index(max(count))
        for i in range(len(self.intervals)):
            if self.intervals[i][0] <= index <= self.intervals[i][1]:
                self.goToTile(i, index - (self.intervals[i][0] + i))
                break

    def joinIncantation(self, orientation):
        for i in range(orientation // 2):
            self.turnLeft()
        if orientation % 2 == 1:
            while self.getNbPlayersOnTile() == 1:
                self.goForward()
                if self.inventory["food"] < 8000:
                    self.takeAll()
                look = self.look()
                if look.count("player") > 1:
                    self.findPlayers(look)
                    break
        else:
            while self.getNbPlayersOnTile() == 1:
                if self.inventory["food"] < 8000:
                    self.takeAll()
                look = self.look()
                if look.count("player") > 1:
                    self.findPlayers(look)
                    break
                self.goForward()
                if self.getNbPlayersOnTile() != 1:
                    break
                self.turnLeft()
                self.goForward()
                if self.getNbPlayersOnTile() != 1:
                    break
                self.turnRight()
        self.incantation(False)

    def gatherToLevelUp(self):
        nb = 0
        self.broadcastMsg(f"Start_{self.level}_{self.teamName}")
        while self.getNbPlayersOnTile() != self.requirements[self.level]["nbPlayer"]:
            while self.inventory["food"] < 8000:
                self.searchForFood()
            self.getInventory()
            if nb > 20:
                self.broadcastMsg(f"Start_{self.level}_{self.teamName}")
                nb = 0
            nb += 1
        self.startIncantation()

    def goToTile(self, nbForward, nbDir):
        """! Move to a specific tile

        @param nbForward Number of front movements
        @param nbDir Number of side movements
        """
        while nbForward != 0:
            self.goForward()
            nbForward -= 1
        if nbDir < 0:
            self.turnLeft()
            while nbDir != 0:
                self.goForward()
                nbDir += 1
        elif nbDir > 0:
            self.turnRight()
            while nbDir != 0:
                self.goForward()
                nbDir -= 1

    def start(self):
        """! Loop of the player"""
        while 1:
            if self.inventory["linemate"] >= 1:
                self.startIncantation()
                break
            self.takeAll()
            self.goForward()

        while 1:
            if self.isChief:
                if self.level == len(self.requirements):
                    # Win
                    # Send defeat to other team
                    self.broadcastMsg(f"Win_{self.teamName}")
                    print(f"The winner is team {self.teamName}")
                    return
                elif self.inventory["food"] < 10000:
                    self.searchForFood()
                else:
                    needed = self.getRequiredResources()
                    self.searchForStone(needed)
                    self.gatherToLevelUp()
            else:
                if self.inventory["food"] < 10000:
                    self.searchForFood()
                else:
                    self.getInventory()


def displayUsage():
    """! Display the usage of the program
    """
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

def verifyArgs(ac, av):
    """! Verify the given parameters

    @param ac Number of parameters
    @param av List of the parameters

    @return 0 if success and -1 in case of failure
    """
    if ac < 5 or ac > 7:
        return -1
    for i in range(1, ac, 2):
        if av[i] not in ["-p", "-n", "-h"]:
            return -1
    return 0

def main(ac, av):
    if ac == 2 and av[1] == "-help":
        displayUsage()
    if verifyArgs(ac, av) < 0:
        return 84
    if ac == 5:
        player = Player(int(av[2]), av[4])
    else:
        player = Player(int(av[2]), av[4], av[6])
    try:
        player.connect()
    except:
        return 84
    try:
        player.preparePlayer()
    except:
        player.close()
        return main(ac, av)
    player.start()
    player.close()
    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
