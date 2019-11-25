
import gevent.monkey
gevent.monkey.patch_all()
from flask import Flask, render_template, url_for, request, redirect, jsonify, session
#from flask.ext.session import Session
from flask_socketio import SocketIO
#import answer
#import flask_session
import sys
#from response_cleverness import drone
#from response_cleverness import argc_argv
from flask_wtf import Form
from wtforms import TextField, SubmitField, SelectField, validators, TextAreaField
import json
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = ' AOSDHGOASHDG'
basedir = os.path.abspath(os.path.dirname(__file__))
current_user = ''

class Config(object):
	SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'app.db')
	SQLALCHEMY_TRACK_MODIFICATION = False 

app.config.from_object(Config)
socketio = SocketIO(app)
db = SQLAlchemy(app)
migrate = Migrate(app, db)

class Question(Form):
	value = TextField()
	name = TextField()
	Submit = SubmitField('Submit')

class AboutMe(db.Model):
	id = db.Column(db.Integer, primary_key=True)
	name = db.Column(db.String(200))
	about_myself = db.Column(db.String(16000000))
	what_i_do = db.Column(db.String(16000000))

class Sender(Form):
	sender = SubmitField('HOME')

class SubmitButton(Form):
	code 		= TextAreaField()
	SubmitButton = SubmitField('SEND')


username = 'response_cleverness'
"""
@app.route('/susanoo', methods=['GET', 'POST'])
def susanoo():
	global username
	global check
	response = 'hello'

	if request.method == 'POST' and submit.validate():
		if 'plc' in request.form:
			text = request.form['plc']
		response = drone.drone(text, AboutMe)
	return render_template('susanoo.html',
				response=response,
				submit=submit
"""			

@app.route('/about_project', methods=['GET', 'POST'])
def about_project():
	send = Sender()
	return render_template('about.html', send=send)

@app.route('/loading')
def loading():
	length = len(current_user)
	return render_template('load_transition.html',
		current_user=current_user,
		length=length
		)

@app.route('/')
def session():	
	return render_template('flashy.html')

"""
@app.route('/submit', methods=['GET', 'POST'])
def submit():
	question = request.form['value']
	print('username is ', username)
	responses = drone.drone(question, AboutMe, current_user)
	print(question)
	print('here I am', responses)
	return jsonify(response=responses)
"""

def clean_database():
	database = AboutMe.query.all()

#	if database == None:
#		return
	for item in database:
#		if item is None:
#			continue
#		if item.name == current_user:
		db.session.delete(item)
		db.session.commit()
	print('database clean')
"""
@app.route('/builder', methods=['GET', 'POST'])
def builder():
	form = Question()
	global current_user

	if form.validate_on_submit():
		print('Posted: value is ')
		print(request.form['about-yourself'])
		clean_database()
		current_user = form.name.data
		print(current_user)
		about_bot = AboutMe(
				name=current_user,
				about_myself=request.form['about-yourself'],
				what_i_do=request.form['your-proposal']
			)
		db.session.add(about_bot)
		db.session.commit()
	return render_template('builder.html', submit=form)
"""

if __name__ == '__main__':

	socketio.run(app, host='0.0.0.0', port=8000, debug=True)


