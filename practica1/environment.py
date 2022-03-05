from random import randint, choice

MAX_ROOMS = 5
CLEAN = True
DIRTY = False


class Environment:
    __rooms = 0
    __state = []
    __states = []

    def __init__(self):
        self.__rooms = randint(1, MAX_ROOMS)
        self.generateWorlds()

    def generateWorlds(self):
        for mask in range(0, pow(2, self.__rooms)):
            currentWorld = []
            for bit in range(0, self.__rooms):
                if (mask >> bit) & 1:
                    currentWorld.append(True)
                else:
                    currentWorld.append(False)
            self.__states.append(currentWorld)

    def show(self, state):
        print("State of each room: ", state)
        print("\n\n")

    def isClean(self, room):
        if room < 1 or self.__rooms < room:
            raise TypeError("Room is out of bounds.")
        return self.__state[room - 1]

    def vacuumMoves(self, startingRoom, state):
        # La aspiradora se mueve hasta la izquierda,
        # después recorre todas las posiciones hasta la derecha
        trashCount = 0
        for col in range(0, self.__rooms):
            if state[col] == DIRTY:
                trashCount += 1
        return self.__rooms - 1 + startingRoom + trashCount

    def optimalSolution(self, startingRoom, state):
        # startingRoom = self.__currentRoom
        solutionOne = solutionTwo = 0

        # To left and then to right
        currentRoom = indexRoom = startingRoom
        while indexRoom >= 1:
            if state[indexRoom - 1] == DIRTY:
                solutionOne += abs(currentRoom - indexRoom) + 1
                currentRoom = indexRoom
            indexRoom -= 1

        indexRoom = startingRoom + 1
        while indexRoom <= self.__rooms:
            if state[indexRoom - 1] == DIRTY:
                solutionOne += abs(currentRoom - indexRoom) + 1
                currentRoom = indexRoom
            indexRoom += 1

        # To right and then to left
        currentRoom = indexRoom = startingRoom
        while indexRoom <= self.__rooms:
            if state[indexRoom - 1] == DIRTY:
                solutionTwo += abs(currentRoom - indexRoom) + 1
                currentRoom = indexRoom
            indexRoom += 1

        indexRoom = startingRoom - 1
        while indexRoom >= 1:
            if state[indexRoom - 1] == DIRTY:
                solutionTwo += abs(currentRoom - indexRoom) + 1
                currentRoom = indexRoom
            indexRoom -= 1

        return min(solutionOne, solutionTwo)

    def getRooms(self):
        return self.__rooms

    def getStates(self):
        return self.__states
