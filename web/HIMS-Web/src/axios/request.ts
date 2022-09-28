// request.ts
import axios from 'axios';
import type { AxiosInstance, AxiosRequestConfig, AxiosResponse } from 'axios';

// 自定义请求返回数据的类型
interface HData<T> {
  data: T;
  returnCode: string;
  success: boolean;
}

class HRequest {
  config: AxiosRequestConfig;
  instance: AxiosInstance;

  constructor(options: AxiosRequestConfig ) {
    this.config = options;
    this.instance = axios.create(options);
  }

  // 类型参数的作用，T决定AxiosResponse实例中data的类型
  request<T = any>(config: AxiosRequestConfig ): Promise<T> {
    return new Promise((resolve, reject) => {
      this.instance
        .request<any, HData<T>>(config)
        .then((res) => {
          resolve(res.data);
        })
        .catch((err) => {
          reject(err);
        });
    });
  }

  get<T = any>(config: AxiosRequestConfig ): Promise<T> {
    return this.request({ ...config, method: 'GET' });
  }

  post<T = any>(config: AxiosRequestConfig ): Promise<T> {
    return this.request({ ...config, method: 'POST' });
  }

  delete<T = any>(config: AxiosRequestConfig ): Promise<T> {
    return this.request({ ...config, method: 'DELETE' });
  }

  patch<T = any>(config: AxiosRequestConfig ): Promise<T> {
    return this.request({ ...config, method: 'PATCH' });
  }
}

export default HRequest