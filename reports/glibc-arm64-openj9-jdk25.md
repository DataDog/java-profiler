---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:44:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 10 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795426832 49
1795426837 49
1795426842 49
1795426847 49
1795426852 44
1795426857 44
1795426862 44
1795426867 44
1795426872 44
1795426877 44
1795426882 44
1795426887 44
1795426892 49
1795426897 49
1795426902 49
1795426907 49
1795426912 49
1795426917 49
1795426922 49
1795426927 49
```
</details>

---

