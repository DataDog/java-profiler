---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 427 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 24.47/sec |
| Health Score | 1529% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769514150 30
1769514155 30
1769514160 30
1769514165 30
1769514170 30
1769514175 30
1769514180 30
1769514185 30
1769514190 30
1769514195 30
1769514200 32
1769514205 32
1769514210 32
1769514215 32
1769514220 32
1769514225 32
1769514230 32
1769514235 32
1769514240 32
1769514245 32
```
</details>

---

