---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:23:09 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1795605454 63
1795605459 63
1795605464 63
1795605469 63
1795605474 63
1795605479 63
1795605484 63
1795605489 63
1795605494 63
1795605499 63
1795605504 63
1795605509 63
1795605514 63
1795605519 63
1795605524 63
1795605529 63
1795605534 63
1795605539 63
1795605544 63
1795605549 63
```
</details>

---

