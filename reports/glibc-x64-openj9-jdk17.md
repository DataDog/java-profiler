---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 68-78 cores)</summary>

```
1795192073 68
1795192078 68
1795192083 68
1795192088 78
1795192093 78
1795192098 78
1795192103 78
1795192108 78
1795192113 78
1795192118 73
1795192123 73
1795192128 73
1795192133 73
1795192138 73
1795192143 73
1795192148 70
1795192153 70
1795192158 70
1795192163 70
1795192168 70
```
</details>

---

