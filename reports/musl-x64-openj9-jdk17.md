---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 04:02:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 79-88 cores)</summary>

```
1778572532 88
1778572537 88
1778572542 88
1778572547 88
1778572552 88
1778572557 88
1778572562 88
1778572567 88
1778572572 88
1778572577 88
1778572582 88
1778572587 88
1778572592 88
1778572597 79
1778572602 79
1778572607 83
1778572613 83
1778572618 83
1778572623 83
1778572628 83
```
</details>

---

