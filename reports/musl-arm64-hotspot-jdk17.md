---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 15:47:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 26-52 cores)</summary>

```
1795034437 26
1795034442 26
1795034447 26
1795034452 26
1795034457 26
1795034462 26
1795034467 39
1795034472 39
1795034477 39
1795034482 39
1795034487 39
1795034492 39
1795034497 39
1795034502 39
1795034507 39
1795034512 39
1795034517 39
1795034522 39
1795034527 52
1795034532 52
```
</details>

---

