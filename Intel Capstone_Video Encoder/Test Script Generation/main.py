#!/usr/bin/python
# -*- coding: UTF-8 -*-

import xml.dom.minidom
from xml.dom.minidom import parse
from xml.dom.minidom import Document
import ConfigParser   
import re
import lxml.etree as ET  
from xml.etree.ElementTree import ElementTree,Element

def ValidCheckXML(XMLName, XSDName):
	xmlschema_doc=ET.parse(XSDName)  
	xmlschema=ET.XMLSchema(xmlschema_doc)  
	xml=ET.parse(XMLName)   
	if not xmlschema.validate(xml):  
		print xmlschema.error_log 
		return False
	else:
		return True


def XMLGenerate(XSDName, ININame):
	# Initialization 
	cf = ConfigParser.ConfigParser()   
	rooT = ET.parse(XSDName)
	cf.read(ININame)  
	UIopt = cf.options("option")

	# XSD: Find all complexType elements and options
	typeSet = []
	optionSet = [] 
	for element in rooT.iter():
		if isinstance(element.tag, basestring):
			if ET.QName(ET.Element(element.tag)).localname == 'complexType':
				if ET.QName(ET.Element(element[0].tag)).localname == 'simpleContent':
					typeSet.append(element)
			elif ET.QName(ET.Element(element.tag)).localname == 'element':
				if not len(element):
					if 'name' in element.keys():
						optionSet.append(element)

	# Write XML 
	doc = Document()  
	rooT = doc.createElement('rooT') 
	rooT.setAttribute('xmlns:xsi',"http://www.w3.org/2001/XMLSchema-instance")
	rooT.setAttribute('xsi:noNamespaceSchemaLocation', XSDName) 
	doc.appendChild(rooT)

	# General Structure
	encName = doc.createElement(cf.get("main","encoder"))
	cmdName = doc.createElement(cf.get("main","command"))

	# Add options
	for opt in UIopt:
		tmp = doc.createElement(opt)
		for option in optionSet:
			if opt == option.get('name'):
				for typeopt in typeSet:
					if option.get('type') == typeopt.get('name'):
						atb = typeopt[0][0][0]
						tmp.setAttribute('tag',atb.get('fixed'))
		opt_value = doc.createTextNode(cf.get("option", opt))
		tmp.appendChild(opt_value)
		cmdName.appendChild(tmp)
	
	encName.appendChild(cmdName)
	rooT.appendChild(encName)

	# Write the DOM object to the file
	f = open('database.xml','w')
	f.write(doc.toprettyxml(indent = '\t'))
	f.close()

	# Valid Checking
	ValidCheckXML(XMLName, XSDName)

def XMLreader(ININame, XMLName):
	# Read from INIfile
	cf = ConfigParser.ConfigParser()   
	cf.read(ININame)  
	encName = cf.get("main","encoder")
	cmdName = cf.get("main","command")

	# Generate Command from XML file
	DOMTree = xml.dom.minidom.parse(XMLName)
	XMLroot = DOMTree.documentElement
	enc = XMLroot.getElementsByTagName(encName)[0]
	cmd = enc.getElementsByTagName(cmdName)[0]
	cmdarr = [cmd.tagName]
	for subCmd in cmd.getElementsByTagName("*"):
		cmdarr.append(subCmd.getAttribute("tag"))
		cmdarr.append(subCmd.childNodes[0].data)
	fcmd = ' '.join(cmdarr)	
	print fcmd

def loopgen(ININame, XSDName, XMLName, LP, cf):
	key,value = LP.pop()
	# Generate an array from 'value'
	result_arr = []
	if value.find('&') > 0:
		str_arr = value.split('&',2)
		init = int(str_arr[0])
		incre = int(str_arr[1])
		final = int(str_arr[2])
		while init <= final:
			result_arr.append(init)
			init += incre
	elif value.find('|') > 0:
		str_arr = value.split(' | ')
		result_arr = []
		for i in str_arr:
			result_arr.append(i)
	else:
		result_arr.append(value)

	if not len(LP):
		for i in result_arr:
			cf.set('option', key, i) 
			cf.write(open(ININame, 'r+'))	
			XMLGenerate(XSDName, ININame)
			XMLreader(ININame, XMLName)
		LP.append((key,value))
	else:	
		for i in result_arr:
			cf.set('option', key, i) 
			cf.write(open(ININame, 'r+'))	
			loopgen(ININame, XSDName, XMLName, LP, cf)
		LP.append((key,value))
		

def cmdGenerate(XSDName, ININame, XMLName):
	# Read from INIfile
	cf = ConfigParser.ConfigParser()   
	cf.read(ININame)
	encName = cf.get("main","encoder")
	cmdName = cf.get("main","command")
	DOMTree = xml.dom.minidom.parse(XMLName)
	XMLroot = DOMTree.documentElement
	enc = XMLroot.getElementsByTagName(encName)[0]
	cmd = enc.getElementsByTagName(cmdName)[0]
  
	LP = cf.items("loop")

	# Start loop detection
	if not len(LP):
		CmdGenerate(ININame, XMLName)
	else:
		loopgen(ININame, XSDName, XMLName, LP, cf)
			
	

# Main
if __name__ == "__main__":
	ININame = 'UI.ini' 
	XSDName = 'rooT.xsd'
	XMLName = 'database.xml'

	XMLGenerate(XSDName, ININame)
	cmdGenerate(XSDName, ININame, XMLName)
	

