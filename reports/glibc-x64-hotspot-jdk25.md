---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 09:29:16 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793975097 32
1793975102 32
1793975107 32
1793975112 32
1793975117 32
1793975122 32
1793975127 32
1793975132 32
1793975137 32
1793975142 32
1793975147 32
1793975152 32
1793975157 32
1793975162 32
1793975167 32
1793975172 32
1793975177 32
1793975182 32
1793975187 32
1793975192 32
```
</details>

---

