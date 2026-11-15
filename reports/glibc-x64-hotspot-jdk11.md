---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 21:04:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 41-63 cores)</summary>

```
1794708081 63
1794708086 43
1794708091 43
1794708096 43
1794708101 43
1794708106 43
1794708111 43
1794708116 41
1794708121 41
1794708126 41
1794708131 41
1794708136 41
1794708141 41
1794708146 41
1794708151 41
1794708156 41
1794708161 41
1794708166 41
1794708171 41
1794708176 41
```
</details>

---

