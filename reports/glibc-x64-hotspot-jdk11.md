---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:34:13 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1794580076 89
1794580081 89
1794580086 89
1794580091 89
1794580096 89
1794580101 89
1794580106 89
1794580111 89
1794580116 89
1794580121 89
1794580126 89
1794580131 89
1794580136 89
1794580141 89
1794580146 91
1794580151 91
1794580156 91
1794580161 91
1794580166 91
1794580171 91
```
</details>

---

