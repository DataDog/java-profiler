---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 07:09:47 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 889 |
| Sample Rate | 14.82/sec |
| Health Score | 926% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (6 unique values: 55-75 cores)</summary>

```
1778151778 73
1778151783 73
1778151788 70
1778151793 70
1778151798 75
1778151803 75
1778151808 75
1778151813 55
1778151818 55
1778151823 55
1778151828 55
1778151833 55
1778151838 57
1778151843 57
1778151848 64
1778151853 64
1778151858 64
1778151863 64
1778151868 64
1778151873 64
```
</details>

---

