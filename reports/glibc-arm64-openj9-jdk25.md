---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 04:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 10 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 27-64 cores)</summary>

```
1790325698 64
1790325703 64
1790325708 64
1790325713 64
1790325718 64
1790325723 64
1790325729 64
1790325734 64
1790325739 64
1790325744 64
1790325749 27
1790325754 27
1790325759 27
1790325764 27
1790325769 27
1790325774 27
1790325779 27
1790325784 27
1790325789 27
1790325794 27
```
</details>

---

