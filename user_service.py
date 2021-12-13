import json
import time
import tornado.web
import tornado.ioloop
import tornado.options
import sqlite3
import logging

class App(tornado.web.Application):

    def __init__(self, handlers, **kwargs):
        super().__init__(handlers, **kwargs)

        self.db = sqlite3.connect('users.db')
        self.db.row_factory = sqlite3.Row
        self.init_db()

    def init_db(self):
        c = self.db.cursor()

        c.execute("""
            CREATE TABLE IF NOT EXISTS users (
            user_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            created_at INTEGER NOT NULL,
            updated_at INTEGER NOT NULL
            )
        """)
        self.db.commit()

class welcomeHandler(tornado.web.RequestHandler):
    def get(self):
        self.add_header("Content-Type", "application/json")
        self.write("Hello! Please visit /users to see users")

class helpHandler(tornado.web.RequestHandler):
    def write_json(self, obj, status_code=200):
        self.set_header("Content-Type", "application/json")
        self.set_status(status_code)
        self.write(json.dumps(obj))

class userHandler(helpHandler):
    @tornado.gen.coroutine
    def get(self, user_id):
        page_no = self.get_argument("page_no", 1)
        page_size = self.get_argument("page_size", 10)

        try:
            page_no = int(page_no)
        except:
            logging.exception("Error while parsing page no: {}".format(page_no))
            self.write_json({"result": False, "errors": "invalid page_no"}, status_code=400)
            return

        try:
            page_size = int(page_size)
        except:
            logging.exception("Error while parsing page_size: {}".format(page_size))
            self.write_json({"result": False, "errors": "invalid page_size"}, status_code=400)
            return


        if user_id is not None:
            try:
                user_id = int(user_id)
            except:
                self.write_json({"result": False, "erorrs": "invalid user_id"}, status_code=400)
                return

        selector = "SELECT * FROM users"
        if user_id is not None:
            selector += " WHERE user_id=?"

        limit = page_size

        offset = (int(page_no) - 1) * int(page_size)

        selector += " ORDER BY created_at DESC LIMIT ? OFFSET ?"

        if user_id is not None:
            args = (user_id, limit, offset)
        else:
            args = (limit, offset)

        c = self.application.db.cursor()

        results = c.execute(selector, args)
        users = []
        for row in results:
            fields = ["user_id", "name", "created_at", "updated_at"]
            user = {
                field:row[field] for field in fields
            }
            users.append(user)

        self.write_json({"result": True, "users": users})

class userlistHandler(helpHandler):
    def get(self):
        page_no = self.get_argument("page_no", 1)
        page_size = self.get_argument("page_size", 10)

        try:
            page_no = int(page_no)
        except:
            logging.exception("Error while parsing page no: {}".format(page_no))
            self.write_json({"result": False, "errors": "invalid page_no"}, status_code=400)
            return

        try:
            page_size = int(page_size)
        except:
            logging.exception("Error while parsing page_size: {}".format(page_size))
            self.write_json({"result": False, "errors": "invalid page_size"}, status_code=400)
            return

        selector = "SELECT * FROM users"

        limit = page_size

        offset = (int(page_no) - 1) * int(page_size)

        selector += " ORDER BY created_at DESC LIMIT ? OFFSET ?"

        args = (limit, offset)

        c = self.application.db.cursor()

        results = c.execute(selector, args)
        users = []
        for row in results:
            fields = ["user_id", "name", "created_at", "updated_at"]
            user = {
                field:row[field] for field in fields
            }
            users.append(user)

        self.write_json({"result": True, "users": users})

    @tornado.gen.coroutine
    def post(self):

        c = self.application.db.cursor()
        username = self.get_argument("name")
        time_now = int(time.time() * 1e6)
        user_id = c.lastrowid

        if isinstance(username, str) == False:
            self.write_json({"result": False, "invalid name": username}, status_code=400)
            return

        c.execute("""INSERT INTO users VALUES (?, ?, ?, ?)""", (user_id, username, time_now, time_now))

        self.application.db.commit()

        user = dict(
        user_id = c.lastrowid,
        name = username,
        created_at = time_now,
        updated_at = time_now
        )

        self.write_json({"result":True, "user":user})

def make_app(options):
    return App([
    (r"/", welcomeHandler),
    (r"/users/(.*)", userHandler),
    (r"/users", userlistHandler),
    ], debug = options.debug)

if __name__ == "__main__":

    tornado.options.define("port", default = 8881)
    tornado.options.define("debug", default = True)
    tornado.options.define("autoreload", default = True)

    tornado.options.parse_command_line()

    options = tornado.options.options
    app = make_app(options)
    app.listen(options.port)
    logging.info("Starting users service. Port: {}".format(options.port))
    tornado.ioloop.IOLoop.instance().start()
