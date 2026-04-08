---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-08 13:30:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1775668982 29
1775668987 29
1775668992 27
1775668997 27
1775669002 27
1775669007 27
1775669012 25
1775669017 25
1775669022 27
1775669027 27
1775669032 27
1775669037 27
1775669042 27
1775669047 27
1775669052 27
1775669057 27
1775669062 27
1775669067 27
1775669072 27
1775669077 27
```
</details>

---

