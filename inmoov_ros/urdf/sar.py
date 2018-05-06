import re
text = "";
with open("/home/georgehartt/inmoov_ws/src/inmoov_urdf/urdf/inmoov_.urdf") as f:
    for line in f:
		#if(line.startswith("      effort=")):
		#	text += "      effort=\"0.1\"\n";
		#else:
		text += line;

f=open("/home/georgehartt/inmoov_ws/src/inmoov_urdf/urdf/inmoov.urdf","w")
text = re.sub(r'\bin-moov-ros\b', 'inmoov_urdf', text);
f.writelines(text);
f.close();
