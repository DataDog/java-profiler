---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 21:48:05 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (6 unique values: 40-57 cores)</summary>

```
1777427038 57
1777427043 57
1777427048 57
1777427053 57
1777427058 57
1777427063 57
1777427068 57
1777427073 40
1777427078 40
1777427083 47
1777427088 47
1777427093 42
1777427098 42
1777427103 42
1777427108 42
1777427113 44
1777427118 44
1777427123 44
1777427128 44
1777427133 44
```
</details>

---

