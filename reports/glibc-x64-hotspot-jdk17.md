---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-20 05:49:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 88-93 cores)</summary>

```
1779270401 93
1779270406 93
1779270411 93
1779270416 93
1779270421 88
1779270426 88
1779270431 88
1779270436 88
1779270441 88
1779270446 88
1779270451 88
1779270456 88
1779270461 88
1779270466 88
1779270471 88
1779270476 88
1779270481 88
1779270486 88
1779270491 88
1779270496 88
```
</details>

---

