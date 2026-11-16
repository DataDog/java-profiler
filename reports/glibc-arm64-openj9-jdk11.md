---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:52:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 10 |
| Allocations | 210 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794836841 48
1794836846 48
1794836851 48
1794836856 48
1794836861 48
1794836866 48
1794836871 48
1794836876 48
1794836881 48
1794836886 48
1794836891 48
1794836896 48
1794836901 48
1794836906 48
1794836911 48
1794836916 48
1794836921 48
1794836926 48
1794836931 48
1794836936 48
```
</details>

---

