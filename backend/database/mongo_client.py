import logging
from pymongo import MongoClient
import os

# Get the current date and time


import dotenv

dotenv.load_dotenv()


class Database:
    MongoURI = os.environ['MONGO_URI']
    def __init__(self):
        self.client = MongoClient(self.MongoURI)
        self.db = self.client.dev
        self.collection = self.db.data

    def insert(self,payload):
        # self.db.connection
        try:
            result = self.collection.insert_one(payload)
            if result.acknowledged:
                return True
        except Exception as e:
            print(f"Mongo Insert Error {e}")
            return False
        return False
    