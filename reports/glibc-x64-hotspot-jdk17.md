---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-28 21:48:05 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 62-74 cores)</summary>

```
1777427043 74
1777427048 62
1777427053 62
1777427058 62
1777427063 62
1777427068 62
1777427073 62
1777427078 62
1777427083 62
1777427088 62
1777427093 64
1777427098 64
1777427103 64
1777427108 64
1777427113 64
1777427118 64
1777427123 64
1777427128 64
1777427133 64
1777427138 64
```
</details>

---

