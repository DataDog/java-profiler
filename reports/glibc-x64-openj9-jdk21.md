---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 08:51:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1787230043 96
1787230048 96
1787230053 96
1787230058 96
1787230063 96
1787230069 96
1787230074 93
1787230079 93
1787230084 93
1787230089 93
1787230094 93
1787230099 93
1787230104 93
1787230109 93
1787230114 93
1787230119 93
1787230124 93
1787230129 93
1787230134 93
1787230139 93
```
</details>

---

