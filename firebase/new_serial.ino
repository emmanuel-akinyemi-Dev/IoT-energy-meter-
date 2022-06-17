  
void  readata(){
  while (serial1.available() > 0)
  {
    c = serial1.read();//read incomming data

    if (c=='\n') 
    {
      break;
      }
    else {
      datain += c;
      }
    }
  
      if (c =='\n') 
    {
       breakdata();
       //Serial.print("sdata1 =" +sdata1);
      // Serial.print("sdata2 =" +sdata2);
       //Serial.print("sdata3 =" +sdata3);
       //Serial.print("sdata4 =" +sdata4);
       c = 0;
       datain="";

           }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//parse data. 
void breakdata(){
  indexOfA = datain.indexOf("A");
  indexOfB = datain.indexOf("B");
  indexOfC = datain.indexOf("C");
  indexOfD = datain.indexOf("D");

  sdata1 = datain.substring(0, indexOfA);
  sdata2 = datain.substring(indexOfA+1, indexOfB);
  sdata3 = datain.substring(indexOfB+1, indexOfC) ;
  sdata4 = datain.substring(indexOfC+1, indexOfD) ;

  }
  
