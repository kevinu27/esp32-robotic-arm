import { defineStore } from 'pinia'

export const useMotorStore = defineStore('motor', {
  state: () => ({
    motorBaseString: '',
    motorHombroString:'',
    motorCodoString:'',
    StringTotal: ''
  }),
 

  actions: {
    setMotorBaseString(str) {
      this.motorBaseString = str
      console.log('this.motorBaseString', this.motorBaseString)
    },
    setMotorHombroString(str) {
      this.motorHombroString = str
      console.log('this.motorHombroString', this.motorHombroString)
    },
    setMotorCodoString(str) {
      this.motorCodoString = str
      console.log('this.motorCodoString', this.motorCodoString)
    },
    async enviarString() {
      const ipAddress = '192.168.1.128'
      this.StringTotal = this.motorBaseString + '/' +  this.motorHombroString + '/' +  this.motorCodoString
      console.log('StringTotal/////', this.StringTotal)

      try {
            const url = `http://${ipAddress}/sendData`;
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: `data=${encodeURIComponent(this.StringTotal)}`
            });
            
            const result = await response.json();
            
            if (response.ok && result.status === 'success') {
                console.log(`
                    <strong>Success!</strong><br>
                    Message: ${result.message}<br>
                    First two characters: "${result.firstTwo}"<br>
                    Rest of string: "${result.rest}"
                `, 'success');
            } else {
                 console.log(`<strong>Error:</strong> ${result.message}`, 'error');
            }
            
        } catch (error) {
            console.error('Error:', error);
             console.log(`<strong>Connection Error:</strong> Could not connect to ESP32. 
                        Please check:<br>
                        • ESP32 IP address is correct<br>
                        • ESP32 is connected to WiFi<br>
                        • You're on the same network`, 'error');
        } finally {
          console.log('finally')
        }
    }
  }
})