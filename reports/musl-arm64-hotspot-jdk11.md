---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 15:47:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 28-38 cores)</summary>

```
1795034442 28
1795034447 28
1795034452 28
1795034457 28
1795034462 28
1795034467 28
1795034472 28
1795034477 28
1795034482 28
1795034487 33
1795034492 33
1795034497 33
1795034502 33
1795034507 33
1795034512 33
1795034517 33
1795034522 33
1795034527 38
1795034532 38
1795034537 38
```
</details>

---

