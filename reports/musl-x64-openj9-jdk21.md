---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-31 00:55:02 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 66-76 cores)</summary>

```
1788151851 74
1788151856 74
1788151861 74
1788151866 74
1788151871 76
1788151876 76
1788151881 76
1788151886 76
1788151891 76
1788151896 76
1788151901 76
1788151906 76
1788151911 76
1788151916 76
1788151921 76
1788151926 76
1788151931 66
1788151936 66
1788151941 66
1788151946 66
```
</details>

---

