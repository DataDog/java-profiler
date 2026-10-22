---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 16 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792676370 46
1792676375 46
1792676380 46
1792676385 46
1792676390 46
1792676395 46
1792676400 46
1792676405 46
1792676410 46
1792676415 51
1792676420 51
1792676425 51
1792676430 51
1792676435 51
1792676440 51
1792676445 51
1792676450 51
1792676455 51
1792676460 51
1792676465 51
```
</details>

---

