---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 05:51:51 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1787132875 64
1787132880 64
1787132885 64
1787132890 64
1787132895 64
1787132900 64
1787132905 64
1787132910 64
1787132915 64
1787132920 64
1787132925 60
1787132930 60
1787132935 60
1787132940 60
1787132945 60
1787132950 60
1787132955 60
1787132960 60
1787132965 60
1787132970 60
```
</details>

---

