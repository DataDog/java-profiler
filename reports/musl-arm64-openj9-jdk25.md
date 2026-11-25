---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:39:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795606494 47
1795606499 47
1795606504 47
1795606509 47
1795606514 47
1795606519 47
1795606524 47
1795606529 47
1795606534 47
1795606539 47
1795606544 47
1795606549 47
1795606554 47
1795606559 47
1795606564 47
1795606569 47
1795606574 47
1795606579 47
1795606584 47
1795606590 47
```
</details>

---

