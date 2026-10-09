---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 01:05:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1791522018 81
1791522023 79
1791522028 79
1791522033 79
1791522039 79
1791522044 79
1791522049 79
1791522054 79
1791522059 79
1791522064 81
1791522069 81
1791522074 81
1791522079 81
1791522084 81
1791522089 81
1791522094 81
1791522099 79
1791522104 79
1791522109 79
1791522114 79
```
</details>

---

