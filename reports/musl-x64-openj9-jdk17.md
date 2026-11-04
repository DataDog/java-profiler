---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793830717 59
1793830722 59
1793830727 59
1793830732 59
1793830737 59
1793830742 59
1793830747 59
1793830752 61
1793830757 61
1793830762 61
1793830767 61
1793830772 61
1793830778 61
1793830783 61
1793830788 61
1793830793 61
1793830798 61
1793830803 61
1793830808 61
1793830813 61
```
</details>

---

