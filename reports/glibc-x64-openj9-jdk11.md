---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:12:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 31-41 cores)</summary>

```
1777558069 31
1777558074 31
1777558079 31
1777558084 31
1777558089 36
1777558094 36
1777558099 41
1777558104 41
1777558109 41
1777558114 41
1777558119 41
1777558124 41
1777558129 41
1777558134 41
1777558139 41
1777558144 41
1777558149 41
1777558154 41
1777558159 41
1777558164 41
```
</details>

---

