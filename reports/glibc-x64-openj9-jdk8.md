---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 0 |

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

