---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:14:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 62-73 cores)</summary>

```
1795003828 62
1795003833 62
1795003838 62
1795003843 62
1795003848 62
1795003853 62
1795003858 62
1795003863 62
1795003868 62
1795003873 68
1795003878 68
1795003883 68
1795003888 68
1795003893 65
1795003898 65
1795003903 73
1795003908 73
1795003913 73
1795003918 71
1795003923 71
```
</details>

---

