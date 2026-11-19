---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 18:10:52 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 414 |

<details>
<summary>CPU Timeline (2 unique values: 58-66 cores)</summary>

```
1795129586 66
1795129591 66
1795129596 66
1795129601 66
1795129606 66
1795129611 66
1795129616 66
1795129621 66
1795129626 66
1795129631 58
1795129636 58
1795129641 58
1795129646 58
1795129651 58
1795129656 58
1795129661 58
1795129666 58
1795129671 58
1795129676 58
1795129681 58
```
</details>

---

