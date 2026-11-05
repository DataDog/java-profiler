---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 09:56:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 37-56 cores)</summary>

```
1793890187 41
1793890192 41
1793890197 41
1793890202 43
1793890207 43
1793890212 37
1793890217 37
1793890222 37
1793890227 37
1793890232 37
1793890237 39
1793890242 39
1793890247 39
1793890252 39
1793890257 39
1793890262 39
1793890267 56
1793890272 56
1793890277 56
1793890282 56
```
</details>

---

