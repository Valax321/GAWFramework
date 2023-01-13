let Module = {
    print: (text: string) => {
        console.log(text);
        const logElement = document.getElementById('log');
        const textElement = document.createElement('p');
        textElement.textContent = text;
        logElement.appendChild(textElement);
        textElement.scrollIntoView();
    },
    canvas: document.getElementById('canvas')
};