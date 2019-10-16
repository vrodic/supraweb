#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <iterator>

using namespace std;
#include "stringtok.h"
//#include "icstring.h"



extern "C" {
#include <web_server.h>
}

#include "main.h"
#include "parts.h"

#define BUFLEN 10000

void outputStandardPage(char *title, const char *content)
{

	
	
}

char *tekst;
char buffer[BUFLEN];
int tlen = 0;


void index_html()
{
	//char *ErrMsg = 0;
	//char *tekst;
	char **result;
	int r =1, nrow = 0, ncolumn = 0, i,j;
	
	int gpYearBegin =0, gpYearEnd =0, id;
	
		

	printf("Content-type: text/html\r\n\r\n");
	printf(HTML_HEADER,"Supra");
	
	printf("<table cellspacing=5><tr><td>");

	r = sqlite_get_table(db, "SELECT articleyear FROM sp_articles ORDER BY articleyear ASC limit 1;", &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		gpYearBegin = atoi(result[1]);	
		sqlite_free_table(result);
	} 


	r = sqlite_get_table(db, "SELECT articleyear FROM sp_articles ORDER BY articleyear DESC limit 1;", &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		gpYearEnd = atoi(result[1]);	
		sqlite_free_table(result);
	} 	

		
	/*r = sqlite_get_table(db, "SELECT count(*) FROM sp_articles;",  &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		onum = atoi(result[1]);
		sqlite_free_table(result);
	} */
	
	
	printf("<div align=\"center\">
  <p><font size=\"+1\" face=\"Verdana, Arial, Helvetica, sans-serif\">Interna Sudska Praksa
    - Odluke Viših sudova povodom rješavanja pravnih lijekova na odluke Općinskog suda u Zagrebu. <br><br>
    Građansko pravo: %d - %d <br>Kazneno pravo:  -  <br><br></font></p>
<br>", gpYearBegin, gpYearEnd);

	printf("<br>
  <p>&nbsp;</p>
  <form method=\"get\" action=\"search\">
   	<select name='type'>");
	char **result2;
	int r2 =1, nrow2 = 0, ncolumn2 = 0,cnt;
	ostringstream bo;
		
	r = sqlite_get_table(db, "SELECT id, title FROM sp_types ORDER BY id ASC",  &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		
		for (i = 1; i < nrow+1; i++) 
		{
			id = atoi(result[ncolumn*i]);
			r2 = sqlite_get_table_printf(db, "SELECT count(*) FROM sp_articles WHERE typeid='%d'",  &result2, &nrow2, &ncolumn2, &zErrMsg, id);
			cnt = atoi(result2[1]);
			sqlite_free_table(result2);
			cout << "<option value='" << id << "'>" << result[ncolumn*i+1] << "</option>"; 
			bo << result[ncolumn*i+1] << ": " << cnt << "<br>";
		}
		sqlite_free_table(result);
	} 	
    
      
      printf("</select><br><br>");
      /*
     printf("Traženi pojam/pojmovi su
      <select name='sm1'>
	<option value='0'>Bilo gdje u tekstu</option>
	<option value='1'>Samo cijela riječ/riječi</option>
	<option value='2'>Početak riječi</option>
      </select>
      <br>");
      */
      printf("Traženi pojmovi:<br>
      <input type=\"text\" name=\"q\" size=55>
	<br>Pretraži odluke u rasponu od
<select name='yg'>");

for (i = 1983; i < gpYearEnd+1;i++)
{
	printf("<option value='%d'>%d</option>",i, i);
}
printf("</select>g. do&nbsp;<select name='yl'>");

for (i = gpYearEnd+1; i > 1983 ;i--)
{
	printf("<option value='%d'>%d</option>", i, i);
}

printf("</select>g.<br>
<table><tr>
     <td align='right'> Oznaka</td><td align='center'><input type='text' name='o'></td></tr>
 <tr>    <td> Zakon</td><td>" );
 
 /*
  printf("<select name='zid'>");
  sqlite_get_table(db,"SELECT id, title FROM sp_laws order by title;", &result, &nrow, &ncolumn, &zErrMsg);
  

  for (i = 0; i < nrow; i++) {
	for (j = 0; j < ncolumn; j++) {
	
	printf("<option size=20 value='%d'>%s </option>", i, result[(i*ncolumn)+j]);
	}

  }
  sqlite_free_table(result);
	

 printf("</select>");
 */
 printf("<input type='text' name='z'>");
printf(" </td></tr>
 </table>
       <input type=\"submit\" name=\"Submit\" value=\"Traži\">
  </form>
  <p>&nbsp; </p>
</div>
<br>
<a href='time'> Pregled po godinama</a>
<br>
<div align='right'>Broj odluka u bazi:<br>");
cout << bo.str();
printf("</div><hr>
Uputstvo za pretraživanje: Upisati jedan ili više pojmova.<br>
Primjer 1: <b>naknada štete</b> - rezultat je bilo koja odluka koja sadrži riječi <b>naknada</b> i <b>štete</b> <br>");

//printf("Primjer 2: <b>\"naknada štete\"</b> - rezultat je bilo koja odluka koja sadrži pojam <b>naknada štete</b><br>");
printf("<BR>Ukoliko želite pretraživanje svih oblika (padeža itd.) zadanog pojma upišite korijen riječi.<br>

<br><br>
<div align='center'><a href=info>Copyright & Info</a></div>");
	
printf("</td></tr></table>");	
 
	printf(HTML_TERM);
	//free(tekst);
	
}


////////////////////////////////////////////////////////////
//	SEARCH PAGE
////////////////////////////////////////////////////////////

void search_html() 
{
	char **result;
	int r =1, nrow = 0, ncolumn = 0, i,j;
	
	
	list<string> ls;
	
	
	ostringstream cond;
	ostringstream query;
	
	printf("Content-type: text/html\r\n\r\n");
	printf(HTML_HEADER,"Supra");
	printf("<a href='/'>Trazenje</a>&nbsp;<a href='time'>Odabir po godinama</a>");
	cout << "<table cellpadding=\"5\" cellspacing=\"2\" width=\"100%\"><tr><td>";

	// limit
	int limit = 10;
	// input parametri
	string q = ClientInfo->Query("q");
	int doyear = atoi(ClientInfo->Query("doyear"));
	int domonth = atoi(ClientInfo->Query("domonth"));
	int zid = atoi(ClientInfo->Query("zid"));
	int offset = atoi(ClientInfo->Query("offset"));
	int yg = atoi(ClientInfo->Query("yg"));
	int yl = atoi(ClientInfo->Query("yl"));
	int type = atoi(ClientInfo->Query("type"));
	
	if (offset < 0) offset = 0;
	
	ostringstream lstr;
	int o1,o2;
	
	lstr << "LIMIT " << limit;
	
	if (offset) {
		lstr << " OFFSET " << offset;
	}
	if (q.size() > 0) {	
	
		stringtok (ls, q);
		for (list<string>::const_iterator z = ls.begin(); z != ls.end(); ++z)
   		{
			cond << " content like '%" << (*z) << "%' AND";
		} 
	
	}
		
	if (strlen(ClientInfo->Query("z")) >0) {
		cond << " law like '%" << ClientInfo->Query("z") << "%' AND";
	}
	
	if (zid) {
		if (zid > 1) {
			cond << " lawid='" << zid << "'  AND";
		}
	}
	if (strlen(ClientInfo->Query("o")) >0) {
		cond << " code1 like '%" << ClientInfo->Query("o") << "%' OR code2 like '%" 
		<< ClientInfo->Query("o") << "%' AND";
	}

	if (yg) {
		cond << " articleyear >='" << yg << "' AND";
	}
	if (yl) {
		cond << " articleyear <='" << yl << "' AND";
	}

	if (type) {
		cond << " typeid ='" << type << "' AND";
	}
	
	if (doyear) {
		cond << " articleyear='" << doyear << "' AND";
	}
	
	if (domonth) {
		cond <<  " articlemonth='" << domonth << "' AND";
	}
	
	//s = ClientInfo->Query("q");
	
	//cout << cond.str();
	
	string t = cond.str();
	t = t.substr(0, t.size()-3);
	int count;
	
	query << "SELECT count(*) FROM sp_articles WHERE " << t <<";";
	//cout << query.str();
	int num;	
	r = sqlite_get_table(db, query.str().c_str(), &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		count = atoi(result[1]);	
		sqlite_free_table(result);
	} 
	if (count == 0) {
		cout << "<br>Nije pronađena niti jedna odluka<br>";
		return;
	}
	
	ostringstream query2;
	
	query2 << "SELECT * FROM sp_articles WHERE " << t << " ORDER BY articleyear DESC, articlemonth ASC, articleno ASC " << lstr.str();
	
	r = sqlite_get_table(db, query2.str().c_str(), &result, &nrow, &ncolumn, &zErrMsg);
	
	o1 = offset +1;
	o2 = offset +limit;

	if (count < offset + limit)
		{o2 = count;}
	
	cout << "<table cellpadding=\"2\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tbody>
	<tr><td valign=\"top\" bgcolor=\"#333399\"><font color=\"#ffffff\">Pretraga:" << q.c_str() 
	<<  " " ;
	if (doyear) cout << doyear;
	cout << "</font><br></td><td valign=\"top\" bgcolor=\"#333399\" align=\"right\">
	<font color=\"#ffffff\">Rezultati " << o1 << " - " << o2 <<" od " << count << "</font><br></td></tr>
	</tbody></table>";
	
	int pos1 =0,pos2 =0;
	
	//cout << "<table><tr><td>";
	for (i = 1; i < nrow+1; i++) 
	{
	
		j = i  +offset;
		printf(result[ncolumn*i]);
		//string id(result[ncolumn*i]);
		string articleno(result[ncolumn*i+1]);
		string articleyear(result[ncolumn*i+2]);
		//string articlemonth(result[ncolumn*i+3]);
		
		

		//string code1(result[ncolumn*i+5);
		//string code2(result[ncolumn*i+6]);
		//string title(result[ncolumn*i+7);
		string content(result[ncolumn*i+8]);
		//string law(result[ncolumn*i+9]);
				
		if (q.size() > 0) {	
	
		stringtok (ls, q);
		for (list<string>::const_iterator z = ls.begin(); z != ls.end(); ++z)
   		{
			pos1 = 0;
			pos2 = 0;
			int rl = 1;
			while ( rl ) {
			ostringstream ss1;
			
			pos1 = content.find ((*z), pos2) ;
		//	fprintf(stderr, "%d\n", pos1);
			if (pos1 >= 0 ) {
			pos2 = pos1 + z->size()+7;
			ss1 << "<b>" << (*z) << "</b>";
			content.replace(pos1, z->size(), ss1.str());
			} else {rl = 0;}
			}
		} 
		}
	
		
		cout  <<j << "<br><table width=\"100%\" border=\"0\"><tr><td><b>Godina: "
		 << articleyear;
		 if (result[ncolumn*i+3]) {
		 	cout << " mjesec: " << result[ncolumn*i+3];
		 }
		 
		 cout <<  " Odluka: " << articleno << "</b></td><td></td></tr><tr><td><b>";
		 if (result[ncolumn*i+5]) {
		 	cout << result[ncolumn*i+5];
		 }
		 cout <<"</b></td><td><div align=\"right\"><b>";
 		 if (result[ncolumn*i+6]) {
		 	cout << result[ncolumn*i+6];
		 }		 
		 
		 cout <<" </b></div></td></tr></table>";
     		if (result[ncolumn*i+9]) 
		 cout << "<b>" << result[ncolumn*i+9] << "</b><br>";
     		 cout << content << "<br><br>";
	}
	cout << "</td></tr></table>";
	
	int pages, pagen,o3,o0;
	pages = count / limit; //php divides int differently?
	pagen = offset/limit;
	float pagesf = (float)count/ (float)limit;
//	fprintf(stderr, "%f\n", pagesf);
	if ((pagesf - pages) > 0) {
		pages++;
	} 
	cout << "<div align=\"center\">";
	string quer(ClientInfo->QueryString);
	int pos = quer.rfind("&offset");
	string quer2 = quer.substr(0, pos);
	//cout << quer2 ;
		if (offset > 0) {
			o0 = offset - limit;
			if (o0 < 0) o0 = 0;

			cout << "<a href=search?" << quer2 << "&offset=" << o0 << ">Predhodna</a> &nbsp;";
		}

		for (i = 0; i < pages; i++)
		{
			j = i +1;
			if (i == pagen)
			{
				cout  << j << "&nbsp;";
			} else {
				o3 = limit*i;

				cout <<  "<a href=search?" << quer2 <<  "&offset=" << o3 << ">" << j <<" </a> &nbsp;";
			}
		}
		if (count > limit+offset ) {
			cout <<  "<a href=search?" << quer2 <<  "&offset=" << o2 << ">" << "Slijedeca</a>";
			
		}
		cout << "</div>";	
	
	if (r != SQLITE_OK) return;
	
	ostringstream top; 
	
	
	//r = sqlite_get_table_printf(db, "SELECT articleyear FROM sp_articles ORDER BY articleyear ASC limit 1;", &result, &nrow, &ncolumn, &zErrMsg);
	
	
	 
/*
	printf("Content-type: text/html\r\n\r\n");
	printf("<HTML>\n");
	printf("<BODY bgcolor='EFEFEF'>\n");
	printf("libwebserver Example<BR><BR>\n");
	printf("Client info structure:<BR><code>\n");	
	printf("struct ClientInfo {<BR>\n
	&nbsp;&nbsp;&nbsp;int outfd<BR>\n
	&nbsp;&nbsp;&nbsp;char *inetname<BR>\n
	&nbsp;&nbsp;&nbsp;char *request<BR>\n
	&nbsp;&nbsp;&nbsp;char *method<BR>\n
	&nbsp;&nbsp;&nbsp;char *user<BR>\n
	&nbsp;&nbsp;&nbsp;char *pass<BR>\n
	&nbsp;&nbsp;&nbsp;char *QueryData;<BR>\n	
	&nbsp;&nbsp;&nbsp;struct memrequest *mem;<BR>\n	
	&nbsp;&nbsp;&nbsp;char *(*Header)(char*);<BR>\n
	&nbsp;&nbsp;&nbsp;char *(*QueryString)(char*);<BR>\n
	&nbsp;&nbsp;&nbsp;char *(*Post)(char*);<BR>\n
	&nbsp;&nbsp;&nbsp;char *(*MultiPart)(char*);<BR>\n
	};<BR>\n");
	printf("ClientInfo->outfd=%d<BR>\n",ClientInfo->outfd);
	printf("ClientInfo->request=%s<BR>\n",ClientInfo->request);
	printf("ClientInfo->method=%s<BR>\n",ClientInfo->method);
	printf("ClientInfo->Header(\"Host\")=\"%s\"<BR>\n",ClientInfo->Header("Host"));
	printf("ClientInfo->Header(\"Accept\")=\"%s\"<BR>\n",ClientInfo->Header("Accept"));
	printf("ClientInfo->Query(\"teste\")=\"%s\"<BR>\n",ClientInfo->Query("teste"));
	printf("ClientInfo->QueryString=\"%s\"<BR>\n",ClientInfo->QueryString);
	printf("ClientInfo->Post(\"dev\")=\"%s\"<BR>\n",ClientInfo->Post("dev"));
	printf("ClientInfo->MultiPart(\"teste\").data=\"%s\"<BR>\n",ClientInfo->MultiPart("teste").data);
	printf("ClientInfo->MultiPart(\"file1\").filename=\"%s\"<BR>\n",ClientInfo->MultiPart("file1").filename);
	printf("ClientInfo->MultiPart(\"file1\").size=\"%d\"<BR>\n",ClientInfo->MultiPart("file1").size);
	printf("ClientInfo->MultiPart(\"file1\").data=\"");
	fwrite(ClientInfo->MultiPart("file1").data,ClientInfo->MultiPart("file1").size,1,stdout);
	printf("\"<BR>\n");
	printf("<form action='/?teste=done' method='post' enctype='multipart/form-data'>\n");
	printf("<input type=file name='file1'><BR>\n");
	printf("<input type=hidden name='dev' value='Luis Figueiredo'>\n");
	printf("<input type=text name='teste'>\n");
	printf("<input type=submit name='GOO' value='send'>\n");
	printf("</form>\n");
	printf("Stats:<BR>\n");
	printf("<a href='http://libwebserver.sourceforge.net'><img border='0' src='/libwebserver.gif'></a><br>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
*/
	cout << HTML_TERM;

	
};

void time_html()
{
	char **result,**result2;
	int r =1, nrow = 0, ncolumn = 0, i,j;
	int nrow2 = 0, ncolumn2 = 0;
	
	int year, month;
	
	printf("Content-type: text/html\r\n\r\n");
	printf(HTML_HEADER,"Supra");
	printf("<a href=../supra>Povratak na pocetak<br><br>");
	
	string query ("SELECT DISTINCT articleyear FROM sp_articles ORDER BY articleyear;");
	r = sqlite_get_table(db, query.c_str(), &result, &nrow, &ncolumn, &zErrMsg);

	cout <<  "<table><tr>";
	for (i = 1; i < nrow +1; i++)
	{
		cout << "<td valign='top'>";
		year = atoi(result[ncolumn*i]);
		cout <<  "<a href='search?doyear=" << year << "'>" << year <<"</a>&nbsp;";
		if (year > 2001) {
		ostringstream query2;
		query2 << "SELECT DISTINCT articlemonth FROM sp_articles WHERE  articleyear='" << year << "' ORDER BY articlemonth;";

		
		r = sqlite_get_table(db, query2.str().c_str(), &result2, &nrow2, &ncolumn2, &zErrMsg);
	
		for (j = 1;  j < nrow2+1; j++)
		{
			month = atoi(result2[ncolumn2*j]);
			cout << "<br><a href='search?doyear=" << year << "&domonth="  << month << "'>" << month <<"</a>&nbsp;";
		}
		sqlite_free_table(result2);
		}
		
		
		
		cout << "</td>";		
	}

	cout << "</tr></table>";
	sqlite_free_table(result);
	/*
	cout << "<br><br><b>2002 po mjesecima</b><br><br>";
	
	string query2("SELECT DISTINCT articlemonth FROM sp_articles WHERE  articleyear='2002' ORDER BY articlemonth;");
	
	r = sqlite_get_table(db, query2.str().c_str(), &result2, &nrow2, &ncolumn2, &zErrMsg);

	for (i = 1; i < nrow +1; i++)
	{
	
		cout << "<a href='search?doyear=2002&domonth=" << result[ncolumn*i] << "'>" << result[ncolumn*i] << "</a>&nbsp;";
	}
	
	sqlite_free_table(result);
	*/
	cout << HTML_TERM;

}

void bg1_jpeg ()
{
	printf("Content-type: image/jpeg\r\n\r\n");	
	web_client_addfile("bg1.jpg");
}

void info_html()
{
	char **result;
	int r =1, nrow = 0, ncolumn = 0, onum;
		
	printf("Content-type: text/html\r\n\r\n");
	printf(HTML_HEADER,"Supra");

	r = sqlite_get_table(db, "SELECT count(*) FROM sp_articles;",  &result, &nrow, &ncolumn, &zErrMsg);
	if (r == SQLITE_OK) {
		onum = atoi(result[1]);
		sqlite_free_table(result);
	} 

	cout << "<br><br><br><div align='center'>Redaktor: Nikola Opatic, sudac<br><br>
	Autor programa za pretrazivanje: <a href='mailto:vedran.rodic@zg.hinet.hr?subject=SUPRA'>Vedran Rodic</a><br><br>
	</div>
	<hr>
	Broj sudskih odluka u bazi:" << onum<<  "<br>";
	cout << HTML_TERM;
	
}
