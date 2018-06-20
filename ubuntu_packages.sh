#!/bin/sh
#
# Install the neccessary packages for an Ubuntu host
#

build_glfw3 ()
{
  # GLFW 3.1.1
  if [ ! -f /usr/local/include/GLFW/glfw3.h ]; then
  	URL="http://downloads.sourceforge.net/project/glfw/glfw/3.1.1/glfw-3.1.1.zip?r=http%3A%2F%2Fwww.glfw.org%2F&ts=1428099282&use_mirror=superb-dca2"
  	DISTFILE="glfw.zip"
  	SRCDIR="glfw-3.1.1"
  	cd /tmp
  	wget "${URL}" -O ${DISTFILE}
  	if [ $? -eq 0 ]; then
  		unzip ${DISTFILE}
  		cd ${SRCDIR}
  		cmake -G "Unix Makefiles"
  		make all install clean
  	fi
  else
	echo "/usr/local/include/GLFW/glfw3.h already exists."
  fi
}

pkg_graphicsdev ()
{
  apt-get --yes install libglew-dbg libglew-dev libglew1.10 \
  libfreeimage3 libfreeimage3-dbg libfreeimage-dev libfreeimageplus-dev \
  freeglut3 freeglut3-dbg freeglut3-dev \
  libxrandr-dev libxi-dev libx11-dev \
  mesa-utils mesa-utils-extra \
  libopenctm-dev libopenctm1 openctm-tools openctm-doc python-openctm
  
}

ID=`id -u`
if [ ${ID} -ne 0 ]; then
	echo "You need to be root to run this script."
	exit 1
fi

pkg_graphicsdev

build_glfw3
