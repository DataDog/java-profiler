---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 18:51:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1788475511 59
1788475516 59
1788475521 59
1788475526 59
1788475531 61
1788475536 61
1788475541 61
1788475546 61
1788475551 61
1788475556 61
1788475561 61
1788475566 61
1788475571 61
1788475576 61
1788475581 61
1788475586 61
1788475591 59
1788475596 59
1788475601 59
1788475606 59
```
</details>

---

