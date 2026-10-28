---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 13:11:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1793207236 35
1793207241 35
1793207246 35
1793207251 35
1793207256 35
1793207261 35
1793207266 35
1793207271 35
1793207276 35
1793207281 35
1793207286 35
1793207291 35
1793207296 35
1793207301 35
1793207306 35
1793207311 35
1793207316 35
1793207321 48
1793207326 48
1793207331 48
```
</details>

---

