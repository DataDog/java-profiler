---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 14:58:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1776192789 51
1776192794 51
1776192799 51
1776192804 51
1776192809 56
1776192814 56
1776192819 56
1776192824 56
1776192829 56
1776192834 56
1776192839 56
1776192844 56
1776192849 56
1776192854 56
1776192859 56
1776192864 56
1776192869 56
1776192874 56
1776192879 56
1776192884 56
```
</details>

---

