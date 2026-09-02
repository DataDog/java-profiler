---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 00:58:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788324855 92
1788324860 94
1788324865 94
1788324870 94
1788324875 94
1788324880 92
1788324885 92
1788324890 92
1788324895 92
1788324900 92
1788324905 92
1788324910 94
1788324915 94
1788324920 96
1788324925 96
1788324930 96
1788324935 96
1788324940 96
1788324945 96
1788324950 96
```
</details>

---

