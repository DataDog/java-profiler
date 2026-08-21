---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 05:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 12 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1787305662 9
1787305667 9
1787305672 9
1787305677 9
1787305682 14
1787305687 14
1787305693 14
1787305698 14
1787305703 14
1787305708 14
1787305713 14
1787305718 14
1787305723 14
1787305728 14
1787305733 14
1787305738 14
1787305743 14
1787305748 14
1787305753 14
1787305758 14
```
</details>

---

