---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:39:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 59-87 cores)</summary>

```
1795196077 87
1795196082 87
1795196087 87
1795196092 87
1795196097 87
1795196102 87
1795196107 87
1795196112 87
1795196117 87
1795196122 87
1795196127 87
1795196132 87
1795196137 87
1795196142 87
1795196147 59
1795196152 59
1795196157 59
1795196162 59
1795196167 59
1795196172 59
```
</details>

---

