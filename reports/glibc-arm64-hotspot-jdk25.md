---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1790956748 48
1790956753 48
1790956758 48
1790956763 48
1790956768 48
1790956773 48
1790956778 48
1790956783 48
1790956788 48
1790956793 48
1790956798 48
1790956803 48
1790956808 48
1790956813 48
1790956818 48
1790956823 48
1790956828 48
1790956833 48
1790956838 47
1790956843 47
```
</details>

---

