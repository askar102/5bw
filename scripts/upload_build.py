import io
import requests
import os

from zipfile import ZipFile, ZIP_DEFLATED
from pathlib import Path

class Uploader():
    def __init__(self):
        self._build_path = Path("../build")

    def run(self):
        self.make_zip()
        self.upload()

    def make_zip(self):
        if not os.path.exists(self._build_path):
            print(f"Upload_build.py: error: path {self._build_path} doesn't exists")
            exit(1)

        with ZipFile("build.zip", "w", ZIP_DEFLATED, True) as zip:
            for root, dirs, files in os.walk(self._build_path):
                for file in files:
                    path = os.path.join(root, file)
                    zip.write(path)
                    # print(path)
            # print(zip.printdir())

    def upload(self):
        with open("build.zip", "rb") as zip:
            # files = {"archive": ("build.zip", zip, 'application/zip')}
            files = {'file': zip} 
            response = requests.post("http://127.0.0.1:8989/upload_test", files=files)

            if (response.ok):
                print(response.json())

if __name__ == "__main__":
    up = Uploader()
    up.run()


# files = {'archive': ('resources.zip', zip_buffer, 'application/zip')}
# response = requests.post("https://127.0.0.1:8989/upload_test")



