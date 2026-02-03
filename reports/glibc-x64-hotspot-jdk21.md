---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:20:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 8 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1770124347 11
1770124352 11
1770124357 11
1770124362 11
1770124367 11
1770124372 32
1770124377 32
1770124382 32
1770124387 32
1770124392 32
1770124397 32
1770124402 32
1770124407 32
1770124412 32
1770124417 32
1770124422 32
1770124427 32
1770124432 32
1770124437 32
1770124442 32
```
</details>

---

