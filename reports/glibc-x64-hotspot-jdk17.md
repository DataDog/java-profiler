---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

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
| CPU Samples | 386 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 8 |
| Allocations | 308 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 20.70/sec |
| Health Score | 1294% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769526918 30
1769526923 32
1769526928 32
1769526933 30
1769526938 30
1769526943 30
1769526948 32
1769526953 32
1769526958 32
1769526963 32
1769526968 32
1769526973 32
1769526978 32
1769526983 32
1769526988 32
1769526993 32
1769526998 32
1769527003 32
1769527008 32
1769527013 32
```
</details>

---

