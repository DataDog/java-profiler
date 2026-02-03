---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 06:18:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1770117199 23
1770117204 23
1770117209 23
1770117214 23
1770117219 23
1770117224 23
1770117229 23
1770117234 23
1770117239 23
1770117244 21
1770117249 21
1770117254 30
1770117259 30
1770117264 30
1770117269 30
1770117274 30
1770117279 30
1770117284 30
1770117289 30
1770117294 32
```
</details>

---

