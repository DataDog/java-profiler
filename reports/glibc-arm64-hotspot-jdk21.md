---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:22:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 12 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 14 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794842316 51
1794842321 51
1794842326 51
1794842331 51
1794842336 51
1794842341 51
1794842346 51
1794842351 51
1794842356 51
1794842361 51
1794842366 51
1794842371 51
1794842376 46
1794842381 46
1794842386 41
1794842391 41
1794842396 41
1794842401 41
1794842406 41
1794842411 41
```
</details>

---

