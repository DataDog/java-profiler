---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:59:16 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (3 unique values: 46-59 cores)</summary>

```
1795532018 59
1795532023 59
1795532028 59
1795532033 59
1795532038 59
1795532043 59
1795532048 59
1795532053 59
1795532058 59
1795532063 59
1795532068 59
1795532073 59
1795532078 59
1795532083 59
1795532088 59
1795532093 54
1795532098 54
1795532103 54
1795532108 54
1795532113 54
```
</details>

---

