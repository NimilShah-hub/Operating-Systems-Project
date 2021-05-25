class Consumer implements Runnable
{
	 Produce_consume_thread t;
    Consumer( Produce_consume_thread t)
    {
        this.t=t;
        new Thread(this,"Consumer").start();
    }
    public void run()
    {
        int item=0;
        while (item<50)
        {
            t.get();
            item++;
        }
    }
}