---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:35:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795112742 50
1795112747 50
1795112752 50
1795112757 50
1795112762 50
1795112767 50
1795112772 50
1795112777 50
1795112782 50
1795112787 50
1795112793 50
1795112798 50
1795112803 50
1795112808 50
1795112813 50
1795112818 50
1795112823 50
1795112828 50
1795112833 50
1795112838 50
```
</details>

---

