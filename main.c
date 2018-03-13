#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "parse.h"

static int read_section(dictionary *pdictionary,const char *sname)
{
    char buf[256];
	const char *p;
    int id;


	if (strlen(sname) > 128)
		return printf("too long section name \"%s\"\n", sname);

	/* Make sure mode is UBI, otherwise ignore this section */
	sprintf(buf, "%s:mode", sname);
	p = iniparser_getstring(pdictionary, buf, NULL);
	if (!p) {
		printf("mode key not found in section %s\n", sname);
	}
	/* If mode is not UBI, skip this section */
	if (strcmp(p, "ubi")) {
		printf("skip non-ubi section %s\n", sname);
	}
    printf("mode %s not found in section %s\n", p,sname);

	/* Fetch volume type */
	sprintf(buf, "%s:vol_type", sname);
	p = iniparser_getstring(pdictionary, buf, NULL);
	if (!p) {
		printf("volume type was not specified in section %s\n", sname);
	}
    printf("volume type %s in section %s\n",p, sname);

    /* Fetch the name of the volume image file */
	sprintf(buf, "%s:image", sname);
	p = iniparser_getstring(pdictionary, buf, NULL);
	if (p)
	{
		printf("image %s referred from section %s\n",p, sname);
	}
    printf("image %s in section %s\n",p, sname);

	/* Fetch volume id */
	sprintf(buf, "%s:vol_id", sname);
	id = iniparser_getint(pdictionary, buf, -1);
	printf("volume ID %d in section %s\n",id, sname);


	/* Fetch volume size */
	sprintf(buf, "%s:vol_size", sname);
	p = iniparser_getstring(pdictionary, buf, NULL);
	if (p)
	{
        printf("vol_size %s key not found in section %s\n", p,sname);
	}
    printf("vol_size %s in section %s\n",p, sname);

	/* Fetch volume name */
	sprintf(buf, "%s:vol_name", sname);
	p = iniparser_getstring(pdictionary, buf, NULL);
	if (!p)
		printf("vol_name key not found in section %s\n", sname);

     printf("vol_name %s in section %s\n",p, sname);


	return 0;
}


int main(int argc ,char *argv[])
{
    dictionary *pdictionary;
    int sects;
    int i;

    pdictionary = iniparser_load("ini.ini");
    if(!pdictionary)
    {
        printf("cannot load init file\n");
        return -1;
    }

    sects = iniparser_getnsec(pdictionary);
    if(sects == -1)
    {
        printf("cann't get section number \n");
        return -1;
    }
    printf ("------------sects=%d\n",sects);

    /*parse the section content*/
    for (i = 0; i < sects; i++)
    {
		const char *sname = iniparser_getsecname(pdictionary, i);

		if (!sname)
		{
			printf("ini-file parsing error (iniparser_getsecname)");
			return -1;
		}
        printf("-sname-%s\n",sname);

        /*display the init file*/
        iniparser_dump_ini(pdictionary,stdout);
        /*find\modify\add the section(entry)*/
        printf("1111111:%d\n",iniparser_find_entry(pdictionary,"mode"));
        printf("2222222:%d\n",iniparser_find_entry(pdictionary,"ubifs"));
        printf("3333333:%d\n",iniparser_find_entry(pdictionary,"ubifs:m2ode"));
		iniparser_setstring(pdictionary,"ubifs:m2ode","dddd");
		printf("3333333:%d\n",iniparser_find_entry(pdictionary,"ubifs:m2ode"));

		/*parse the section*/
		read_section(pdictionary,sname);
    }

    return;

}
