import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { BtnComponent } from './btn/btn.component';
import { IonicModule } from '@ionic/angular';
import { FormsModule } from '@angular/forms';



@NgModule({
  declarations: [BtnComponent],
  imports: [
    CommonModule,
    IonicModule,
    FormsModule
  ],
  exports:[BtnComponent]
})
export class SharedComponentModule { }
