---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:14:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 12 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1793185543 51
1793185548 51
1793185553 51
1793185558 51
1793185563 39
1793185568 39
1793185573 39
1793185578 39
1793185583 39
1793185588 39
1793185593 39
1793185598 39
1793185603 39
1793185608 39
1793185613 39
1793185618 39
1793185623 39
1793185628 39
1793185633 39
1793185638 39
```
</details>

---

