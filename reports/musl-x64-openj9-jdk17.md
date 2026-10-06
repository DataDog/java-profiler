---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 08:29:12 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 68-88 cores)</summary>

```
1791289463 68
1791289468 68
1791289473 68
1791289478 88
1791289483 88
1791289489 88
1791289494 88
1791289499 88
1791289504 88
1791289509 88
1791289514 88
1791289519 88
1791289524 88
1791289529 88
1791289534 88
1791289539 88
1791289544 88
1791289549 88
1791289554 88
1791289559 88
```
</details>

---

