---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795001527 62
1795001532 62
1795001537 62
1795001542 62
1795001547 62
1795001552 62
1795001557 62
1795001562 62
1795001567 64
1795001572 64
1795001577 62
1795001582 62
1795001587 62
1795001592 62
1795001597 62
1795001602 62
1795001607 62
1795001612 62
1795001617 62
1795001622 62
```
</details>

---

