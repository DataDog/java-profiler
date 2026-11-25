---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:20:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795641445 64
1795641450 64
1795641455 64
1795641460 64
1795641465 64
1795641470 64
1795641475 64
1795641480 64
1795641485 64
1795641490 64
1795641495 64
1795641500 64
1795641505 64
1795641510 64
1795641515 64
1795641520 64
1795641525 45
1795641530 45
1795641535 45
1795641540 45
```
</details>

---

