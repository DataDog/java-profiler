---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 06:07:57 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 9 |
| Allocations | 114 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 40-43 cores)</summary>

```
1794827038 40
1794827043 40
1794827048 40
1794827053 40
1794827058 40
1794827063 40
1794827068 40
1794827073 40
1794827078 40
1794827083 40
1794827088 40
1794827093 40
1794827098 43
1794827103 43
1794827108 43
1794827113 43
1794827118 40
1794827123 40
1794827128 40
1794827133 40
```
</details>

---

