---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 11:29:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 14 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1795537529 50
1795537534 55
1795537539 55
1795537544 55
1795537549 55
1795537554 55
1795537559 55
1795537564 55
1795537569 55
1795537574 55
1795537579 55
1795537584 55
1795537589 55
1795537594 55
1795537599 55
1795537604 60
1795537609 60
1795537614 60
1795537619 60
1795537624 60
```
</details>

---

