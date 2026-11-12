---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:40:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 10 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 65-86 cores)</summary>

```
1794504898 65
1794504903 65
1794504908 65
1794504913 65
1794504918 65
1794504923 65
1794504928 65
1794504933 86
1794504938 86
1794504943 86
1794504948 78
1794504953 78
1794504958 78
1794504963 78
1794504968 78
1794504973 78
1794504978 83
1794504983 83
1794504988 83
1794504993 83
```
</details>

---

