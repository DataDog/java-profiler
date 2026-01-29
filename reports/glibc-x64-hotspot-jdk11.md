---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 19.60/sec |
| Health Score | 1225% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 26.37/sec |
| Health Score | 1648% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 63-71 cores)</summary>

```
1769697764 71
1769697769 71
1769697774 71
1769697779 66
1769697784 66
1769697789 66
1769697794 66
1769697799 67
1769697804 67
1769697809 67
1769697814 67
1769697819 63
1769697824 63
1769697829 71
1769697834 71
1769697839 71
1769697844 71
1769697849 71
1769697854 71
1769697859 71
```
</details>

---

