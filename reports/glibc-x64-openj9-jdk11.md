---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:54:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1793800136 65
1793800141 65
1793800146 65
1793800151 65
1793800156 65
1793800161 65
1793800166 65
1793800171 65
1793800176 65
1793800181 65
1793800186 65
1793800191 65
1793800196 65
1793800201 67
1793800206 67
1793800211 67
1793800216 67
1793800221 67
1793800226 67
1793800231 67
```
</details>

---

