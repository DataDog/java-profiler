---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 06:18:33 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 23-32 cores)</summary>

```
1770117214 23
1770117219 23
1770117224 23
1770117229 23
1770117234 23
1770117239 32
1770117244 32
1770117249 30
1770117254 30
1770117259 28
1770117264 28
1770117269 28
1770117274 28
1770117279 30
1770117284 30
1770117289 30
1770117294 30
1770117299 32
1770117304 32
1770117309 32
```
</details>

---

