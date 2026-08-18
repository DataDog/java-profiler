---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 08:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1787055562 49
1787055567 49
1787055572 49
1787055577 49
1787055582 49
1787055587 49
1787055592 49
1787055597 51
1787055602 51
1787055607 47
1787055612 47
1787055617 47
1787055622 47
1787055627 47
1787055632 47
1787055637 49
1787055642 49
1787055647 51
1787055652 51
1787055657 49
```
</details>

---

