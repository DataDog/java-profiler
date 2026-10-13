---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 77-79 cores)</summary>

```
1791891572 78
1791891577 79
1791891582 79
1791891587 79
1791891592 79
1791891597 77
1791891602 77
1791891607 77
1791891612 77
1791891617 77
1791891622 77
1791891627 77
1791891632 77
1791891637 77
1791891642 77
1791891647 77
1791891652 77
1791891657 77
1791891662 77
1791891667 77
```
</details>

---

