class Producer implements Runnable
{
	 Produce_consume_thread t;
    Producer( Produce_consume_thread t)
    {
        this.t=t;
        new Thread(this,"Producer").start();
    }
    public void run()
    {
        int item=0;
        int i = 0;
        while (item<50)
        {
            t.put(i++);
            item++;
        }
    }
}