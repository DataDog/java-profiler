---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 06:47:20 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794310987 32
1794310992 32
1794310997 32
1794311002 32
1794311007 32
1794311012 32
1794311017 32
1794311022 32
1794311027 32
1794311032 32
1794311037 32
1794311042 32
1794311047 32
1794311052 32
1794311057 32
1794311062 32
1794311067 32
1794311072 32
1794311077 32
1794311082 32
```
</details>

---

