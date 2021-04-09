import cv2

if __name__ == '__main__':
    img = cv2.imread('out.ppm')
    cv2.imwrite('out.jpg', img)
