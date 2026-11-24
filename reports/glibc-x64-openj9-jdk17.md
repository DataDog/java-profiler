---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 00:03:32 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 22-43 cores)</summary>

```
1795496334 41
1795496339 41
1795496344 41
1795496349 41
1795496354 43
1795496359 43
1795496364 43
1795496369 43
1795496374 22
1795496379 22
1795496384 22
1795496389 22
1795496394 22
1795496399 22
1795496404 22
1795496409 22
1795496414 22
1795496419 22
1795496424 22
1795496429 22
```
</details>

---

