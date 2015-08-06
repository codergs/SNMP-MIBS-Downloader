# SNMP_MIBS_Downloader
##Instrcutions for Installing snmp-mibs-downloader on Ubuntu using snmp-mibs-downloader_1.1.tar.gz

Recently, I tried installing snmp on my Ubuntu machine, and had world of problems downloading the MIBs as the snmp-mibs-dowloader
package was not availabe under the apt suite. Though I found the information about the package residing under the multiverse, I couldn't figure how to add that to the apt lookup path. Hence, I decided to download the package and install manually, which resulted into more hours of debugging as the package was poorly documented (Just my view point). 

Here's the link--> http://packages.ubuntu.com/precise/net/snmp-mibs-downloader

* This repo has tweaked make file and steps that will help you install snmp-mibs-downloader on Ubuntu 

1.  Download the tar.gz version from the above mentioned link
2.  Drop to root user on Ubuntu (If one has sudo privileges, then that will work as well)
3.  Change directory to the one where the file snmp-mibs-downloader_1.1.tar.gz resides. (For eg., lets say the file was 
    downloaded under /home/your_username/Downlowad folder, one can type the below commands:
      <p>**cd ~/Download** 
      <p>**sudo tar xvzf snmp-mibs-downloader_1.1.tar.gz**
4.  The above will utar and unzip the snmp-mibs-downloader_1.1.tar.gz to create snmp-mibs-downloader_1.1 folder under Downloads
5.  Use the make file under this repo as the one that comes with the package gave me build errors as the necessary folder paths      weren't created prior running the script
6.  Under my make file, there is an added clean tag that wil come handy if somethinng needs to be re-built 
7.  Change the directory to snmp-mibs-downloader_1.1 by typing cd ssnmp-mibs-downloader_1.1
     <p>**make install (for root users) and sudo make install (for sudo users)**
     <p>**sudo donwload-mibs**
8.  Running this command I got an error: **/usr/bin/smistrip not a file or directory**, which was be corrected installing the        smistrip package from the apt suite using: 
    <p>**apt-get install smistrip (for root users) and sudo apt-get install smistrip (for sudo users)**
9.  For me this did install the MIBS under /usr/share/snmp/mibs and /var/lib/snmp/mibs. Since var/lib/snmp/mibs was not in the       MIB search path, I decided to move all the MIBS from /var/lib/snmp/mibs into the /usr/share/snmp/mibs

  **Note**:* For many users the installed MIBs were under /usr/local/share/snmp/mibs
           * I changed all the mibs under /usr/share/snmp/mibs to .txt extension (May not be needeed, but Ben Rockwood's                   *"The  Net-SNMP Programming Guide"* mentions to do the above. 
    
  **Note**: * <p>Questions can be asked that why I didn't add the /var/lib/snmp/mibs to the MIB search path. 
            * <p>For a matter of fact, I did try a lot, but couldn't find the MIB search path environment variable. I came across                 post on stack overflow, which suggested adding command mibdirs +/var/lib/snmp/mibs that didn't work for me. You                  can cross check this by a simple trick whether thiscommand works or not /var/lib/snmp/mibs. 
    
    Here's how you should check:
    
    * Under /etc/snmp/snmp/snmp.conf file, uncomment the line that says, #mibs :
    * On uncommenting the above, we are telling snmpd to not use any mibs from the search path 
    * Now move all the mibs that start by SNMPv2 to /var/lib/snmp/mibs folder 
    * Again under /etc/snmp/snmp/snmp.conf file, after the line that says mibs :
      type mibdirs +/var/lib/snmp/mibs and  save it
    * Restart the snmp daemon by issuing:
      service snmpd restart (for root users) and sudo service snmpd restart (for sudo users)
    * Now, issue 
      <p>**Command** ==> **snmpwalk -v1 -c public localhost .1.3.6.1.2.1.1.2** 
      <p>**Output**  ==> **SNMPv2-MIB::sysObjectID.0 = OID: NET-SNMP-MIB::netSnmpAgentOIDs.10** 
      
      If you see the above output then the path was /var/lib/snmp/mibs looked up
      
      <p>**Command** ==>  **snmpwalk -v1 -c public localhost .1.3.6.1.2.1.1.2**
      <p>**Output**  ==>  **iso.3.6.1.2.1.1.2.0 = OID: iso.3.6.1.4.1.8072.3.2.10**
      
      If you see the above output then the path was /var/lib/snmp/mibs was not looked up 
