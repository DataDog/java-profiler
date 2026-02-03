---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 10 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1770124556 30
1770124561 30
1770124566 28
1770124571 28
1770124576 28
1770124581 28
1770124586 28
1770124591 28
1770124596 28
1770124601 28
1770124606 28
1770124611 28
1770124616 28
1770124621 28
1770124626 28
1770124631 28
1770124636 28
1770124641 28
1770124646 28
1770124651 28
```
</details>

---

