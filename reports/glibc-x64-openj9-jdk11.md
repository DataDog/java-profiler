---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:00:50 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1096 |
| Sample Rate | 18.27/sec |
| Health Score | 1142% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1786388237 89
1786388242 89
1786388247 89
1786388252 89
1786388257 89
1786388262 89
1786388267 89
1786388272 89
1786388277 89
1786388282 91
1786388287 91
1786388292 91
1786388297 91
1786388303 91
1786388308 91
1786388313 91
1786388318 91
1786388323 91
1786388328 91
1786388333 91
```
</details>

---

