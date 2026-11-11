---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:02:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 74-96 cores)</summary>

```
1794427049 74
1794427054 74
1794427059 74
1794427064 74
1794427069 96
1794427074 96
1794427079 96
1794427084 96
1794427089 96
1794427094 96
1794427099 96
1794427104 96
1794427109 96
1794427114 96
1794427119 96
1794427124 96
1794427129 96
1794427134 96
1794427139 96
1794427144 96
```
</details>

---

