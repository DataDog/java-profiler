---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:56:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 88-91 cores)</summary>

```
1794325898 88
1794325903 88
1794325908 88
1794325913 88
1794325918 88
1794325923 88
1794325928 88
1794325933 90
1794325938 90
1794325943 90
1794325948 90
1794325953 90
1794325958 90
1794325963 90
1794325968 90
1794325973 91
1794325978 91
1794325983 91
1794325988 91
1794325993 91
```
</details>

---

