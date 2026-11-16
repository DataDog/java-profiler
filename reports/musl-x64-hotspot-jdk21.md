---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 19:49:10 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794789888 81
1794789893 81
1794789898 81
1794789903 81
1794789908 81
1794789913 81
1794789918 81
1794789923 81
1794789928 79
1794789933 79
1794789938 79
1794789943 79
1794789948 79
1794789953 79
1794789958 79
1794789963 79
1794789968 79
1794789973 79
1794789978 79
1794789983 79
```
</details>

---

