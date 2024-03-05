from pymongo import MongoClient

class Database:

    def __init__(self):
        self.client = MongoClient('mongodb://localhost:27017')
        self.db = self.client.dev
        self.collection = self.db.data

    def insert(self,payload):
        # self.db.connection
        result = self.collection.insert_one(payload)
        if result.acknowledged:
            return True
        return False