---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 07:43:43 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 11 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (2 unique values: 81-93 cores)</summary>

```
1792496352 81
1792496357 81
1792496362 81
1792496367 81
1792496372 81
1792496377 81
1792496382 81
1792496387 81
1792496392 81
1792496397 81
1792496402 81
1792496407 81
1792496412 81
1792496417 81
1792496422 81
1792496427 81
1792496432 81
1792496437 93
1792496442 93
1792496447 93
```
</details>

---

