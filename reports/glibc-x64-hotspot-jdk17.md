---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 04:32:38 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 63-66 cores)</summary>

```
1791966570 66
1791966575 66
1791966580 66
1791966585 66
1791966590 66
1791966595 66
1791966600 66
1791966605 66
1791966610 63
1791966615 63
1791966620 63
1791966625 63
1791966630 63
1791966635 63
1791966640 63
1791966645 65
1791966650 65
1791966655 63
1791966660 63
1791966665 63
```
</details>

---

