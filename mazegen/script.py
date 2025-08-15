import cv2

fname = 'mazegen'
im = cv2.imread(fname+'.ppm')
cv2.imwrite(fname+'.png', im)
