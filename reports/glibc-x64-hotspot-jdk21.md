---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-08 13:30:10 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (5 unique values: 51-79 cores)</summary>

```
1775668958 79
1775668963 79
1775668968 79
1775668973 79
1775668978 79
1775668983 79
1775668988 79
1775668993 79
1775668998 79
1775669003 79
1775669008 70
1775669013 70
1775669018 61
1775669023 61
1775669028 61
1775669033 61
1775669038 61
1775669043 61
1775669048 56
1775669053 56
```
</details>

---

