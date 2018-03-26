//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ULicense.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
bool __fastcall License(void)
{
  FILE *f;
  AnsiString S;
  BYTE b[6];
  char Str[20];
  int handle;
  long size;
  struct date D;
  bool Yes = true;

  getdate(&D);

  f = fopen("License.dat","rb");
  if(f)
  {
    if(!fscanf(f, "������������ ���: %s ", Str))
    {
      MessageBox(0, "�� ������ ���� ��������", "�������� ��������", MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
      return false;
    }
    fclose(f);

    handle = open("License.dat", O_WRONLY);
    lseek(handle, 6l, SEEK_END);    // ���� �� ������� ����� �� 6 ����
    write(handle, &b[0], 1);    // �������� 1 ���� �� �������� �����
    close(handle);

    f = fopen("License.dat","rb");
    fseek(f, -7, SEEK_END);
    for(int i = 0; i < 6; i++)
      fread(&b[i], 1, 1, f);
    fclose(f);
    if((b[0] == 0xFF) && (b[1] == 0xFF) && (b[2] == 0xFF) &&
       (b[3] == 0xFF) && (b[4] == 0xFF) && (b[4] == 0xFF))
    {
      Yes = false;
      MessageBox(0, "�������� ����������\n �������������� ������� �� �.225-45-82\n���� vlb@mnsk.belrw.com, starosty@mail.ru", "�������� ��������", MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
    }
    else if((b[0] == (BYTE)(255.0 * cos(b[3]))) && (b[1] == (BYTE)(100.0 * cos(b[4]))) && (b[2] == (BYTE)(190.0 * sin(b[5]))) &&
            (b[3] <= 31) && (b[4] <=  12))
    {
      D.da_year -= 2000;
      D.da_mon -= 1;
      if((b[5] < D.da_year) ||
         ((b[5] == D.da_year) && (b[4] < D.da_mon)) ||
         ((b[5] == D.da_year) && (b[4] == D.da_mon) && (b[3] < D.da_day)))
      {
        f = fopen("License.dat","r+b");
        fseek(f, -7, SEEK_END);
        b[0] = 0xFF;
        for(int i = 0; i < 6; i++)
          fwrite(&b[0], 1, 1, f);
        fclose(f);
        Yes = false;
        MessageBox(0, "�������� ����������\n �������������� ������� �� �.225-45-82\n���� vlb@mnsk.belrw.com, starosty@mail.ru", "�������� ��������", MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
      }
    }
    else
    {
      Yes = false;
      MessageBox(0, "���� �������� �������� ����������� ������\n �������������� ������� �� �.225-45-82\n���� vlb@mnsk.belrw.com, starosty@mail.ru", "�������� ��������", MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
    }

    handle = open("License.dat", O_WRONLY);
    size = filelength(handle);  /* ���������� ����� ����� */
    chsize(handle, size - 7);
    close(handle);
  }
  else
  {
    MessageBox(0, "�� ��������� ���� �������� License.dat", "�������� ��������", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    Yes = false;
  }
  return Yes;
}
//---------------------------------------------------------------------------
