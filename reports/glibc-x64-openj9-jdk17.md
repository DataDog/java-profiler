---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 89-92 cores)</summary>

```
1773165008 89
1773165013 89
1773165018 89
1773165023 89
1773165028 92
1773165033 92
1773165038 92
1773165043 92
1773165048 92
1773165053 92
1773165058 92
1773165063 92
1773165068 92
1773165073 92
1773165078 92
1773165083 92
1773165088 92
1773165093 92
1773165098 92
1773165103 92
```
</details>

---

