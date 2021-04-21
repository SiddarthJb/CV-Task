import cv2
import numpy as np

class Detect():
    def __init__(self):
        self.cap = cv2.VideoCapture(0)
        self.Cascade = None

    def getFrame(self):
        s, img = self.cap.read()
        return img


    def setCascade(self,CascadePath):
      self.Cascade = cv2.CascadeClassifier(CascadePath)

    def detect(self):
        image = self.getFrame()
        if image is not None:
          gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
          faces = self.Cascade.detectMultiScale(gray,scaleFactor=1.2,
                                              minNeighbors=5,
                                              minSize=(20, 20))
          return faces
        

    def releaseCamera(self):
        self.cap.release()


def main():
    faceDetection = Detect()
    faceDetection.setCascade("./haarcascade_frontalface_alt.xml")
    overlay = cv2.imread("./image.jpeg")
    while True:
        faces = faceDetection.detect()
        img = faceDetection.getFrame()

        # Overlay mask only when face is detected
        if faces is not None:
           for (x,y,w,h) in faces:
               cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
               overlay = cv2.resize(overlay,(w,h))
               roi = img[y:y+h, x:x+w] 
               img[y:y+h, x:x+w] = overlay

        cv2.imshow('video',img)
        k = cv2.waitKey(30) & 0xff
        if k == 27:
            faceDetection.releaseCamera()
            cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
   