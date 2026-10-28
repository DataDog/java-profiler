---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:01:16 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 58-61 cores)</summary>

```
1793184664 58
1793184669 58
1793184674 58
1793184679 58
1793184684 58
1793184689 58
1793184694 58
1793184699 58
1793184704 58
1793184709 58
1793184714 58
1793184719 58
1793184724 58
1793184729 58
1793184734 58
1793184739 60
1793184744 60
1793184749 61
1793184754 61
1793184759 61
```
</details>

---

