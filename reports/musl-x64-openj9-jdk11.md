---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (3 unique values: 61-81 cores)</summary>

```
1793721216 79
1793721221 79
1793721226 79
1793721231 79
1793721236 79
1793721241 79
1793721246 79
1793721251 79
1793721256 79
1793721261 81
1793721266 81
1793721271 61
1793721276 61
1793721281 61
1793721286 61
1793721291 61
1793721296 61
1793721301 61
1793721306 61
1793721311 61
```
</details>

---

