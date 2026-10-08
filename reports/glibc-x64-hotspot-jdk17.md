---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791470928 30
1791470933 30
1791470938 30
1791470943 30
1791470948 30
1791470953 30
1791470958 30
1791470963 30
1791470968 30
1791470973 30
1791470978 30
1791470983 30
1791470988 32
1791470993 32
1791470998 32
1791471003 32
1791471008 32
1791471013 32
1791471018 32
1791471023 32
```
</details>

---

