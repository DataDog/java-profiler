---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-13 07:08:42 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 12 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (5 unique values: 43-69 cores)</summary>

```
1773399853 43
1773399858 43
1773399863 43
1773399868 43
1773399873 56
1773399878 56
1773399883 56
1773399888 60
1773399893 60
1773399898 60
1773399903 60
1773399908 60
1773399913 60
1773399918 60
1773399923 60
1773399928 69
1773399933 69
1773399938 69
1773399943 69
1773399948 69
```
</details>

---

