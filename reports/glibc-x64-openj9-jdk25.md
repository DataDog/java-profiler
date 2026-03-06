---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 11 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 50-58 cores)</summary>

```
1772790209 52
1772790214 52
1772790219 52
1772790224 52
1772790229 50
1772790234 50
1772790239 50
1772790244 50
1772790249 50
1772790254 50
1772790259 50
1772790264 50
1772790269 50
1772790274 50
1772790279 50
1772790284 50
1772790289 50
1772790294 50
1772790299 50
1772790304 50
```
</details>

---

