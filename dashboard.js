// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.20.0/firebase-app.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration here (Do not use the existing configuration)
const firebaseConfig = {
  apiKey: "AIzaSyCeVkSnOVDvCdxP49_FIJHph3IbvELYm2s",
  authDomain: "coba-17953.firebaseapp.com",
  databaseURL: "https://coba-17953-default-rtdb.firebaseio.com",
  projectId: "coba-17953",
  storageBucket: "coba-17953.appspot.com",
  messagingSenderId: "690263688101",
  appId: "1:690263688101:web:30b779c0d4ca580cb45e4c",
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// getting reference to the database
var database = firebase.database();

//getting reference to the data we want

var dataRef2 = database.ref("WQMS/temperature");

var angka = 10;

//fetch the data

dataRef2.on("value", function (getdata2) {
  var temp = getdata2.val();
  document.getElementById("temperature").innerHTML = temp + "&#8451;";
  angka = temp;
});

console.log(angka);

var data = {
  labels: [0],
  datasets: [
    {
      label: "Dataset 1",
      data: [0],
      borderColor: "rgb(75, 192, 192)",
      lineTension: 0.5,
      backgroundColor: "#9966ff",
    },
  ],
};

var config = {
  type: "line",
  data: data,
  options: {
    scales: {
      y: {
        max: 100,
        min: 0,
      },
    },
  },
};

var myChart = new Chart(document.getElementById("myChart"), config);

window.setInterval(myCallback, 2000);

function myCallback() {
  var now = new Date();
  now = now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
  var value = Math.floor(Math.random() * 100);
  //   console.log(value);

  //   console.log(now);

  if (data.datasets[0].data.length >= 20) {
    data.labels.shift();
    data.datasets[0].data.shift();
  }
  data.labels.push(now);
  data.datasets[0].data.push(angka);

  //   //   console.log(data);
  //   console.log(data.labels);
  //   console.log(data.datasets[0].data);

  myChart.update();
}
