#include "scene.h"

Scene::Scene(int max){
	if(max<0)
		max = 0;
	maxImages = max;
	//Image* foo[max];
	images = new Image*[max];
	xCoord = new int[max];
	yCoord = new int[max];
	for(int i=0;i<max;i++){
		images[i] = NULL;
	}
}
Scene::~Scene(){
	for(int i = 0; i<maxImages; i++){
		if(images[i]!=NULL){
			delete images[i];
			images[i]=NULL;
		}
	}
	delete[] images;
	delete[] xCoord;
	delete[] yCoord;
	images = NULL;
	xCoord = NULL;
	yCoord = NULL;
}

Scene::Scene(const Scene &source){
	maxImages = source.maxImages;
	xCoord = new int[maxImages];
	yCoord = new int[maxImages];
	images = new Image*[maxImages];
	for(int i=0; i<maxImages;i++){
		xCoord[i] = source.xCoord[i];
		yCoord[i] = source.yCoord[i];
		if(source.images[i]!=NULL){
			images[i] = new Image(*source.images[i]);
		}else{
			images[i] = NULL;
		}
	}
}
const Scene & Scene::operator= (const Scene &source){
	delete[] xCoord;
	delete[] yCoord;
	xCoord = NULL;
	yCoord = NULL;
//cout<<"x and y arrays deleted successfully"<<endl;
	for (int i = 0; i<maxImages;i++){
		if(images[i]!=NULL){
			delete images[i];
			images[i] = NULL;
			//cout<<"image "<<i<<" deleted successfully"<<endl;
		}
	}
//cout<<"contents of images succssfully deleted"<<endl;
	delete[] images;
//cout<<"images array successfully deleted"<<endl;
	maxImages = source.maxImages;
//cout<<"source file accessed"<<endl;
	xCoord = new int[maxImages];
	//cout << "LINE :" << __LINE__ << endl;
	yCoord = new int[maxImages];
	//cout << "LINE :" << __LINE__ << endl;
	images = new Image*[maxImages];
	//cout << "LINE :" << __LINE__ << endl;

	for(int i = 0; i<maxImages; i++){
		//cout << "LINE :" << __LINE__ << endl;
		xCoord[i] = source.xCoord[i];
		//cout << "LINE :" << __LINE__ << endl;
		yCoord[i] = source.yCoord[i];
		//cout << "LINE :" << __LINE__ << endl;
		if(source.images[i]!=NULL){
			images[i] = new Image(*source.images[i]);
			cout<<"an image copied"<<endl;
		}else{
			images[i] = NULL;//problem is that pointers for the image array of sc and set are the same.  have to make new image object rather than just copying over the pointers.  big problem.
		}
	}
	return *this;
}
void Scene::changemaxlayers(int newmax){
	if(newmax < 0){
		//cout<< "max pictures can't be negative" << endl;
		return;
	}
	int* temp=new int[newmax];
	Image** temp2= new Image*[newmax];
	int* temp3= new int[newmax];
	for(int i=0; i<newmax; i++){
		temp2[i] = NULL;
	}
	for(int i = 0; i<maxImages; i++){
		if(images[i] != NULL && i < newmax){
			temp[i] = xCoord[i];
			temp3[i] = yCoord[i];
			temp2[i] = images[i];
		}else if(images[i] != NULL && i>=newmax){
			delete [] temp;
			delete [] temp2;
			delete [] temp3;
			cout<<"invalid newmax"<<endl;
			return;
		}
	}
	delete[] xCoord;
	delete[] yCoord;
	delete[] images;
	xCoord = temp;
	yCoord = temp3;
	images = temp2;
	/*for(int i = 0; i<newmax; i++){
		if(i>maxImages){
			//xCoord[i] = NULL;
			//yCoord[i] = NULL;
			images[i] = NULL;
		}else{
			xCoord[i] = temp[i];
			yCoord[i] = temp3[i];
			images[i] = temp2[i];
		}
		delete temp2[i];
	}*/
	maxImages = newmax;
	return;
}
void Scene::addpicture(const char *FileName, int index, int x, int y){
	if(index<0||index>maxImages-1){
		cout << "index out of bounds" << endl;
		return;
	}
	Image* stuff = new Image();
	if(!stuff->readFromFile(FileName)){
		delete stuff;
		return;
	}
	if(images[index]!=NULL){
		delete images[index];
		images[index] = NULL;
	}
	images[index] = stuff;
	xCoord[index] = x;
	yCoord[index] = y;
	stuff = NULL;
}
void Scene::changelayer(int index, int newindex){
	if(index<0||index>maxImages-1||newindex<0||newindex>maxImages-1){
		cout<<"invalid index"<<endl;
		return;
	}
	if(index==newindex){
		return;
	}
	if(images[newindex]!=NULL){
		delete images[newindex];
		images[newindex] = NULL;
	}
	images[newindex] = images[index];
	xCoord[newindex] = xCoord[index];
	yCoord[newindex] = yCoord[index];
	if(images[index]!=NULL) {
		images[index] = NULL;
//cout<<"deleted image "<<index<<endl;
	}
	//xCoord[index]=NULL;
	//yCoord[index]=NULL;
	return;
}
void Scene::translate(int index, int xcoord, int ycoord){
	if (index<0||index>maxImages-1){
		cout<<"invalid index"<<endl;
		return;
	}
	xCoord[index] = xcoord;
	yCoord[index] = ycoord;
	return;
}
void Scene::deletepicture(int index){
	if(index<0||index>maxImages-1){
		cout<<"invalid index"<<endl;
		return;
	}
	if(images[index]!=NULL){
		delete images[index];
		images[index] = NULL;
	}
	return;
}
Image* Scene::getpicture(int index) const{
	if(index<0||index>maxImages-1){
		cout<<"invalid index"<<endl;
		return NULL;
	}
	return images[index];
}
Image Scene::drawscene() const{
	size_t height = 0;
	size_t width = 0;
	for(int i = 0; i<maxImages; i++){
		if(images[i]!=NULL){
			//cout<<"image "<<i<<" is not null"<<endl;
			if((images[i]->height()+yCoord[i])>(unsigned int)height){
				height = images[i]->height()+yCoord[i];
			}
			if((images[i]->width()+xCoord[i])>(unsigned int)width){
				width = images[i]->width()+xCoord[i];
			}
		}else{
			//cout<<"image "<<i<<" is null"<<endl;
		}
	}
	Image scene = Image();
	scene.resize(width, height);
	for(int q = 0; q<maxImages; q++){
		if(images[q]!=NULL){
			for(unsigned int i = xCoord[q];i<(xCoord[q]+images[q]->width()); i++){
				for(unsigned int j = yCoord[q];j<(yCoord[q]+images[q]->height());j++){
					*((&scene)->operator()(i,j))=*(images[q]->operator()(i-xCoord[q],j-yCoord[q]));
				}
			}
		}
	}
	return scene;
}
