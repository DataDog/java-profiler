---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 11:44:37 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 85-92 cores)</summary>

```
1794847084 85
1794847089 87
1794847094 87
1794847099 90
1794847104 90
1794847109 90
1794847114 90
1794847119 90
1794847124 90
1794847129 90
1794847134 92
1794847139 92
1794847144 92
1794847149 90
1794847154 90
1794847159 90
1794847164 90
1794847169 90
1794847174 90
1794847179 90
```
</details>

---

