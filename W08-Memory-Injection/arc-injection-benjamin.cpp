// Benjamin's Arc Injection Idea

/***********************************************************
 * ARC INJECTION VULNERABILITY
 * From (Helfrich, "Security for Software Engineers", 2019)
 * 1.  "There must be a function pointer used in the code."
 * 2.  "Through some vulnerability, there must be a way for
 *      user input to overwrite the function pointer. This 
 *      typically happens through a stack buffer 
 *      vulnerability."
 * 3.  "After the memory is overwritten, the function 
 *      pointer must be dereferenced."
 * The solution was helped by Baltasarq's post in this 
 * Stack Overflow post:
 * https://stackoverflow.com/questions/3811328/try-to-write-char-to-a-text-file
 **********************************************************/
void arcVulnerability(const string & key)
{
   // load the 128-byte key into a char buffer
   char buffer[128];
   void (* endMessage)() = saved;

   // write the characters to buffer
   for (int i = 0; i <= 128; ++i)
   {
      buffer[i] = key[i];
   }

   // write the key to a character text file
   ofstream ofs; // solely for outputting to the file
   ofs.open("special-key.txt", ios::text);
   // check for failures
   if(ofs.fail())
   {
      endMessage = failedSave;
   }
   else
   {
      ofs.write(buffer, 128);
      ofs.close(); // close the file stream
   }

   // display end message
   (*endMessage)();

   return;
}

/***********************************************************
 * ARC INJECTION EXPLOIT
 * From (Helfrich, "Security for Software Engineers", 2019)
 * 1.  "The attacker must exploit a vulnerability allowing 
 *      unintended access to the function pointer."
 * 2.  "The attacker must have the address of another 
 *      function which is to be used to replace the existing
 *      function pointer."
 **********************************************************/
void arcExploit()
{
   string key = "cUWt+]}IBr/b~d ;~b&yW<C|<f Klu%3d[WUZ;P*E<lr=~mxJnIP}bf#a#<+.kZN.[}RT_<8vp>B*] ;.5Kn~p+e$NFZVN+j9sL&8(P:pZ/nH|MW/ECr.?sz@fIKJ$`.";
   arcVulnerability(key);
   return;
}

/***********************************************************
 * ARC INJECTION WORKING
 * Initiate normal behavior of arcVulerability()
 **********************************************************/
void arcWorking()
{
   string key = "cUWt+]}IBr/b~d ;~b&yW<C|<f Klu%3d[WUZ;P*E<lr=~mxJnIP}bf#a#<+.kZN.[}RT_<8vp>B*] ;.5Kn~p+e$NFZVN+j9sL&8(P:pZ/nH|MW/ECr.?sz@fIKJ$`.";
   arcVulnerability(key);
   return;
}
