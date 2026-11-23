---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:39:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (6 unique values: 64-82 cores)</summary>

```
1795451604 64
1795451609 64
1795451614 72
1795451619 72
1795451624 72
1795451629 80
1795451634 80
1795451639 80
1795451644 80
1795451649 80
1795451654 80
1795451659 80
1795451664 80
1795451669 82
1795451674 82
1795451679 82
1795451684 82
1795451689 82
1795451694 65
1795451699 65
```
</details>

---

