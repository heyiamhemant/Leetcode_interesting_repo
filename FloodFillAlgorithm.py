def recursiveColor(x,y,image,color,newColor):
    m = len(image)
    n = len(image[0])  
    image[x][y] = newColor
    if (x>0 and image[x-1][y]==color):
        recursiveColor(x-1,y,image,color,newColor)
    if (y>0 and image[x][y-1]==color):
        recursiveColor(x,y-1,image,color,newColor)
    if(x<m-1 and image[x+1][y]==color):
        recursiveColor(x+1,y,image,color,newColor)
    if (y<n-1 and image[x][y+1]==color):
        recursiveColor(x,y+1,image,color,newColor)
    return
def floodFill(image, x, y, newColor):
    # Write your Code here.
    #brute force
    color = image[x][y]
    if(color == newColor):
        return image
    recursiveColor(x,y,image,color,newColor)
    return image     