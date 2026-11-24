---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 31-57 cores)</summary>

```
1795538327 32
1795538332 32
1795538337 32
1795538342 32
1795538347 32
1795538352 32
1795538357 31
1795538362 31
1795538367 31
1795538372 31
1795538377 31
1795538382 31
1795538387 31
1795538392 31
1795538397 57
1795538402 57
1795538407 57
1795538412 57
1795538417 57
1795538422 55
```
</details>

---

