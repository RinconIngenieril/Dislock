# Dislock

A simple computer screen locker using a distance sensor.

***

Dislock es un proyecto con el cual puedes bloquear tu ordenador usando tan solo un **Arduino Leonardo** y un sensor de **ultrasonidos**.

El código se encarga de calcular la distancia por medio del sensor de ultrasonidos **SRF05** y compararla con la distancia máxima permitida. Si se supera este valor máximo durante más de 1 segundo se envia el shortcut de bloqueo de pantalla por USB.

## Consideraciones

El sistema envía el shortcut **CTRL + ALT + L**. Este es un shortcut de bloqueo de pantalla en Ubuntu, aunque no viene configurado siempre por defecto.

Si usas otro sistema operativo asegurate de configurar el shortcut adecuado en la función **void doYourMagic()** del código de Arduino.

## Calibración

Acerca la mano a **menos de 10 cm del sensor**, el LED se apagará y tendrás 5 segundos para retirar la mano del sensor y colocarte en la posición y distancia natural en la silla.

El LED de estado parpadeará 4 veces para indicar que empieza el proceso de calibración. Mantente quietx hasta que el LED se encienda de manera permanente, esto indicará que el proceso de calibración se ha realizo con éxito y el sistema está armado.

Si en lugar de encenderse de manera fija, el LED vuelve a parpadear 4 veces es que el proceso de calibración ha fallado y por tanto el sistema a empezado a calibrarse de nuevo.

## Habilitar o deshabilitar el sistema

Existe una forma de deshabilitar el sistema de tal manera que no se envíe el shortcut de bloqueo al ordenador aunque se detecte que trigger que lo provocaría.

Para deshabilitar el sistema debes poner la mano a menos de 10 cm hasta que parpadee el LED 2 veces, 5 segundos aproximadamente.

Cuando el sistema está deshabilitado el LED de estado se enciende variando su brillo.

Para volver a habilitar el sistema repite el paso anterior. Debes poner la mano a menos de 10 cm hasta que parpadee el LED 2 veces, 5 segundos aproximadamente.

***

Queda pendiente crear una carcasa imprimible en 3D para montar el sistema

***

¡Cualquier idea es bien recibida!

***

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Licencia Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Dislock</span> by <span xmlns:cc="http://creativecommons.org/ns#" property="cc:attributionName">Enrique Gómez, Rincón Ingenieril</span> licensed by <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.<br /><br />
