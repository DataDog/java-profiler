---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 20:36:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 15 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1794360720 46
1794360725 46
1794360730 46
1794360735 46
1794360740 46
1794360745 46
1794360750 46
1794360755 46
1794360760 46
1794360765 46
1794360770 49
1794360775 49
1794360780 49
1794360785 49
1794360790 49
1794360795 49
1794360800 49
1794360805 49
1794360810 51
1794360815 51
```
</details>

---

