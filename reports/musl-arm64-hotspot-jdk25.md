---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 09:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 12 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 16 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790257795 43
1790257800 43
1790257805 43
1790257810 43
1790257815 43
1790257820 43
1790257825 43
1790257830 43
1790257835 43
1790257840 43
1790257845 43
1790257850 43
1790257855 43
1790257860 43
1790257865 43
1790257870 43
1790257875 43
1790257880 43
1790257886 48
1790257891 48
```
</details>

---

