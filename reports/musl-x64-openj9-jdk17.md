---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 08:20:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (5 unique values: 39-63 cores)</summary>

```
1770124556 41
1770124561 41
1770124566 41
1770124571 41
1770124576 41
1770124581 41
1770124586 41
1770124591 41
1770124596 41
1770124601 41
1770124606 41
1770124611 39
1770124616 39
1770124621 39
1770124626 39
1770124631 44
1770124636 44
1770124641 44
1770124646 44
1770124651 46
```
</details>

---

