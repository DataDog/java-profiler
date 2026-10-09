---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 03:28:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1791530634 10
1791530639 10
1791530644 10
1791530649 30
1791530654 30
1791530659 32
1791530664 32
1791530669 32
1791530674 32
1791530679 32
1791530684 32
1791530689 32
1791530694 32
1791530699 32
1791530704 32
1791530709 32
1791530714 32
1791530719 32
1791530724 32
1791530729 32
```
</details>

---

