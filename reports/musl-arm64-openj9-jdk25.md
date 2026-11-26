---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:26:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702899 64
1795702904 64
1795702909 64
1795702914 64
1795702919 64
1795702924 64
1795702929 64
1795702934 64
1795702939 64
1795702944 64
1795702949 64
1795702954 64
1795702959 64
1795702964 64
1795702969 64
1795702974 64
1795702979 64
1795702984 64
1795702989 64
1795702995 64
```
</details>

---

