---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769514145 32
1769514150 30
1769514155 30
1769514160 30
1769514165 30
1769514170 30
1769514175 30
1769514180 32
1769514185 32
1769514190 32
1769514195 32
1769514200 32
1769514205 32
1769514210 32
1769514215 32
1769514220 32
1769514225 32
1769514230 32
1769514235 32
1769514240 32
```
</details>

---

