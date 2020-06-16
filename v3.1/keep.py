
import time, subprocess

# Logging function
def AddLog(status):
    # Log Restarts
    logFile = open('restartlog.txt', 'a')
    timeString = time.asctime(time.localtime(time.time()))
    logFile.write('%s %s\n' % (timeString, status))
    logFile.flush()
    logFile.close()

# Start the program
process = subprocess.Popen(['python', 'weatheros.py'])
AddLog('Started')

while True:
    # Check the state of the program
    status = process.poll()

    if status != None:
        # If the program crash, it will restart
        process = subprocess.Popen(['python', 'weatheros.py'])
        print 'Termination code %d, restarted' % (status)
        AddLog('Restarted')
    else:
        # Still running
        time.sleep(1)
