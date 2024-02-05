import { Component, Input, OnInit } from '@angular/core';

@Component({
  selector: 'app-btn',
  templateUrl: './btn.component.html',
  styleUrls: ['./btn.component.scss'],
})
export class BtnComponent  implements OnInit {
@Input() Label: string = "";
@Input() isChecked: boolean = false; // Puedes establecer el estado del checkbox

  constructor() { }

  ngOnInit() {}



}
