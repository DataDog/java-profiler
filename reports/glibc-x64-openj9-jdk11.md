---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:25:29 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 48-50 cores)</summary>

```
1795706445 48
1795706450 48
1795706455 48
1795706460 48
1795706465 48
1795706470 48
1795706475 48
1795706480 48
1795706485 48
1795706490 48
1795706495 48
1795706500 48
1795706505 48
1795706510 48
1795706515 50
1795706520 50
1795706525 48
1795706530 48
1795706535 48
1795706540 48
```
</details>

---

