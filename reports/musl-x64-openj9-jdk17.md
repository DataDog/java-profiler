---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:35:22 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 55-70 cores)</summary>

```
1794832262 70
1794832268 70
1794832273 70
1794832278 70
1794832283 62
1794832288 62
1794832293 62
1794832298 57
1794832303 57
1794832308 57
1794832313 57
1794832318 57
1794832323 57
1794832328 57
1794832333 57
1794832338 57
1794832343 57
1794832348 55
1794832353 55
1794832358 55
```
</details>

---

