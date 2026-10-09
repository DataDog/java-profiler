---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:28:09 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791530698 32
1791530704 32
1791530709 32
1791530714 27
1791530719 27
1791530724 27
1791530729 27
1791530734 27
1791530739 27
1791530744 27
1791530749 27
1791530754 27
1791530759 27
1791530764 27
1791530769 27
1791530774 27
1791530779 27
1791530784 27
1791530789 27
1791530794 27
```
</details>

---

