---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:33:54 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 52-58 cores)</summary>

```
1794508056 56
1794508061 54
1794508066 54
1794508071 54
1794508076 54
1794508081 52
1794508086 52
1794508091 52
1794508096 52
1794508101 52
1794508106 52
1794508111 54
1794508116 54
1794508121 54
1794508126 56
1794508131 56
1794508136 58
1794508141 58
1794508146 58
1794508151 55
```
</details>

---

