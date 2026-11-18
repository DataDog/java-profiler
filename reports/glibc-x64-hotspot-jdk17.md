---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:33:06 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 38-47 cores)</summary>

```
1795011970 38
1795011975 38
1795011980 47
1795011985 47
1795011990 47
1795011995 47
1795012000 47
1795012005 47
1795012010 47
1795012015 47
1795012020 47
1795012025 47
1795012030 47
1795012035 47
1795012040 47
1795012045 47
1795012050 47
1795012055 47
1795012060 47
1795012065 47
```
</details>

---

