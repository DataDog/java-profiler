---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 37-47 cores)</summary>

```
1793647499 45
1793647504 45
1793647509 45
1793647514 45
1793647519 45
1793647524 45
1793647529 45
1793647534 45
1793647539 45
1793647544 45
1793647549 45
1793647554 45
1793647559 44
1793647564 44
1793647569 44
1793647574 47
1793647579 47
1793647584 40
1793647589 40
1793647594 38
```
</details>

---

