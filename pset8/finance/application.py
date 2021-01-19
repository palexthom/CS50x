import os, time, datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, isint

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Create a list of items to print and pass them as an argument to the template
    rows = db.execute("SELECT symbol, SUM(shares) FROM 'transactions' WHERE username = :username GROUP BY symbol", username = session['user_id'])
    total = 0
    for row in rows:
        dict = lookup(row['symbol'])
        if dict != None :
            price = round(dict['price'],2)
            row['price'] = price
            row['name'] = dict['name']
            row['total'] = row['SUM(shares)'] * price
            total += row['SUM(shares)'] * price
    # Check how much money you habe
    cash = round(db.execute("SELECT cash FROM 'users' WHERE username= :username", username = session['user_id'])[0]['cash'],2)

    # Calculate total
    total = total + cash
    return render_template("home.html", items = rows, total = total, cash = cash)


    #symbol name shares price total

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        #apology if input blank
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 403)

        #apology if number of shares isn't a positive integer
        if not isint(request.form.get("shares")):
            return apology("number of shares must be an integer", 403)
        elif int(request.form.get("shares")) <= 0 :
            return apology("number of shares must be positive", 403)
        else:
            shares = int(request.form.get("shares"))

        # lookup for the share
        dict = lookup(request.form.get("symbol"))
        if dict != None :
            price = round(dict['price'],2)

            #look in database (SELECT) in database to see how much cash has the user
            cash = db.execute("SELECT cash FROM 'users' WHERE username= :username", username = session['user_id'])[0]['cash']

            #apology if user cannot afford the shares
            if (cash - (shares * price)) < 0:
                return apology("can't afford the shares", 403)

            else:
                #add transaction to database
                db.execute("INSERT INTO transactions (date, username, symbol, shares, price) VALUES (?, ?, ?, ?, ?)",
                            round(time.time()), session['user_id'], request.form.get("symbol"), shares, price)
                #update user cash value
                db.execute("UPDATE users SET cash = (?) WHERE username = (?)", cash - (price * shares), session['user_id'])

                return render_template("bought.html", dict=dict, shares=shares)

        else:
            # apology if symbol does not exist (lookup returns NONE)
            return apology("must provide a valid symbol", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Create a list of items to print and pass them as an argument to the template
    rows = db.execute("SELECT * FROM 'transactions' WHERE username = :username ORDER BY date ASC", username = session['user_id'])
    for row in rows:
        row['date'] = datetime.datetime.fromtimestamp(row['date'])

    return render_template("history.html", items = rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    # session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                         username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")) :
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Ensure value is submitted
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 403)

        dict = lookup(request.form.get("symbol"))
        if dict != None :
            return render_template("quoted.html", dict=dict)
        else:
            return apology("must provide a valid symbol", 403)
    else:
        # User reached route via GET, display page
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username doesn't exists and password is correct
        if len(rows) != 0:
            return apology("username already exists", 403)
        elif request.form.get("password") != request.form.get("confirmation"):
            #TODO : compare strings or hash and compare hashs ?
            return apology("passwords don't match")
        else:
            # Insert new user in users table (hash user's password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                    request.form.get("username"), generate_password_hash(request.form.get("confirmation")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        #apology if input blank
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 403)

        #apology if number of shares isn't a positive integer
        if not isint(request.form.get("shares")):
            return apology("number of shares must be an integer", 403)
        elif int(request.form.get("shares")) <= 0 :
            return apology("number of shares must be positive", 403)
        else:
            shares = int(request.form.get("shares"))

        # lookup current price of shares
        dict = lookup(request.form.get("symbol"))
        if dict != None :
            price = round(dict['price'],2)

            #look in database if user owns enough of these shares
            qty = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE username = :username AND symbol = :symbol GROUP BY :symbol",
                        username = session['user_id'], symbol = request.form.get("symbol"))[0]['SUM(shares)']
            cash = db.execute("SELECT cash FROM 'users' WHERE username= :username", username = session['user_id'])[0]['cash']

            #apology if user doesn't have enough shares
            if (shares > qty):
                return apology("not enough shares to sell", 403)

            else:
                #add transaction to database
                db.execute("INSERT INTO transactions (date, username, symbol, shares, price) VALUES (?, ?, ?, ?, ?)",
                            round(time.time()), session['user_id'], request.form.get("symbol"), -shares, price)
                #update user cash value
                db.execute("UPDATE users SET cash = (?) WHERE username = (?)", cash + (price * shares), session['user_id'])

                return render_template("sold.html", dict=dict, shares=shares)

        else:
            # apology if symbol does not exist (lookup returns NONE)
            return apology("must provide a valid symbol", 403)


    else:
        return render_template("sell.html")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
