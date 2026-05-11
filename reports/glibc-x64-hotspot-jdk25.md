---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 12:20:42 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 75-82 cores)</summary>

```
1778516145 80
1778516150 80
1778516155 80
1778516160 75
1778516165 75
1778516170 75
1778516175 75
1778516180 75
1778516185 77
1778516190 77
1778516195 77
1778516200 82
1778516205 82
1778516210 82
1778516215 82
1778516220 82
1778516225 82
1778516230 78
1778516235 78
1778516240 78
```
</details>

---

