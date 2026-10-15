---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 11:57:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792079283 32
1792079288 32
1792079293 32
1792079298 32
1792079303 32
1792079308 32
1792079313 32
1792079318 32
1792079323 32
1792079328 32
1792079333 32
1792079338 32
1792079343 32
1792079348 32
1792079353 32
1792079358 32
1792079363 32
1792079368 32
1792079373 32
1792079378 32
```
</details>

---

