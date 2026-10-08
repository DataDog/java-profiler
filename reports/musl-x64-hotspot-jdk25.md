---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:47:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 75 |
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
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 55-88 cores)</summary>

```
1791466897 55
1791466902 55
1791466907 55
1791466912 55
1791466917 55
1791466922 55
1791466927 55
1791466932 88
1791466937 88
1791466942 88
1791466947 88
1791466952 88
1791466957 88
1791466962 67
1791466967 67
1791466972 75
1791466977 75
1791466982 75
1791466987 75
1791466992 75
```
</details>

---

