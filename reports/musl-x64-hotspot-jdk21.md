---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-03 18:51:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788475513 94
1788475518 96
1788475523 96
1788475528 96
1788475533 94
1788475538 94
1788475543 94
1788475548 94
1788475553 94
1788475558 94
1788475563 94
1788475568 94
1788475573 94
1788475578 94
1788475583 96
1788475588 96
1788475593 96
1788475598 96
1788475603 96
1788475608 96
```
</details>

---

