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
 **********************************************************/
void arcVulnerability(/* arguments */)
{
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
   arcVulnerability(/* parameters with malicious data */);
   return;
}

/***********************************************************
 * ARC INJECTION WORKING
 * Initiate normal behavior of arcVulerability()
 **********************************************************/
void arcWorking()
{
   arcVulerability(/* parameters with no malicious data */);
   return;
}
