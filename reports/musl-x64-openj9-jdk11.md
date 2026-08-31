---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-31 00:55:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 69-71 cores)</summary>

```
1788151846 71
1788151851 71
1788151856 71
1788151861 71
1788151866 71
1788151871 71
1788151876 71
1788151881 69
1788151886 69
1788151891 69
1788151896 69
1788151901 69
1788151906 69
1788151911 69
1788151916 69
1788151922 69
1788151927 71
1788151932 71
1788151937 69
1788151942 69
```
</details>

---

