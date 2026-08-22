---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 08:14:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 62-66 cores)</summary>

```
1787400607 62
1787400612 62
1787400617 62
1787400622 62
1787400627 62
1787400632 62
1787400637 62
1787400642 66
1787400647 66
1787400652 66
1787400657 66
1787400662 66
1787400667 66
1787400672 66
1787400677 66
1787400682 66
1787400687 66
1787400692 66
1787400697 66
1787400702 66
```
</details>

---

