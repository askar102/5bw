import io
import requests
import os
import argparse

from zipfile import ZipFile, ZIP_DEFLATED
from pathlib import Path

class Uploader():
    def __init__(self, docker: bool = False):
        self._build_path = Path("../build")
        self._docker = docker

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

            if self._docker:
                response = requests.post("http://host.docker.internal:8989/upload_test", files=files, data={"extra_data": "docker"})
            else:
                response = requests.post("http://127.0.0.1:8989/upload_test", files=files)

            if response.ok:
                print(response.json())
            else:
                print(f"Upload failed: {response.status_code} {response.text}")

if __name__ == "__main__":
    par = argparse.ArgumentParser()
    par.add_argument("--docker", action="store_true")

    args = par.parse_args()


    up = Uploader(docker=args.docker)
    up.run()


# files = {'archive': ('resources.zip', zip_buffer, 'application/zip')}
# response = requests.post("https://127.0.0.1:8989/upload_test")



