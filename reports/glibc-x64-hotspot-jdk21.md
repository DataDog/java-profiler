---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1777983466 32
1777983471 32
1777983476 32
1777983481 34
1777983486 34
1777983491 34
1777983496 34
1777983501 34
1777983506 34
1777983511 34
1777983516 34
1777983521 34
1777983526 34
1777983531 34
1777983536 34
1777983541 34
1777983546 34
1777983551 34
1777983556 34
1777983561 34
```
</details>

---

