---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 09:59:31 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 12 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 972 |
| Sample Rate | 16.20/sec |
| Health Score | 1012% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (6 unique values: 83-96 cores)</summary>

```
1770130537 85
1770130542 85
1770130547 83
1770130552 83
1770130557 87
1770130562 87
1770130567 87
1770130572 87
1770130577 87
1770130582 89
1770130587 89
1770130592 89
1770130597 89
1770130602 89
1770130607 92
1770130612 92
1770130617 96
1770130622 96
1770130627 96
1770130632 96
```
</details>

---

