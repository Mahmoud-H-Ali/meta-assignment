# meta-assignment
OSES ASSIGNMENT ON EMBEDDED LINUX Heart Rate Monitor 


This README file contains information on the contents of the meta-assignment layer.

Name : Mahmoud
Last name : Hassan Ali 

matricola : s281632




I. Adding the meta-assignment layer to your build
=================================================
in the poky directory 

clone the layer into poky directory 

	git clone https://github.com/MahmoudElhadedy/meta-assignment

add these lines in the local.conf file to the recipes to the image to be deployed 

	IMAGE_INSTALL_append = " hrtmod"
	KERNEL_MODULE_AUTOLOAD += "hrtmod"

	IMAGE_INSTALL_append = " hrtapp"


then run 
    bitbake-layers add-layer meta-assignment

