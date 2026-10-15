---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 09:27:40 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 13-30 cores)</summary>

```
1792070537 13
1792070542 13
1792070547 13
1792070552 13
1792070557 13
1792070562 13
1792070567 13
1792070572 13
1792070577 13
1792070582 13
1792070587 13
1792070592 30
1792070597 30
1792070602 14
1792070607 14
1792070612 14
1792070617 14
1792070622 14
1792070627 14
1792070632 14
```
</details>

---

