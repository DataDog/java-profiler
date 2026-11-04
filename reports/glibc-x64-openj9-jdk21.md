---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:45 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1793800150 79
1793800155 79
1793800160 79
1793800165 79
1793800170 79
1793800175 79
1793800180 79
1793800185 79
1793800190 79
1793800195 79
1793800200 81
1793800205 81
1793800210 81
1793800215 81
1793800220 81
1793800225 81
1793800230 79
1793800235 79
1793800240 79
1793800245 79
```
</details>

---

