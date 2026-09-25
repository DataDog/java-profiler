---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 74-86 cores)</summary>

```
1790346474 76
1790346479 76
1790346484 76
1790346489 76
1790346494 74
1790346499 74
1790346504 74
1790346509 74
1790346514 74
1790346519 74
1790346524 76
1790346529 76
1790346534 76
1790346539 76
1790346544 76
1790346549 78
1790346554 78
1790346559 78
1790346564 78
1790346569 86
```
</details>

---

