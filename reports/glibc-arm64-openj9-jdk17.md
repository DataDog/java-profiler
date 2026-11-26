---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:52:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795693673 47
1795693678 47
1795693683 47
1795693688 47
1795693693 47
1795693698 47
1795693703 47
1795693708 47
1795693713 47
1795693719 47
1795693724 47
1795693729 47
1795693734 47
1795693739 47
1795693744 47
1795693749 47
1795693754 47
1795693759 42
1795693764 42
1795693769 42
```
</details>

---

