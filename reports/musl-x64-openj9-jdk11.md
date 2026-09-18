---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 43-81 cores)</summary>

```
1789731816 81
1789731821 81
1789731826 81
1789731831 81
1789731836 45
1789731841 45
1789731846 45
1789731851 45
1789731856 45
1789731861 45
1789731866 43
1789731871 43
1789731876 43
1789731881 43
1789731886 43
1789731891 43
1789731896 45
1789731901 45
1789731906 45
1789731911 45
```
</details>

---

