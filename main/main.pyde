import random
import copy

class Object:
    def __init__(self, row, col, img, id):
        self.row = row
        self.col = col    
        self.img = img 
        self.id = id   

class ButtonPosition:
    def __init__(self, left, top, width, height):
        self.left = left
        self.top = top
        self.width = width
        self.height = height
        
n = 1
m = 5
speed = 50
grid = [[0] * m for it in range (n) ]

objectSize = 80
offset = 20

buttonsWidth = objectSize * 4   
gridWidth = objectSize * m
gridHeight = objectSize * n

appWidth = gridWidth + buttonsWidth + 100
appHeight = gridHeight  + 100

performanceResult = 0.0
currentlyAdding = 0

def drawAt(row, col, img):
    image(img, col * objectSize, row * objectSize, objectSize, objectSize)

def drawObject(object):
    drawAt(object.row, object.col, object.img)
    
def insideRect(x, y, left, top, width, height):
    return left <= x < left + width and top <= y < top + height

def overButton(button):
    return insideRect(mouseX, mouseY, button.left, button.top, button.width, button.height);

def drawTextButton(button, buttonText):
    fill(255)
    stroke(0)
    rect(button.left, button.top, button.width, button.height) 
    textSize(20);
    fill(0)
    text(buttonText, button.left + button.height, button.top + button.height);

def drawImageButton(button, buttonImage):
    fill(255)
    rect(button.left, button.top, button.width, button.height) 
    image(buttonImage, button.left, button.top, button.width, button.width)
    
def clearGrid():
    for row in range(0, n):
        for col in range(0, m):
            grid[row][col] = 0

def setup():    
    print(appWidth, appHeight)
    size(appWidth, appHeight + 50)   
    
    global vacuum, ground, trash, objectsArray
    ground = Object(-1, -1, loadImage("assets/singleFloor.jpeg"), 0)
    vacuum = Object(0, 0, loadImage("assets/vacuum.png"), 1)
    trash = Object(-1, -1, loadImage("assets/trash.png"), 2)
    objectsArray = [ground, vacuum, trash]
    
    global buttonCalculate, buttonAddVacuum, buttonAddTrash, outputPerformanceResult
    buttonCalculate = ButtonPosition(gridWidth + 20, 20, 100, 20);
    buttonAddVacuum = ButtonPosition(gridWidth + 20, 60, objectSize, objectSize);
    buttonAddTrash = ButtonPosition(gridWidth + 30 + objectSize, 60, objectSize, objectSize);
    outputPerformanceResult = ButtonPosition(gridWidth + 140, 20, 100, 20)
        
    
def draw():
    #if play:
     #   findWay()
      #  delay(speed)
      
    background(255)
    drawTextButton(buttonCalculate, "Calcular")
    drawImageButton(buttonAddVacuum, vacuum.img)
    drawImageButton(buttonAddTrash, trash.img)
    drawTextButton(outputPerformanceResult, str(round(performanceResult, 3)) + " %")
    
    fill(255)
    for row in range(0, n):
        for col in range(0, m):
            drawAt(row, col, ground.img)
    
    fill(255)
    for row in range(0, n):
        for col in range(0, m):
            drawAt(row, col, objectsArray[grid[row][col]].img)
            
    drawObject(vacuum);
    
def vacuumMoves():
    # La aspiradora se mueve hasta la izquierda, 
    # después recorre todas las posiciones hasta la derecha
    trashCount = 0
    for col in range(0, m):
        if grid[0][col] == trash.id:
            trashCount += 1    
    return m - 1 + vacuum.col + trashCount
    
def humanMoves():
    # Suponiendo que todo está en una fila
    left = vacuum.col
    right = vacuum.col
    trashCount = 0
    for col in range(0, m):
        if grid[0][col] == trash.id:
            trashCount += 1
            right = col
            if col < left:
                left = col
     
    # Moverse a la izquierda, regresar, moverse a la derecha
    op1 = abs(vacuum.col - left) + abs(right - left)
    # Moverse a la derecha, regresar, moverse a la izquierda
    op2 = abs(vacuum.col - right) + abs(right - left)
    return min(op1, op2) + trashCount

def mousePressed():
    global performanceResult, currentlyAdding
    
    if overButton(buttonCalculate):
        print("Calculate")
        performanceResult = 100 * float(vacuumMoves()) / humanMoves()
        
    elif overButton(buttonAddVacuum):
        print("Add vacuum")
        currentlyAdding = vacuum.id
    elif overButton(buttonAddTrash):
        print("Add trash")
        currentlyAdding = trash.id
    else:
        print("Mouse", mouseX, mouseY)
        
        col = mouseX / objectSize
        row = mouseY / objectSize
        
        # set the object in that position
        print("Set object", currentlyAdding)
        if insideRect(row, col, 0, 0, n, m):
            print("Is valid")
            if currentlyAdding == vacuum.id:
                vacuum.row = row
                vacuum.col = col
            elif grid[row][col] == currentlyAdding:
                grid[row][col] = ground.id
            else:
                grid[row][col] = currentlyAdding
                
