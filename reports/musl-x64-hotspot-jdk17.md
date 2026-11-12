---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 68-85 cores)</summary>

```
1794495893 85
1794495898 85
1794495903 85
1794495908 85
1794495913 85
1794495918 85
1794495923 85
1794495928 85
1794495933 85
1794495938 85
1794495943 85
1794495948 85
1794495953 85
1794495958 85
1794495963 68
1794495968 68
1794495973 68
1794495978 68
1794495983 68
1794495988 68
```
</details>

---

