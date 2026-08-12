---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 08:46:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 74-83 cores)</summary>

```
1786538572 79
1786538577 79
1786538582 79
1786538587 79
1786538592 79
1786538597 79
1786538602 74
1786538607 74
1786538612 74
1786538617 76
1786538622 76
1786538627 76
1786538632 76
1786538637 78
1786538642 78
1786538647 78
1786538652 78
1786538657 78
1786538662 78
1786538667 78
```
</details>

---

