---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:25:29 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 25-36 cores)</summary>

```
1795706363 36
1795706368 36
1795706373 36
1795706378 36
1795706383 36
1795706388 36
1795706393 36
1795706398 36
1795706403 36
1795706408 36
1795706413 36
1795706418 36
1795706423 36
1795706428 36
1795706433 36
1795706438 36
1795706443 36
1795706448 36
1795706453 36
1795706458 36
```
</details>

---

