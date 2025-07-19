


<template>
  <h3>Selecciona la dirección:</h3>
  <div class="botones">
    
          <div class="botones-direccion">
        <button class="direccion" :disabled="clockwise" :class="{ 'boton-seleccionado': clockwise }" id="boton1" @click="seleccionarDirreccion('clockwise')">
            <svg class="invertida" viewBox="0 0 24 24" fill="none" stroke="black" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <polyline points="1 4 1 10 7 10"></polyline>
            <path d="M3.51 15a9 9 0 1 0 2.13-9.36L1 10"></path>
            </svg>
        </button>
        </div>


        <!-- Flecha circular normal -->
         <div class="botones-direccion" >
        <button class="direccion" :class="{ 'boton-seleccionado': counterClockwise }" id="boton2" :disabled="counterClockwise"  @click="seleccionarDirreccion('counterClockwise')">
            <svg viewBox="0 0 24 24" fill="none" stroke="black" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <polyline points="1 4 1 10 7 10"></polyline>
            <path d="M3.51 15a9 9 0 1 0 2.13-9.36L1 10"></path>
            </svg>
        </button>
        </div>
        {{ clockwise }}
        {{ counterClockwise }}
  </div>
</template>

<script>
import { useMotorStore } from '@/stores/motorStore'

export default {
  name: 'DirectionButton',
  components: {
  },
  //  props: {
  //   direction: {
  //     type: String,
  //     required: true
  //   }
  // },    
  data() {
    return {
      // titulo: 'Componente MotorBlock',
      // contador: 5,
      // extra: 3,
      motorStore: useMotorStore(),
      clockwise: false,
      counterClockwise: false,
    }
  },
    methods: {
    seleccionarDirreccion(id) {
      if (id === 'clockwise') {
        if(!this.clockwise){
          this.clockwise= true
          this.counterClockwise= false
          this.motorStore.setDirection('1')
        }
      } else {
          this.clockwise= false
          this.counterClockwise= true
        this.motorStore.setDirection('0')


      }
    },
  },  


}
</script>

<style scoped>
.botones {
  display: flex;
}



    .direccion {
      padding: 10px 20px;
      margin: 5px;
      border: 2px solid #333;
      border-radius: 8px;
      background-color: white;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
    }

    .direccion:disabled {
      background-color: #ccc;
      cursor: not-allowed;
      opacity: 0.6;
    }

    svg {
      width: 24px;
      height: 24px;
    }

    .invertida {
      transform: scaleX(-1); /* Invierte horizontalmente la flecha */
    }

            button {
            background-color: #4CAF50;
            color: white;
            padding: 12px 24px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s;
        }
        button:hover {
            background-color: #45a049;
        }
        button:disabled {
            background-color: #cccccc;
            cursor: not-allowed;
        }
        .boton-seleccionado{
          background-color: green!important;
        }

</style>