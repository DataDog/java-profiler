---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 09:56:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
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
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1793890193 51
1793890198 51
1793890203 51
1793890208 51
1793890213 51
1793890218 51
1793890223 51
1793890228 51
1793890233 49
1793890238 49
1793890243 47
1793890248 47
1793890253 49
1793890258 49
1793890263 49
1793890268 49
1793890273 49
1793890278 49
1793890283 51
1793890288 51
```
</details>

---

