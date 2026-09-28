---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:39:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 52-64 cores)</summary>

```
1790602534 52
1790602539 63
1790602544 63
1790602549 63
1790602554 63
1790602559 63
1790602564 63
1790602569 63
1790602574 63
1790602579 63
1790602584 63
1790602589 63
1790602594 63
1790602599 63
1790602604 63
1790602609 61
1790602614 61
1790602619 61
1790602624 61
1790602629 61
```
</details>

---

