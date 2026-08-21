---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 19:10:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1787353537 76
1787353542 76
1787353547 76
1787353552 76
1787353557 76
1787353562 76
1787353567 76
1787353572 96
1787353577 96
1787353582 96
1787353587 96
1787353592 96
1787353597 96
1787353602 96
1787353607 96
1787353613 96
1787353618 96
1787353623 96
1787353628 96
1787353633 96
```
</details>

---

