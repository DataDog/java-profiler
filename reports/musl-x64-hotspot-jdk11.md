---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:12:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 8 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 66-70 cores)</summary>

```
1770134673 66
1770134678 66
1770134683 70
1770134688 70
1770134693 70
1770134698 70
1770134703 70
1770134708 70
1770134713 70
1770134718 70
1770134723 70
1770134728 70
1770134733 70
1770134738 70
1770134743 70
1770134748 70
1770134753 70
1770134758 70
1770134763 70
1770134768 70
```
</details>

---

