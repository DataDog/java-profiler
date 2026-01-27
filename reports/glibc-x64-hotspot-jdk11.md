---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 459 |
| Sample Rate | 15.30/sec |
| Health Score | 956% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 22.43/sec |
| Health Score | 1402% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
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
1769514245 32
1769514250 32
```
</details>

---

