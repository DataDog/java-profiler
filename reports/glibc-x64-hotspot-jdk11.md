---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:59:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 955 |
| Sample Rate | 15.92/sec |
| Health Score | 995% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 43-55 cores)</summary>

```
1791546607 43
1791546612 43
1791546617 43
1791546622 43
1791546627 43
1791546632 43
1791546637 43
1791546642 43
1791546647 43
1791546652 51
1791546657 51
1791546662 55
1791546667 55
1791546673 55
1791546678 55
1791546683 55
1791546688 55
1791546693 55
1791546698 55
1791546703 55
```
</details>

---

