---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:47:04 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 9-27 cores)</summary>

```
1789731742 9
1789731747 9
1789731752 9
1789731757 9
1789731762 9
1789731767 9
1789731772 27
1789731778 27
1789731783 27
1789731788 27
1789731793 27
1789731798 27
1789731803 27
1789731808 27
1789731813 27
1789731818 27
1789731823 27
1789731828 27
1789731833 27
1789731838 27
```
</details>

---

