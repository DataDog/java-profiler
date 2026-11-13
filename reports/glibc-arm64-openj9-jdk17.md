---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794584441 48
1794584446 48
1794584451 48
1794584456 48
1794584461 48
1794584466 48
1794584471 48
1794584476 48
1794584481 48
1794584486 48
1794584491 48
1794584496 48
1794584501 48
1794584506 48
1794584511 48
1794584516 48
1794584521 48
1794584526 48
1794584531 48
1794584536 48
```
</details>

---

