---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:39:28 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795196122 66
1795196127 66
1795196132 66
1795196137 64
1795196142 64
1795196147 64
1795196152 64
1795196157 64
1795196162 64
1795196167 64
1795196172 64
1795196177 64
1795196182 64
1795196187 64
1795196192 64
1795196197 64
1795196202 64
1795196207 64
1795196212 64
1795196217 64
```
</details>

---

