---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 10:37:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786977216 44
1786977221 44
1786977226 44
1786977231 44
1786977236 44
1786977241 44
1786977246 44
1786977251 48
1786977256 48
1786977261 48
1786977266 48
1786977271 43
1786977276 43
1786977281 43
1786977286 43
1786977291 43
1786977296 43
1786977301 43
1786977306 43
1786977311 43
```
</details>

---

