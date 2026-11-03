---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:00:44 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1793721196 89
1793721201 91
1793721206 91
1793721211 89
1793721216 89
1793721221 89
1793721226 89
1793721231 89
1793721236 89
1793721241 89
1793721246 89
1793721251 89
1793721256 89
1793721261 87
1793721266 87
1793721271 89
1793721276 89
1793721281 89
1793721286 91
1793721291 91
```
</details>

---

