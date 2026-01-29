---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 25.30/sec |
| Health Score | 1581% |
| Threads | 11 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 25.83/sec |
| Health Score | 1614% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 47-73 cores)</summary>

```
1769697754 47
1769697759 47
1769697764 47
1769697769 47
1769697774 47
1769697779 47
1769697784 73
1769697789 73
1769697794 73
1769697799 73
1769697804 73
1769697809 73
1769697814 73
1769697819 73
1769697824 73
1769697829 73
1769697834 73
1769697839 73
1769697844 73
1769697849 73
```
</details>

---

