
#ifndef TYPE_SOUND_Desc
#define TYPE_SOUND_Desc

typedef struct{
  char address;       /*!< The address in the desc base. Idendifier of the desc. It is unique. */
  int nbWindows;	/*!< The number of Windows stored in the histogram */
  int** histogram;   /*!< This histogram sizes k*m.
                            k : Windows number
                            m : Intervals number */
}SoundDesc;

#endif

