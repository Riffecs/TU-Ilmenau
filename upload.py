from ftplib import FTP
import sys
import os

# Load Data
USER = os.getenv('user')
PASSWORD = os.getenv('key')
SERVER = os.getenv('server')

# Upload Settings
ftp = FTP(SERVER, USER, PASSWORD)
ftp.cwd('file')
try:
    ftp.mkd('TU-Ilmenau')
except:
    ftp.mkd('TU-Ilmenau')
    ftp.cwd('TU-Ilmenau')

try:
    ftp.mkd(sys.argv[2])
except:
    ftp.mkd(sys.argv[2])
    ftp.cwd(sys.argv[2])
file = open(sys.argv[1], 'rb')
ftp.storbinary('STOR ' + sys.argv[1], file)
file.close()
ftp.quit()
