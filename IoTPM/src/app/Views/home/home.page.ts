import { getElement } from 'ionicons/dist/types/stencil-public-runtime';
import { FirebaseService } from './../../Services/firebase.service';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-home',
  templateUrl: './home.page.html',
  styleUrls: ['./home.page.scss'],
})
export class HomePage implements OnInit {
  buttons: any[] = [];

  constructor(private db: FirebaseService) {}
  async ngOnInit() {
    this.db.loadData('controlLED');
    this.buttons = this.db.getElements();
  }

  async changeState(i: number) {
    try {
      this.buttons[i].data.encender = !this.buttons[i].data.encender;

      const ruta = 'controlLED/' + this.buttons[i].id; // Asegúrate de tener la barra inclinada (/) para delimitar la colección y el documento
      const data = { encender: this.buttons[i].data.encender }; // Asegúrate de tener la barra inclinada (/) para delimitar la colección y el documento

      await this.db.setElement(ruta, data);
    } catch (error) {
      console.log(error);
    }

    console.log(this.buttons[i].data.encender);
  }
}
