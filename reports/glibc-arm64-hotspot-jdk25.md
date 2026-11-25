---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:50:53 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 10 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 14 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795628812 33
1795628817 33
1795628822 33
1795628827 33
1795628832 33
1795628837 33
1795628842 33
1795628847 33
1795628852 33
1795628857 33
1795628862 33
1795628867 33
1795628872 33
1795628877 33
1795628882 33
1795628887 33
1795628892 33
1795628897 33
1795628902 33
1795628907 28
```
</details>

---

