---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 18:21:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 10 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 10 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1786745800 36
1786745805 36
1786745810 36
1786745815 36
1786745820 36
1786745825 36
1786745830 36
1786745835 36
1786745840 36
1786745845 36
1786745850 36
1786745855 36
1786745860 36
1786745865 36
1786745870 36
1786745875 36
1786745880 36
1786745885 36
1786745890 36
1786745895 32
```
</details>

---

