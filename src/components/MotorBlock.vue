


<template>
  <div >
      <div class="direction-buttons">
        <DirectionButton/>
        <AngleSteppingTrasmission/>
        </div>
        {{ clockwise }}
        {{ counterClockwise }}
  </div>
</template>

<script>
import DirectionButton from './DirectionButton.vue'
import AngleSteppingTrasmission from './AngleSteppingTrasmission.vue'
export default {
  name: 'MotorBlock',
  components: {
    DirectionButton,
    AngleSteppingTrasmission
  },
    data() {
    return {
      // titulo: 'Componente MotorBlock',
      // contador: 5,
      // extra: 3
      // clockwise: false,
      // counterClockwise: false,
    }
  },
  methods: {
    // seleccionarDirreccion(id) {
    //   if (id === 'clockwise') {
    //     if(!this.clockwise){
    //       this.clockwise= true
    //       this.counterClockwise= false
    //     }
    //   } else {
    //     this.counterClockwise= !this.counterClockwise
    //     this.clockwise= !this.clockwise


    //   }
    // },
    // sumar(a, b) {
    //   return a + b;
    // }
  },  


}
</script>

<style scoped>
h1 {
  font-weight: 500;
  font-size: 2.6rem;
  position: relative;
  top: -10px;
}

h3 {
  font-size: 1.2rem;
}

.greetings h1,
.greetings h3 {
  text-align: center;
}

@media (min-width: 1024px) {
  .greetings h1,
  .greetings h3 {
    text-align: left;
  }
}

    .botones-direccion{
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
        .direction-buttons{
          display: flex;
          justify-content: center;
          align-items: center;
          border: 2px solid red;
          flex-direction: column;
        }
</style>