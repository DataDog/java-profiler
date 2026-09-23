---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 16:42:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 65-88 cores)</summary>

```
1790195845 88
1790195850 65
1790195855 65
1790195860 73
1790195865 73
1790195870 73
1790195875 73
1790195880 73
1790195885 73
1790195890 73
1790195895 73
1790195900 73
1790195905 73
1790195910 73
1790195915 73
1790195920 73
1790195925 73
1790195930 73
1790195935 73
1790195940 73
```
</details>

---

