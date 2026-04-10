---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-10 06:00:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 76-84 cores)</summary>

```
1775814870 76
1775814875 76
1775814880 78
1775814885 78
1775814890 78
1775814895 78
1775814900 78
1775814905 78
1775814910 84
1775814915 84
1775814920 84
1775814925 79
1775814930 79
1775814935 79
1775814940 79
1775814945 79
1775814950 79
1775814955 79
1775814960 79
1775814965 79
```
</details>

---

