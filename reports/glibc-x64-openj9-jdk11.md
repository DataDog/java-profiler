---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-10 19:29:54 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 81-86 cores)</summary>

```
1775863481 86
1775863486 86
1775863491 86
1775863496 86
1775863501 86
1775863506 86
1775863511 86
1775863516 86
1775863521 86
1775863526 86
1775863531 81
1775863536 81
1775863541 81
1775863546 81
1775863551 81
1775863556 81
1775863561 81
1775863566 81
1775863571 81
1775863576 81
```
</details>

---

