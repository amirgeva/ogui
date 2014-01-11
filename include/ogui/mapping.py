#Copyright (c) 2013-2014, Amir Geva
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#
#* Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#
#* Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
#  and/or other materials provided with the distribution.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import os
import re

out=open('mapping.inl','w')
types={'float','Point','bool','int','xstring','Rect','unsigned','Alignment','Orientation'}
declared_names={}

def fill_attrs(all,parents,name):
	attrs=[]
	if all.has_key(name):
		attrs=list(all.get(name))
	if parents.has_key(name):
		parent=parents.get(name)
		attrs=attrs+fill_attrs(all,parents,parent)
	return attrs


widget_class=(""
"class {CLASS}Generator : public TWidgetGenerator<{CLASS}>\n"
"{\n"
"public:\n"
"  static pointer parse(xml_element_ptr el)\n"
"  {\n"
"    pointer widget=create();\n"
"    for(auto it=el->attr_begin();it!=el->attr_end();++it)\n"
"    {\n"
"      xstring name=it->first;\n"
"      xstring value=it->second;\n"
"      {CONDS}\n"
"    }\n"
"    return widget;\n"
"  }\n"
"};\n")

cond='      if (name=="{ATTR}") set_value(widget,&{CLASS}::set_{ATTR},value);\n'


creator_func=(''
'inline widget_ptr widget_parse(xml_element_ptr el)\n'
'{\n'
'  if (el->get_type() == "{CLASS}") return {CLASS}Generator::parse(el);\n'
'  return widget_ptr();\n'
'}\n'
'\n')


def process(all,parents):
	for name in declared_names:
		attrs=fill_attrs(all,parents,name)
		for line in widget_class.split('\n'):
			if line.strip()=='{CONDS}':
				for a in attrs:
					attr_name=a[0]
					attr_name=attr_name[4:]
					cond_line=cond.replace('{ATTR}',attr_name)
					cond_line=cond_line.replace('{CLASS}',name)
					out.write(cond_line)
			else:
				pline=line.replace('{CLASS}',name)
				out.write('{}\n'.format(pline))
	for line in creator_func.split('\n'):
		if line.strip().startswith('if'):
			for name in declared_names:
				cond_line=line.replace('{CLASS}',name)
				out.write('{}\n'.format(cond_line))
		else:
			out.write('{}\n'.format(line))
				

def processWidgets():
	cls=re.compile('class (\w+) : public ((?:\w*)Widget)')
	decl_pattern=re.compile('OGUI_DECLARE_WIDGET\((\w+)\);')
	attr=re.compile('virtual(?:\s+)void(?:\s+)(set_(?:\w+))\(const (\w+)')
	wattr=re.compile('virtual(?:\s+)void(?:\s+)(set_(?:\w+))\(widget_ptr (\w+)')
	files=os.listdir('.')
	all={}
	parents={}
	for filename in files:
		f=open(filename,"r")
		class_name=''
		attrs=[]
		for line in f.readlines():
			m=re.search(decl_pattern,line)
			if not m is None:
				g=m.groups()
				name=g[0]
				declared_names[name]=True
			m=re.search(cls,line)
			if not m is None:
				g=m.groups()
				if len(class_name)>0:
					all[class_name]=attrs
					attrs=[]
				class_name=g[0]
				parents[class_name]=g[1]
			elif line.strip()=='class Widget':
				if len(class_name)>0:
					all[class_name]=attrs
					attrs=[]
				class_name='Widget'
			m=re.search(attr,line)
			if m is None:
				m=re.search(wattr,line)
				if not m is None:
					g=m.groups()
					attrs.append((g[0], 'widget_ptr'))
			if not m is None:
				g=m.groups()
				if g[1] in types:
					attrs.append(g)
		if len(class_name)>0:
			all[class_name]=attrs
	process(all,parents)
			
def processSkinColors():
    out=open('skin_colors.inl','w')
    for line in open('constants.h','r').readlines():
        line=line.strip()
        if line.startswith("SKIN_COLOR_") and line.endswith(','):
            name=line.replace(',',' ').strip()
            out.write('{{ "{}" , {} }},\n'.format(name,name))
		
  
def main():
    processWidgets()
    processSkinColors()


if __name__=='__main__':
	main()
