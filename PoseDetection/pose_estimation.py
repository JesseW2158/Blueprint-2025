import cv2
import math
import cvzone
from cvzone.SerialModule import SerialObject
from ultralytics import YOLO
import numpy as np

capture = cv2.VideoCapture(0)
model = YOLO('yolo11n-pose.pt')
arduino = SerialObject()

optimal_posture = np.array(
[[     309.87,      227.27,     0.99623],
 [      351.3,      185.46,     0.99773],
 [     276.82,      184.85,      0.9959],
 [     411.96,       215.9,     0.97995],
 [     230.26,      211.94,     0.87248],
 [     520.76,      451.26,     0.87289],
 [     114.88,      438.87,     0.95974],
 [          0,           0,   0.0033513],
 [          0,           0,    0.010388],
 [          0,           0,   0.0078412],
 [          0,           0,    0.013907],
 [          0,           0,  0.00098551],
 [          0,           0,   0.0017347],
 [          0,           0,  0.00044921],
 [          0,           0,  0.00085875],
 [          0,           0,   0.0005258],
 [          0,           0,  0.00087443]])

while True:
    actual_posture = None
    posture_score = 0
    ret, frame = capture.read()
    
    results = model(frame)
    frame = results[0].plot()
    
    for keypoints in results[0].keypoints.data:
        keypoints = keypoints.cpu().numpy()
        
        actual_posture = keypoints
        for i, keypoint in enumerate(keypoints):
            x, y, confidence = keypoint
            
            if confidence > 0.8:
                posture_score += math.dist((x, y), (optimal_posture[i][0], optimal_posture[i][1])) / 10 ** 2
    
    print(posture_score)
    
    # print(posture_score)
    
    # if(posture_score < 2.5):
    if(posture_score < 6):
        arduino.sendData([0])
    else:
        arduino.sendData([1])
    
    cv2.imshow('Press space to end', frame)
    if cv2.waitKey(1) & 0xFF == ord(' '):
        break
    
capture.release()
cv2.destroyAllWindows()