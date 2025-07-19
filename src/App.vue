<script setup>
import HelloWorld from './components/HelloWorld.vue'
import TheWelcome from './components/TheWelcome.vue'
import MotorBlock from './components/MotorBlock.vue'
import MotorBlockBase from './components/MotorBlockBase.vue'
import MotorBlockHombro from './components/MotorBlockHombro.vue'
import MotorBlockCodo from './components/MotorBlockCodo.vue'
import MoveIndividually from './components/MoveIndividually.vue'
</script>

<template>
  <header>
    <h1>Enviar al esp32 </h1>
    <h3>motor-direccion-angulo-microstepping</h3>
  </header>

  <main>
    <MoveIndividually  />
    <button> Enviar </button>
  </main>
</template>

<style scoped>
h1 {
    color: #333;
    text-align: center;
}
header {
  line-height: 1.5;
  /* border: 2px solid red; */
  width: 100%;
  display: flex;
    justify-content: center;
  flex-direction: column;
  align-items: center;
  margin-bottom: 1rem;
}

.addMotorMovement{
  /* border: 2px solid red; */
  display: flex;
  justify-content: center;
  width: 100%;

}

.addMotorMovement button{
width: 10%;
height: 30px;
}

main {
  display: flex;
  justify-content: center;
  flex-direction: column;
  align-items: center;
  width: 100%;
}

</style>
