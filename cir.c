double cir()
{

int x=-1;
int y=1;
int i;
for (i=0;i<240;i++)
{
x++;
if (x==20) { x=0; y++;}

TEllipse* e=new TEllipse(x/20.0,y/20.0,1/40.0,1/40.0);
cout <<x<<" "<<y<<endl;
e->SetFillColor(i);
e->Draw();

}



}