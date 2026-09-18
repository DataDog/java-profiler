---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 05:01:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789721778 30
1789721783 30
1789721788 30
1789721793 30
1789721798 30
1789721803 30
1789721808 30
1789721813 30
1789721818 30
1789721823 30
1789721828 30
1789721833 30
1789721838 30
1789721843 30
1789721848 30
1789721853 30
1789721858 30
1789721863 30
1789721868 30
1789721873 30
```
</details>

---

