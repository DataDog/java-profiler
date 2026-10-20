---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 06:11:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 17-27 cores)</summary>

```
1792490654 24
1792490659 24
1792490664 24
1792490669 24
1792490674 24
1792490679 24
1792490684 24
1792490689 24
1792490694 24
1792490699 24
1792490704 24
1792490709 27
1792490714 27
1792490720 19
1792490725 19
1792490730 19
1792490735 19
1792490740 19
1792490745 19
1792490750 17
```
</details>

---

