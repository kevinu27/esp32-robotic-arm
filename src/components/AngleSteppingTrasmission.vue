


<template>
  <div class="form">
    <h2>grados:</h2>
    <input type="number" id="degrees" v-model="degrees" />
    <h2>Microstepping:</h2>
       <select id="steps" v-model="stepping">
      <option disabled value="">Selecciona un color</option>
      <option value="200">200</option>
      <option value="400">400</option>
      <option value="800">800</option>
      <option value="1600">1600</option>
      <option value="3200">3200</option>
      <option value="6400">6400</option>
    </select>
  </div>
</template>

<script>

export default {
  name: 'AngleSteppingTrasmission',
  components: {
  },
 
  data() {
    return {
      degrees: 0,
      stepping: 200,
    }
  },
    methods: {
    seleccionarDirreccion(id) {
      if (id === 'clockwise') {
        if(!this.clockwise){
          this.clockwise= true
          this.counterClockwise= false
        }
      } else {
        this.counterClockwise= !this.counterClockwise
        this.clockwise= !this.clockwise


      }
    },
  },  


}
</script>

<style scoped>
 .form{
  display: flex;
  flex-direction: column;
  margin-bottom: 2rem;
 }

</style>