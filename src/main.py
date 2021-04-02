import cv2

img = cv2.imread('out.ppm')
cv2.imwrite('out.bmp', img)
