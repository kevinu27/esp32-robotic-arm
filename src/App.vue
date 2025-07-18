<script setup>
import HelloWorld from './components/HelloWorld.vue'
import TheWelcome from './components/TheWelcome.vue'
import MotorBlock from './components/MotorBlock.vue'
</script>

<template>
  <header>
    <h1>ESP32 WiFi Communication</h1>
    <h3>motor-direccion-angulo-microstepping</h3>
  </header>

  <main>
    <MotorBlock />
    
    <div class="addMotorMovement">
      <button> +</button>
    </div>

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
}

.addMotorMovement{
  border: 2px solid red;
  display: flex;
  justify-content: center;
}

.addMotorMovement button{
width: 10%;
height: 30px;
}

</style>
