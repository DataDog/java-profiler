---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 11:22:31 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1777389449 28
1777389454 28
1777389459 28
1777389464 28
1777389469 28
1777389474 28
1777389479 28
1777389484 28
1777389489 28
1777389494 28
1777389499 27
1777389504 27
1777389509 27
1777389514 27
1777389519 27
1777389524 27
1777389529 27
1777389534 27
1777389539 27
1777389544 28
```
</details>

---

