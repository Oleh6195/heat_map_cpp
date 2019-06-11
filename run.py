import cv2
import os
import subprocess
from sys import argv

image_folder = 'img'
video_name = 'video.avi'


parallel = subprocess.Popen(["./parallel"], stdout=subprocess.PIPE)
parallel.wait()
res = str(parallel.communicate()[0], 'utf-8').split('\n')
for i in res:
    print(i)

images = [img for img in os.listdir(image_folder) if img.endswith(".png")]
images.reverse()
frame = cv2.imread(os.path.join(image_folder, images[0]))
height, width, layers = frame.shape

video = cv2.VideoWriter(video_name, cv2.VideoWriter_fourcc('M','J','P','G'), 60, (width,height))

for image in images:
    video.write(cv2.imread(os.path.join(image_folder, image)))

cv2.destroyAllWindows()
video.release()