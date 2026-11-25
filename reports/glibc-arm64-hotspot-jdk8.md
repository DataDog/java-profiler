---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:00:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 42 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1795618514 47
1795618519 47
1795618524 47
1795618529 42
1795618534 42
1795618539 59
1795618544 59
1795618549 59
1795618554 59
1795618559 59
1795618564 59
1795618569 59
1795618574 59
1795618579 59
1795618584 59
1795618589 59
1795618594 59
1795618599 64
1795618604 64
1795618609 64
```
</details>

---

