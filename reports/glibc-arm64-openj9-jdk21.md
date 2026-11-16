---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:25:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (5 unique values: 34-43 cores)</summary>

```
1794831633 34
1794831638 39
1794831643 39
1794831648 38
1794831653 38
1794831658 38
1794831663 38
1794831668 38
1794831673 38
1794831678 38
1794831683 38
1794831688 40
1794831693 40
1794831699 40
1794831704 40
1794831709 43
1794831714 43
1794831719 38
1794831724 38
1794831729 38
```
</details>

---

