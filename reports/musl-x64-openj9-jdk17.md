---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 13:48:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793382226 64
1793382231 64
1793382236 64
1793382241 64
1793382246 64
1793382251 64
1793382256 64
1793382261 64
1793382266 62
1793382271 62
1793382276 62
1793382281 62
1793382286 62
1793382291 62
1793382296 62
1793382301 62
1793382306 62
1793382311 62
1793382316 62
1793382321 62
```
</details>

---

