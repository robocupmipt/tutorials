from naoqi import ALProxy
import sys
import time


class SonarsHolder:
    def __init__(self, port, robot_ip):
        # Create proxy to ALMemory
        try:
            self.memoryProxy = ALProxy("ALMemory", robot_ip, port)
        except Exception, e:
            print "Could not create proxy to ALMemory"
            print "Error was: ", e

        # Create proxy to ALSonar
        try:
            self.sonarProxy = ALProxy("ALSonar", robot_ip, port)
        except Exception, e:
            print "Could not create proxy to ALSonar"
            print "Error was: ", e

        # Subscribe to sonars, this will launch sonars (at hardware level)
        # and start data acquisition.
        self.sonarProxy.subscribe("myApplication")

    def exit(self):
        self.sonarProxy.unsubscribe("myApplication")

    def GetData(self):
        left_sonar = self.memoryProxy.getData("Device/SubDeviceList/US/Left/Sensor/Value")
        right_sonar = self.memoryProxy.getData("Device/SubDeviceList/US/Right/Sensor/Value")
        return {"left": left_sonar, "right": right_sonar}

def main(port, robot_ip):
    sonars = SonarsHolder(port, robot_ip)
    while(True):
        print(round(sonars.GetData()['left'] * 100, 2), round(sonars.GetData()['right'] * 100, 2))
        time.sleep(2)

if __name__ == "__main__":
    port = 9559
    robot_ip = "192.168.1.4"
    main(port, robot_ip)
