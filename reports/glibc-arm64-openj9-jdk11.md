---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:37:25 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 14-14 cores)</summary>

```
1794850098 14
1794850103 14
1794850108 14
1794850113 14
1794850118 14
1794850123 14
1794850128 14
1794850133 14
1794850138 14
1794850143 14
1794850148 14
1794850153 14
1794850158 14
1794850163 14
1794850168 14
1794850173 14
1794850178 14
1794850183 14
1794850188 14
1794850193 14
```
</details>

---

