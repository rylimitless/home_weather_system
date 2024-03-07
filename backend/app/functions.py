import database.mongo_client as database

db  = database.Database()

def insert(payload):
    result = db.insert(payload)
    return result
