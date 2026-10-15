---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 09:57:56 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 22-30 cores)</summary>

```
1792072258 22
1792072263 22
1792072268 22
1792072273 22
1792072278 22
1792072283 22
1792072288 22
1792072293 22
1792072298 24
1792072303 24
1792072308 22
1792072313 22
1792072318 22
1792072323 22
1792072328 22
1792072333 22
1792072338 22
1792072343 22
1792072348 22
1792072353 22
```
</details>

---

