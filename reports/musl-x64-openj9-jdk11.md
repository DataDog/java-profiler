---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794850058 27
1794850063 27
1794850068 27
1794850073 27
1794850078 27
1794850083 27
1794850088 27
1794850093 27
1794850098 27
1794850103 27
1794850108 27
1794850113 27
1794850118 29
1794850123 29
1794850128 27
1794850133 27
1794850138 27
1794850143 27
1794850148 27
1794850153 27
```
</details>

---

