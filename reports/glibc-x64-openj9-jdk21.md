---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 11:42:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (6 unique values: 68-79 cores)</summary>

```
1795538317 79
1795538322 79
1795538327 79
1795538332 79
1795538337 79
1795538342 79
1795538347 77
1795538352 77
1795538357 77
1795538362 77
1795538367 70
1795538372 70
1795538377 72
1795538382 72
1795538387 72
1795538392 74
1795538397 74
1795538402 74
1795538407 74
1795538412 68
```
</details>

---

