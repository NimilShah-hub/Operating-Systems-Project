class  P_C
{
    public static void main(String[] args)
    {
        Produce_consume_thread t=new  Produce_consume_thread();
        new Producer(t);
        new Consumer(t);
    }
}