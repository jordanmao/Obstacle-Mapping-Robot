import random, pygame, sys, math
from pygame import gfxdraw

def ReadFiles():
    file1 = open('D:\RobotPath.txt','r')
    file2 = open('D:\Obstacles.txt','r')
    string1 = file1.read()
    string2 = file2.read()

    robotPath = string1.split(' ')[:-1] #last object in list is ''
    for x in range(len(robotPath)):
        coord = robotPath[x].split(',')
        robotPath[x] = (int(coord[0]),int(coord[1]))

    obstacles = string2.split(' ')[2:-1]
    for x in range(len(obstacles)):
        coord = obstacles[x].split(',')
        obstacles[x] = (int(coord[0]),int(coord[1]))
    return [robotPath,obstacles]

def FarthestCoord(list1,list2):
    farthestCoord = 1
    for coord in list1:
        x = abs(coord[0])
        y = abs(coord[1])
        if x > farthestCoord:
            farthestCoord = x
        elif y > farthestCoord:
            farthestCoord = y
    for coord in list2:
        x = abs(coord[0])
        y = abs(coord[1])
        if x > farthestCoord:
            farthestCoord = x
        elif y > farthestCoord:
            farthestCoord = y
    return farthestCoord


black = (0, 0, 0)
green = (50, 220, 80)
white = (255, 255, 255)
blue = (52, 146, 240)
red = (222, 36, 36)
pygame.init()
size = 900
screen = pygame.display.set_mode([size,size])
pygame.display.set_caption("Obstacle Mapping")
clock = pygame.time.Clock()

pair = ReadFiles()
robotPath = pair[0]
obstacles = pair[1]

farthestCoord = FarthestCoord(robotPath,obstacles)
scale = math.floor((size/2)/farthestCoord) #rounds down

done = False
for coord in obstacles:
    x = int(coord[0] * scale + size / 2)
    y = int(coord[1] * scale + size / 2)
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    screen.fill(white)
    for coord in robotPath:
        x = int(coord[0]*scale + size/2)
        y = int(-coord[1]*scale + size/2)
        pygame.draw.circle(screen,green,(x,y),5)
    for coord in obstacles:
        x = int(coord[0] * scale + size / 2)
        y = int(coord[1] * scale + size / 2)
        pygame.draw.circle(screen, black, (x, y), 5)
    pygame.display.flip()
    clock.tick(50)
