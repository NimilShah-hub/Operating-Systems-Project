class Produce_consume_thread
{
    int num;
    boolean flag=false;
    synchronized int get()
    {
        if (!flag)
            try
            {
                wait();
            }
            catch (Exception e)
            {
                System.out.println("Excepton occurs at : "+e);
            }
        System.out.println("Consumed Item:" +num);
        try
        {
            Thread.sleep(1000);
        }
        catch (Exception e)
        {
            System.out.println("Excepton occurs at : "+e);
        }
        flag=false;
        notify();
        return num;
    }
    synchronized int put(int num)
    {
        if (flag)
            try
            {
                wait();
            }
            catch (Exception e)
            {
                System.out.println("Excepton occur at : "+e);
            }
        this.num=num;
        flag=true;
        System.out.println("Produced Item:"+num);
        try
        {
            Thread.sleep(1200);
        }
        catch (Exception e)
        {
            System.out.println("Excepton occur at : "+e);
        }
        notify();
        return num;
    }
}