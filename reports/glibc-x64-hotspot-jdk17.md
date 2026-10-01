---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 00:59:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1790830471 47
1790830476 47
1790830481 47
1790830486 47
1790830491 47
1790830496 47
1790830501 51
1790830506 51
1790830511 51
1790830516 51
1790830521 51
1790830526 51
1790830531 51
1790830536 51
1790830541 51
1790830546 51
1790830551 51
1790830556 51
1790830561 51
1790830566 51
```
</details>

---

