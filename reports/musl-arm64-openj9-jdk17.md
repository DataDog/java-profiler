---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 12:42:26 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1792773555 53
1792773560 64
1792773565 64
1792773570 64
1792773575 64
1792773580 48
1792773585 48
1792773590 48
1792773595 48
1792773600 48
1792773605 48
1792773610 48
1792773615 43
1792773620 43
1792773625 43
1792773630 43
1792773635 43
1792773640 43
1792773645 43
1792773650 43
```
</details>

---

