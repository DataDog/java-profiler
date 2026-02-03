---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:47:06 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 12 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 56-65 cores)</summary>

```
1770129751 60
1770129756 60
1770129761 65
1770129766 65
1770129771 56
1770129776 56
1770129781 56
1770129786 56
1770129791 56
1770129796 56
1770129801 56
1770129806 56
1770129811 56
1770129816 56
1770129821 56
1770129826 56
1770129831 56
1770129836 56
1770129841 56
1770129846 56
```
</details>

---

