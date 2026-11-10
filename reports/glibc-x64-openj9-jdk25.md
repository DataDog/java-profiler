---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:16 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 87-92 cores)</summary>

```
1794326135 90
1794326140 90
1794326145 90
1794326150 90
1794326155 92
1794326160 92
1794326165 92
1794326170 92
1794326175 92
1794326180 92
1794326185 92
1794326190 92
1794326195 92
1794326200 91
1794326205 91
1794326210 89
1794326215 89
1794326220 89
1794326225 89
1794326230 89
```
</details>

---

