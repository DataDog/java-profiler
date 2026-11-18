---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:52:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 65-81 cores)</summary>

```
1795013150 68
1795013155 68
1795013160 68
1795013165 68
1795013170 68
1795013175 68
1795013180 68
1795013185 68
1795013190 68
1795013195 68
1795013200 68
1795013205 68
1795013210 65
1795013215 65
1795013220 65
1795013225 65
1795013230 65
1795013235 65
1795013240 65
1795013245 65
```
</details>

---

