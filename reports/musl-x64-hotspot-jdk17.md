---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 15:02:26 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 15-31 cores)</summary>

```
1790621743 15
1790621748 15
1790621753 15
1790621758 17
1790621763 17
1790621768 17
1790621773 17
1790621778 17
1790621783 17
1790621788 19
1790621793 19
1790621798 19
1790621803 19
1790621808 31
1790621813 31
1790621818 31
1790621823 31
1790621828 31
1790621833 31
1790621838 31
```
</details>

---

