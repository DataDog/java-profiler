---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 12:37:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 76-82 cores)</summary>

```
1794850063 82
1794850068 82
1794850073 80
1794850078 80
1794850083 80
1794850088 80
1794850093 82
1794850098 82
1794850103 82
1794850108 82
1794850113 78
1794850118 78
1794850123 78
1794850128 76
1794850133 76
1794850138 76
1794850143 76
1794850148 76
1794850153 76
1794850158 76
```
</details>

---

