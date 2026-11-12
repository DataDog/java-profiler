---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:01:55 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 88-92 cores)</summary>

```
1794480898 90
1794480903 90
1794480908 90
1794480913 88
1794480918 88
1794480923 88
1794480928 88
1794480933 88
1794480938 88
1794480943 88
1794480948 88
1794480953 92
1794480958 92
1794480963 92
1794480968 90
1794480973 90
1794480978 90
1794480983 90
1794480988 90
1794480993 90
```
</details>

---

