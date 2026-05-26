---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-26 09:56:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1067 |
| Sample Rate | 17.78/sec |
| Health Score | 1111% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 44-52 cores)</summary>

```
1779803423 52
1779803428 52
1779803433 52
1779803438 52
1779803443 52
1779803448 46
1779803453 46
1779803458 46
1779803463 46
1779803468 46
1779803473 46
1779803478 46
1779803483 46
1779803488 46
1779803493 46
1779803498 46
1779803503 46
1779803508 46
1779803513 46
1779803518 46
```
</details>

---

