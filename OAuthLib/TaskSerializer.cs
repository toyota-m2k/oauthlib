using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OAuthLib
{
    public class TaskSerializer<T>
    {
        Dictionary<string, TaskCompletionSource<T>> mMap;

        public TaskSerializer()
        {
            mMap = new Dictionary<string, TaskCompletionSource<T>>();
        }

        public delegate Task<T> Runnable();

        public async Task<T> Execute(string key, Runnable action)
        {
            for (; ; )
            {
                TaskCompletionSource<T> task = null;
                bool waiting = false;
                lock (mMap)
                {
                    waiting = mMap.TryGetValue(key, out task);
                    if (task == null)
                    {
                        task = new TaskCompletionSource<T>();
                        mMap.Add(key, task);
                    }
                }

                if (waiting)
                {
                    return await task.Task;
                }
                else
                {
                    try
                    {
                        var r = await action();
                        lock (mMap)
                        {
                            task.TrySetResult(r);
                            mMap.Remove(key);
                        }
                        return r;
                    }
                    catch (Exception e)
                    {
                        task.TrySetException(e);
                        throw e;
                    }
                }
            }
        }
    }
}
