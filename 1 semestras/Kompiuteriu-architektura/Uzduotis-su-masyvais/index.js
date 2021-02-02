let C = 0; //Teisingam programos veikimui reikalingas counter'is

// Taškų, kurie bus pavaizduoti scatter plot klasė
let Point = class {
	constructor(x, y){ //x - indeksas, y - atsitiktinis skaičius
		this.x = x;
		this.y = y;
	}
}

//Funkcija generuojanti atsitiktinius skaičius iki k
let generateNumbers = (A, n, k) => {

    for(let i = 0; i < n; i++){
        A[i] = Math.floor(Math.random() * (k)) + 1;
    }

}

//Funkcija sukurianti lentelę
let createTable = (A, begin, end) =>{

    let table = document.getElementById('results');

    for(let i = begin; i < end; i++){
        let tr = document.createElement('tr');
        let index = document.createElement('td');
        let val = document.createElement('td');
        let ir = document.createTextNode(i);
        let vr = document.createTextNode(A[i]);

        index.appendChild(ir);
        val .appendChild(vr);
        tr.appendChild(index);
        tr.appendChild(val);
        table.appendChild(tr);
    }

}

//Funkcija, kuri išvalo lentelę panaudojus slider'į
let clearTable = () => {
    let table = document.getElementById('results');
    while (table.lastElementChild) {
        table.removeChild(table.lastElementChild);
  	}
}

let removeSlider = () => {
	document.getElementById('slider-container')
		.removeChild(document.getElementById('slider-container').lastChild);
}

//Funkcija sukurianti slider'į
let createSlider = (n, i) => {
    let slider = document.createElement('input');
    slider.setAttribute("type", "range");
    slider.setAttribute("min", "2");
    slider.setAttribute("max", n);
    if(i === 'Begin'){
    	slider.setAttribute("value", 2);
    }
    else {
    	slider.setAttribute("value", n);
    }
    slider.setAttribute("class", "slider");
    slider.setAttribute("id", `myRange${i}`);

    document.getElementById('slider-container').appendChild(slider);
}

//Funkcija, kuri sukuria scatter plot pagal duotus duomenis
let createScatter = (Points, begin, end, c) => {
	let ctx = document.getElementById('myChart').getContext('2d');

	//Scatter plot konfigūracija
	let config = {
		type: 'scatter',
		data: {
			datasets: [{
				data: Points,
				backgroundColor: 'rgb(0, 0, 0)'
			}]
		},
		options: {
			legend: {
				display: false
			},
			scales: {
				xAxes: [{
					ticks: {
						max: end,
						min: begin,
						stepSize: 5
					},
					type: 'linear',
					position: 'bottom'
				}],
				yAxes: [{
					ticks: {
						max: end,
						min: begin,
						stepSize: 5
					}
				}]
			}
		}
	};
	
	//Tikrinama ar scatter plot matmenys keičiami naudojant slider'į
	if(c){
		window.myChart.destroy();
		window.myChart = new Chart(ctx, config);
		return 0;
	}
	window.myChart = new Chart(ctx, config);
	
}

//Sukuriamas duomenų masyvas panaudojant Point klasę
let createPoints = (A) => {
	
	let P = new Array();

	for(let i = 0; i < A.length; i++){
		let p = new Point(i, A[i]);
		P.push(p);
	}
	
	return P;

}

//Pagrindinė funkcija
let loadData = () => {

	//Tikrinama ar funkcija buvo paleista anksčiau
	if(C != 0){
		clearTable();
		removeSlider();
		window.myChart.destroy();
	}

    let n = document.getElementById('n').value;
	let k = document.getElementById('k').value;
	
	if(n > 999 || k > 999){
		alert('Naudokite mažesnius skaičius');
		return 0;
	}

	if(n < 1 || k < 1){
		alert('Naudokite didesnius skaičius');
		return 0;
	}

    let A = new Array(n);
	let P = new Array();
    
    createSlider(n, 'Begin');
    createSlider(n, 'End');

    let beginSlider = document.getElementById("myRangeBegin");
    let begin_val_output = document.getElementById("sb-value");
    begin_val_output.innerHTML = `Pradžios reikšmė: ${beginSlider.value}`;

    let endSlider = document.getElementById("myRangeEnd");
    let end_val_output = document.getElementById("se-value");
    end_val_output.innerHTML = `Pabaigos reikšmė: ${endSlider.value}`;

    generateNumbers(A, n, k);
	P = createPoints(A);
    createTable(A, 0, n);
	createScatter(P, parseInt(n), parseInt(n), false);

	//Naudojant slider'į, keičiamas scatter plot ir lentelės dydžiai
    beginSlider.oninput = function() {
        begin_val_output.innerHTML = `Pradžios reikšmė: ${this.value}`;
        clearTable();
		createTable(A, beginSlider.value, endSlider.value);
		createScatter(P, parseInt(beginSlider.value), parseInt(endSlider), true);

    }

    endSlider.oninput = function() {
        end_val_output.innerHTML = `Pabaigos reikšmė: ${this.value}`;
        clearTable();
		createTable(A, beginSlider.value, endSlider.value);
		createScatter(P, parseInt(beginSlider.value), parseInt(endSlider), true);

    }
    C++;
}

//Mirksinčio perspėjimo animacija. Nereikalinga, bet geriau atrodo :D

window.onload = () => {
	let t = document.getElementById('size-warning');	

	setInterval(() => {
		t.classList.toggle('red-text');
	}, 1000);
}






