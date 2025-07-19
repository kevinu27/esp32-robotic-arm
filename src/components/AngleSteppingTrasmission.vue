<template>
  <div class="form">
    <h2>Grados:</h2>
    <input type="number" id="degrees" v-model="degrees1" />

    <h2>Microstepping:</h2>
    <select id="steps" v-model="stepping1">
      <option disabled value="">Selecciona un valor</option>
      <option value="200">200</option>
      <option value="400">400</option>
      <option value="800">800</option>
      <option value="1600">1600</option>
      <option value="3200">3200</option>
      <option value="6400">6400</option>
    </select>
  </div>

  <h2 >Valor actual en store:</h2>
  <p>Grados: {{ degrees1 }}</p>
  <p>Stepping: {{ stepping1 }}</p>
</template>

<script>
import { useMotorStore } from '@/stores/motorStore'

export default {
  name: 'AngleSteppingTrasmission',

  data() {
    return {
      motorStore: useMotorStore(),
    }
  },    
  methods: {
    // setDegrees(degrees) {
    //   this.motorStore.setDegrees(degrees)
    // },
  },  

  computed: {
    degrees1: {
      get() {
        return this.motorStore.degrees1;
      },
      set(val) {
        this.motorStore.degrees1 = val;
      }
    },
    stepping1: {
      get() {
        return this.motorStore.stepping1;
      },
      set(val) {
        this.motorStore.stepping1 = val;
      }
    }
  }
}
</script>

<style scoped>
.form {
  display: flex;
  flex-direction: column;
  margin-bottom: 2rem;
}
</style>