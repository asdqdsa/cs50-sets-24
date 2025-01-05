import os

from cs50 import SQL
from flask import (
    Flask,
    flash,
    jsonify,
    redirect,
    render_template,
    request,
    session,
)

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
app.config["DEBUG"] = True
app.config["ENV"] = "development"
app.jinja_env.globals.update(zip=zip)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # User's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not day or not month or not name:
            return redirect("/")

        try:
            day = int(day)
            month = int(month)
        except ValueError:
            return redirect("/")

        if not 1 <= month <= 12 and not 1 <= day <= 31:
            return redirect("/")

        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)",
            name,
            month,
            day,
        )
        return redirect("/")

    else:
        # Display entries in the database on index.html
        cakedays = db.execute("select * from birthdays")
        return render_template("index.html", cakedays=cakedays)


@app.route("/delete/<int:id>", methods=["POST"])
def delete(id):
    db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")
