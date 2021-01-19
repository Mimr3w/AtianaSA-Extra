/*===============================*
 *     CivType Autocorrect
 *        Version 1.0.0
 *        By King_Hual
 *===============================*/

#if defined _civtype_included
        #endinput
#endif
#define _civtype_included

stock CivConvert(const input[], output[], size)
{
	new curSize = 0, changes = 0, i=0;
	if(input[0] >= 97 && input[0] <= 122)
	{
		output[0] = input[0] - 32;
		i++;
	}
	else if(input[curSize] == 33 || input[curSize] == 44 || input[curSize] == 46 || input[curSize] == 63 || input[curSize] == 32)
	{
	    output[0] = input[0];
	    i++;
	}
	while(i<=size)
	{
		if(input[i] == '\0')
		{
		    if(input[curSize] != 33 && input[curSize] != 44 && input[curSize] != 46 && input[curSize] != 63 && input[curSize] != 32)
		    {
			    output[curSize+1] = 46;
			    output[curSize+2] = '\0';
		    }
		    break;
		}
		else {
		    curSize++;
		    changes = 0;
	  		if(input[i] == 105 && input[i-1] == 32 && input[i+1] == 32)
		    {
		        output[curSize] = input[i] - 32;
		        changes = 1;
		    }
		    if(input[i] >= 65 && input[i] <= 90 && input[i-1] != 32)
		    {
		        output[curSize] = input[i] + 32;
		        changes = 1;
		    }
			switch(input[i])
			{
			    case 33,44,46,63:
			    {
			        if(input[i+1] != 33 && input[i+1] != 44 && input[i+1] != 46 && input[i+1] != 63 && input[i+1] != 32)
					{
					    output[curSize] = input[i];
					    curSize++;
						output[curSize] = 32;
						curSize++;
						if(input[i+1] >= 97 && input[i+1] <= 122 && input[i] != 44)
						{
							output[curSize] = input[i+1] - 32;
						}
						else
						{
						    output[curSize] = input[i+1];
						}
						changes = 1;
						i++;
					}
	   				else if(input[i+1] != 33 && input[i+1] != 44 && input[i+1] != 46 && input[i+1] != 63 && input[i+1] == 32 && input[0] >= 97 && input[0] <= 122 && input[i] != 44)
				    {
						output[curSize] = input[i];
						curSize++;
						output[curSize] = input[i+1];
						curSize++;
				    	output[curSize] = input[i+2] - 32;
				        changes = 1;
				        i+=2;
				    }
			    }
			}
			if(input[i] == 32 && (input[i+1] == 111 || input[i+1] == 79) && (input[i+2] == 114 || input[i+2] == 82) && input[i+3] == 32)
			{
			    if(input[i-1] != 33 && input[i-1] != 44 && input[i-1] != 46 && input[i-1] != 63 )
			    {
					output[curSize] = 44;
					curSize++;
					output[curSize] = input[i];
					curSize++;
					output[curSize] = input[i+1];
					curSize++;
					output[curSize] = input[i+2];
					curSize++;
					output[curSize] = input[i+3];
					changes = 1;
					i+=3;
				}
				else if(input[i+1] == 111) {
        			output[curSize] = input[i];
					curSize++;
					output[curSize] = input[i+1] - 32;
					curSize++;
					output[curSize] = input[i+2];
					curSize++;
					output[curSize] = input[i+3];
					changes = 1;
					i+=3;
				}
				
			}
			if(changes == 0)
			{
  				output[curSize] = input[i];
			}
	    }
		i++;
	}
	return strlen(output);
}
