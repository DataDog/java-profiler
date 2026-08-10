---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 58-68 cores)</summary>

```
1786375993 68
1786375998 68
1786376003 64
1786376008 64
1786376013 62
1786376018 62
1786376023 62
1786376028 62
1786376033 62
1786376038 62
1786376043 62
1786376048 62
1786376053 62
1786376058 58
1786376063 58
1786376068 60
1786376073 60
1786376078 60
1786376084 60
1786376089 60
```
</details>

---

