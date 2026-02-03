---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 08:20:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (7 unique values: 34-64 cores)</summary>

```
1770124342 35
1770124347 35
1770124352 41
1770124357 41
1770124362 42
1770124367 42
1770124372 42
1770124377 46
1770124382 46
1770124387 46
1770124392 46
1770124397 34
1770124402 34
1770124407 34
1770124412 34
1770124417 34
1770124422 34
1770124427 34
1770124432 34
1770124437 34
```
</details>

---

