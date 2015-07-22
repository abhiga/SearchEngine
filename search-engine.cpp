
#include <string.h>
#include "search-engine.h"

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
  // Create dictionary of the indicated type

  // Populate dictionary and sort it if necessary
	if (dictionaryType == ArrayDictionaryType) {
		_wordToURLList = new ArrayDictionary();
	}
	else if (dictionaryType == AVLDictionaryType) {
		_wordToURLList = new AVLDictionary();
	}
	else if (dictionaryType == BinarySearchDictionaryType) {
		_wordToURLList = new BinarySearchDictionary();
	}
	else if (dictionaryType == HashDictionaryType) {
		_wordToURLList = new HashDictionary();
	}
	else {
		exit(1);
	}
	int count = 0;
	int countLines = 0;
	int c;
	char *url;// = new char[400];
	char *desc;// = new char[1000];
	int index;
	char *temp;// = new char[1000];
	char * elem;// = new char[1000];
	FILE *fd = fopen("url.txt","r");
	if(fd == NULL) {
		printf("Could not open file %s\n", "url.txt");
		exit(1);
		
	}
	else {
		while ((c=fgetc(fd))!=-1) {
		if(c=='\n')
			countLines++;
		}
	}
	fclose(fd);
	int numUrls = countLines/3;
	URLRecord **list = new URLRecord*[2000];
	fd = fopen("url.txt","r");
	for(int i = 0; i < numUrls; i++) 
		list[i] = new URLRecord();
	while (fgets(temp,1000,fd)) {
		if(strcmp(temp,"\n")) {
			elem = strtok(temp," ");
			printf("%d",index);
			index = atoi(elem);
			elem = strtok(NULL," ");
			list[index]->_url = strdup(elem);
			//printf("%s",url);
			fgets(temp,1000,fd);
			elem = strtok(temp,"\n");
			list[index]->_description = strdup(elem);
			//printf("%s\n",desc);
		}
	}
	//while(fscanf(fd, "%s", temp)==1){
			//fscanf(fd, "%s",desc);
			//fscanf(fd, "%s",next);
		/*while(fgets(temp,1000,fd)) {
			if(strncmp(temp,"\n",1)) {
				strcpy(desc,temp);
				//url = strstr(temp, "http://");
				url = strtok(strstr(temp, "http://"), "\n");
				if (url!=NULL)				
					printf("%s\n",url);
				else 
					printf("%s\n",desc);
			}

		}*/
	countLines = 0;
	fclose(fd);
	fd = fopen("word.txt","r");
	if(fd == NULL) {
		printf("Could not open file %s\n", "word.txt");
		exit(1);
		
	}
	else {
		/*while ((c=fgetc(fd))!=-1) {
		if(c=='\n')
			countLines++;
		}*/
	
		//printf("%d\n",countLines);	
			/*if(strncmp(temp, "http://",strlen("http://"))==0){
				printf("%s\n",temp);
				printf("%s\n",desc);
				desc[0] = '\0';
				count = 0;
			}
			else {
				if(count == 0) {
					strcpy(desc, temp);
				count = 1;
				}
				else {
				strcat(desc," ");
				strcat(desc,temp);
				}
			}
		}*/
		char *word;
		/*while (fgets(temp, 1000, fd)) {
			if (strcmp(temp, "\n")) {
				elem = strtok(temp, " ");
				//word = strdup(elem);
				//elem = strtok(NULL, " \n");
				printf("%s\n", elem);
				/*while (elem!=NULL) {
					index = atoi(elem);
					printf("%d\n", index);
					elem = strtok(NULL, " \n");
				}
			//} 
			}
		//while(fscanf(fd, "%s", temp)==1){
			//printf("%s\n",temp);
		}*/
		while (fgets(temp, 1000, fd)) {
			if (strcmp(temp, "\n")) {
				elem = strtok(temp, " \n");
				word = strdup(elem);
				URLRecordList *head = NULL;
				URLRecordList *prev = NULL;
				elem = strtok(NULL, " \n");
				while (elem != NULL) {
					index = atoi(elem);
					if (list[index]->_url == NULL)
						continue;
					URLRecordList *tmp = new URLRecordList();
					if (head == NULL)
						head = tmp;
					tmp -> _urlRecord = list[index];
					if (prev != NULL)
						prev -> _next = tmp;
					prev = tmp;
					elem = strtok(NULL, " \n");
				}
			
				_wordToURLList->addRecord(word, head);
			
				delete word;
				delete elem;
			}
		}

		
	}		
	
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }

  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
  
  const int nurls=2;

  const char * words = "data structures";

  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };

  fprintf( stderr, "Search for words: \"%s\"\n", words);

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", words );

  for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }

  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
