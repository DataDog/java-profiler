---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:16:17 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 84-94 cores)</summary>

```
1795691233 84
1795691238 84
1795691243 84
1795691248 84
1795691253 84
1795691258 84
1795691263 84
1795691268 92
1795691273 92
1795691278 94
1795691283 94
1795691289 94
1795691294 94
1795691299 94
1795691304 94
1795691309 94
1795691314 94
1795691319 89
1795691324 89
1795691329 89
```
</details>

---

