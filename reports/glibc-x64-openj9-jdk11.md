---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 60-71 cores)</summary>

```
1793829479 60
1793829484 60
1793829489 60
1793829494 60
1793829499 60
1793829504 60
1793829509 60
1793829514 71
1793829519 71
1793829524 71
1793829529 71
1793829534 71
1793829539 71
1793829544 71
1793829549 71
1793829554 71
1793829559 71
1793829564 71
1793829569 71
1793829574 71
```
</details>

---

