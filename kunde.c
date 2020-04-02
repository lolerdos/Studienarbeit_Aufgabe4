#include <stdio.h>
#include <string.h>
#include "kunde.h"



static Kunde_t StammInit[] =
                 {
                    {"Duck Donald",
                     {"Vogelweg", 3, "Entenhausen"},
                     "09999/991"},
                    {"Duck Daisy",
                     {"Vogelweg", 4, "Entenhausen"},
                     "09999/992"},
                    {"Duck Dagobert",
                     {"Kroesusstrasse", 1, "Dagoberts Palast"},
                     "09998/3"}
                 };

static Kunde_t *stamm=NULL;
static int      stammNum=0;

static void anschriftAusgeben(const Anschrift_t *anschrift);


void KundeAusgeben(const Kunde_t *kunde)
  {
   printf(" Name:    %s\n", kunde->name);
   anschriftAusgeben(&kunde->anschrift);
   printf(" Tel.Nr:  %s\n", kunde->telNr);
  }

static void anschriftAusgeben(const Anschrift_t *anschrift)
  {
   printf(" Strasse: %s %d\n", anschrift->strasse, anschrift->hausNr);
   printf(" Ort:     %s\n", anschrift->ort);
  }

void KundeStammAusgeben(void)
  {
   int pos;

   printf("Kundenstamm:\n\n");
   for(pos=0;pos<stammNum;pos++)
     {
      if (stamm[pos].name[0])
        {
         KundeAusgeben(&stamm[pos]);
         printf("\n");
        }
     }
  }

int KundeStammInit(void)
  {
   int pos;

   if ((stamm=malloc(sizeof(StammInit)))==NULL) return(KUNDE_STINI_FEHL);

   for(pos=0;pos<sizeof(StammInit)/sizeof(Kunde_t);pos++)
     {
      stamm[pos]=StammInit[pos];
     }
   stammNum=pos;

   return(KUNDE_STINI_OK);
  }

void KundeStammExit(void)
  {
   free(stamm);
  }

int KundeStammEintragen(const Kunde_t *kunde)
  {
   /* Positionsvariablen fuer freie Position im Kundenstamm und
      Position mit identischem Eintrag (Name)                   */
   int posFrei=-1, posIdent=-1;
   int pos;
   int stat=KUNDE_STEIN_FEHL_ALLG;

   for(pos=0;pos<stammNum;pos++)
     {
      if (stamm[pos].name[0])
        {
         if (strcmp(stamm[pos].name, kunde->name)==0) posIdent=pos;
        }
      else if (posFrei<0)
        {
         posFrei=pos;
        }
     }

   if (posIdent>=0)     stat=KUNDE_STEIN_FEHL_EXISTIERT;
   else
     {
      if (posFrei<0)
        {
         Kunde_t *stammNeu=realloc(stamm,(stammNum+1)*sizeof(Kunde_t));

         if (stammNeu!=NULL)
           {
            stamm=stammNeu;
            posFrei=stammNum;
            stammNum++;
           }
        }

      if (posFrei<0) stat=KUNDE_STEIN_FEHL_VOLL;
      else
        {
         /* Freie Position gefunden und Eintrag existiert
            noch nicht                                    */
         stamm[posFrei]=*kunde;
         stat=KUNDE_STEIN_OK;
        }
     }

   return(stat);
  }

int KundeStammLoeschen(const char *name)
  {
   int pos;
   int stat=KUNDE_STLOE_FEHL_ALLG;

   for(pos=0;pos<stammNum;pos++)
     {
      if (strcmp(stamm[pos].name, name)==0) break;
     }

   if (pos>=stammNum) stat=KUNDE_STLOE_FEHL_EXNICHT;
   else
     {
      stamm[pos].name[0]=0;
      stat=KUNDE_STLOE_OK;
     }

   return(stat);
  }
