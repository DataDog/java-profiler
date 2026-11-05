---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 08:25:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 8 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 12 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793884793 48
1793884798 48
1793884803 48
1793884808 48
1793884813 48
1793884818 48
1793884823 43
1793884828 43
1793884833 43
1793884838 43
1793884843 43
1793884848 43
1793884853 43
1793884858 43
1793884863 43
1793884868 43
1793884873 43
1793884878 43
1793884883 43
1793884888 43
```
</details>

---

