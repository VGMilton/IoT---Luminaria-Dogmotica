import { getElement } from 'ionicons/dist/types/stencil-public-runtime';
import { Injectable } from '@angular/core';
import { Firestore } from '@angular/fire/firestore';
import { collection, doc, getDocs, setDoc } from 'firebase/firestore';

@Injectable({
  providedIn: 'root',
})
export class FirebaseService {
  docRef: any;
  elements:any[]=[];

  constructor(private db: Firestore) {
  }


  async setElement(ruta:string,obj: any) {
    try {
      this.docRef = doc(this.db, ruta); //RUTA DE TABLA EN LA BD
      await setDoc(this.docRef, obj);
    } catch (error) {
      console.log(error);
    }
  }

  async loadData(ruta:string){
    try {
      const docs = await getDocs(collection(this.db,ruta));
      docs.forEach((doc)=>{
        const element = {
          id:doc.id,
          data:doc.data()
        };
        this.elements.push(element)
      })
    } catch (error) {
      throw error;
    }
  }
  getElements(){{
    return this.elements;
  }}
  getElement(index:number){
    return this.elements[index];
  }
}
