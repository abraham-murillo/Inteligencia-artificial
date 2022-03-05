from environment import Environment
from random import randint


class Vacuum:
    __currentRoom = 0
    __startingRoom = 0
    __operationsDone = 0
    __totalPerformance = 0
    environment = Environment()

    def __init__(self):
        print("Number of rooms for each state: ", self.environment.getRooms())
        print("Number of states: ", pow(2, self.environment.getRooms()))
        print("\n\n")
        for state in self.environment.getStates():
            self.__currentRoom = self.__startingRoom = randint(
                1, self.environment.getRooms()
            )
            self.__operationsDone = self.environment.vacuumMoves(
                self.__startingRoom, state
            )
            self.__totalPerformance += self.performance(state)
            self.show(state)
        print("Total average performance: ", self.totalAveragePerformance())

    def totalAveragePerformance(self):
        numberOfWorlds = pow(2, self.environment.getRooms())
        return float(self.__totalPerformance) / numberOfWorlds

    def performance(self, state):
        if self.environment.optimalSolution(self.__startingRoom, state) == 0:
            return 1
        return float(self.__operationsDone) / self.environment.optimalSolution(
            self.__startingRoom, state
        )

    def show(self, state):
        print("Current room: ", self.__currentRoom)
        print("Performance: ", self.performance(state))
        self.environment.show(state)
