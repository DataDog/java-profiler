---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:20:51 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795641359 70
1795641364 70
1795641369 70
1795641374 72
1795641379 72
1795641384 72
1795641389 72
1795641394 72
1795641399 72
1795641404 72
1795641409 72
1795641414 72
1795641419 72
1795641424 72
1795641429 72
1795641434 72
1795641439 72
1795641444 72
1795641449 72
1795641454 72
```
</details>

---

