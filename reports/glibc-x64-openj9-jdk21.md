---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 05:04:14 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1793178057 74
1793178062 74
1793178067 74
1793178072 74
1793178077 81
1793178082 81
1793178087 81
1793178092 81
1793178097 76
1793178102 76
1793178107 74
1793178112 74
1793178117 74
1793178122 74
1793178127 74
1793178132 74
1793178137 74
1793178142 74
1793178147 74
1793178152 74
```
</details>

---

