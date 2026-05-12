---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 04:02:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 73-77 cores)</summary>

```
1778572527 73
1778572532 73
1778572537 73
1778572542 73
1778572547 73
1778572552 73
1778572557 73
1778572562 73
1778572567 73
1778572572 73
1778572577 73
1778572582 73
1778572587 73
1778572592 73
1778572597 77
1778572602 77
1778572607 77
1778572612 77
1778572617 77
1778572622 77
```
</details>

---

