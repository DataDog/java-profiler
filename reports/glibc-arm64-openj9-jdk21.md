---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 17-29 cores)</summary>

```
1795380703 22
1795380708 22
1795380713 22
1795380718 22
1795380723 22
1795380729 17
1795380734 17
1795380739 17
1795380744 17
1795380749 17
1795380754 17
1795380759 17
1795380764 17
1795380769 29
1795380774 29
1795380779 29
1795380784 29
1795380789 29
1795380794 29
1795380799 29
```
</details>

---

