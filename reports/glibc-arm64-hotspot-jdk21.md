---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:33:58 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 10 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 14 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (3 unique values: 36-43 cores)</summary>

```
1789673360 36
1789673365 36
1789673370 36
1789673375 38
1789673380 38
1789673385 38
1789673390 38
1789673395 38
1789673400 43
1789673405 43
1789673410 43
1789673415 43
1789673420 43
1789673425 43
1789673430 43
1789673435 43
1789673440 38
1789673445 38
1789673450 38
1789673455 38
```
</details>

---

