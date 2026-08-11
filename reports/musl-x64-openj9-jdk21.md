---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 05:49:19 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786441469 27
1786441474 27
1786441479 32
1786441484 32
1786441489 32
1786441494 32
1786441499 32
1786441504 32
1786441509 32
1786441514 32
1786441519 32
1786441524 32
1786441529 32
1786441534 32
1786441539 32
1786441544 32
1786441549 32
1786441554 32
1786441559 32
1786441564 32
```
</details>

---

