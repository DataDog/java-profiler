---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-05 05:23:31 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 12 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 39-42 cores)</summary>

```
1770286705 42
1770286710 42
1770286715 42
1770286720 42
1770286725 42
1770286730 42
1770286735 42
1770286740 42
1770286745 39
1770286750 39
1770286755 39
1770286760 39
1770286765 39
1770286770 39
1770286775 39
1770286780 39
1770286785 39
1770286790 39
1770286795 39
1770286800 39
```
</details>

---

