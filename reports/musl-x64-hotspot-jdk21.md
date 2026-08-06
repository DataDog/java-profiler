---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 84-87 cores)</summary>

```
1786018975 87
1786018980 87
1786018985 85
1786018990 85
1786018995 87
1786019000 87
1786019005 87
1786019010 87
1786019015 87
1786019020 87
1786019025 87
1786019030 86
1786019035 86
1786019040 84
1786019045 84
1786019050 84
1786019055 84
1786019060 84
1786019065 84
1786019070 84
```
</details>

---

