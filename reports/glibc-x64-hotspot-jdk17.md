---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (2 unique values: 76-79 cores)</summary>

```
1794945018 79
1794945023 79
1794945028 79
1794945033 79
1794945038 79
1794945043 79
1794945048 79
1794945053 76
1794945058 76
1794945063 76
1794945068 76
1794945073 76
1794945078 76
1794945083 76
1794945088 76
1794945093 76
1794945098 76
1794945103 76
1794945108 76
1794945113 76
```
</details>

---

