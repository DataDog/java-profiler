---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 14:37:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 25-35 cores)</summary>

```
1790361179 27
1790361184 27
1790361189 25
1790361194 25
1790361199 25
1790361204 25
1790361209 35
1790361214 35
1790361219 35
1790361224 35
1790361229 35
1790361234 35
1790361239 35
1790361244 35
1790361249 35
1790361254 35
1790361259 35
1790361264 35
1790361269 35
1790361274 35
```
</details>

---

