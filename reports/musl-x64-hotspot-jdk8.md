---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 70-90 cores)</summary>

```
1794360740 79
1794360745 79
1794360750 73
1794360755 73
1794360760 73
1794360765 73
1794360770 73
1794360775 70
1794360780 70
1794360785 70
1794360790 70
1794360795 70
1794360800 70
1794360805 70
1794360810 70
1794360815 70
1794360820 70
1794360825 70
1794360830 70
1794360835 70
```
</details>

---

