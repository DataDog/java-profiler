---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 17:32:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 39-77 cores)</summary>

```
1777325180 39
1777325185 39
1777325190 53
1777325195 53
1777325200 53
1777325205 53
1777325210 53
1777325215 53
1777325220 57
1777325225 57
1777325230 77
1777325235 77
1777325240 77
1777325245 77
1777325250 77
1777325255 77
1777325260 77
1777325265 77
1777325270 77
1777325275 77
```
</details>

---

