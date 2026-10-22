---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792676352 91
1792676357 91
1792676362 89
1792676367 89
1792676372 89
1792676377 89
1792676382 89
1792676387 89
1792676392 89
1792676397 91
1792676402 91
1792676407 91
1792676412 91
1792676417 89
1792676422 89
1792676427 89
1792676432 89
1792676437 89
1792676442 89
1792676447 89
```
</details>

---

