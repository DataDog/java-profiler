---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 7-15 cores)</summary>

```
1791891526 15
1791891531 15
1791891536 15
1791891541 15
1791891546 15
1791891551 7
1791891556 7
1791891561 7
1791891567 7
1791891572 7
1791891577 7
1791891582 7
1791891587 7
1791891592 7
1791891597 7
1791891602 7
1791891607 7
1791891612 7
1791891617 7
1791891622 7
```
</details>

---

