---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:01:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 39-43 cores)</summary>

```
1793184732 41
1793184737 41
1793184742 41
1793184747 39
1793184752 39
1793184757 41
1793184762 41
1793184767 41
1793184772 41
1793184777 41
1793184782 41
1793184787 41
1793184792 41
1793184797 41
1793184802 41
1793184807 41
1793184812 43
1793184817 43
1793184822 43
1793184827 43
```
</details>

---

