---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 08:59:58 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (4 unique values: 69-76 cores)</summary>

```
1786020999 69
1786021004 69
1786021009 69
1786021014 69
1786021019 72
1786021024 72
1786021029 74
1786021034 74
1786021039 76
1786021044 76
1786021049 76
1786021054 76
1786021059 76
1786021064 76
1786021069 76
1786021074 76
1786021079 76
1786021084 76
1786021089 76
1786021094 76
```
</details>

---

