---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-14 12:04:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 985 |
| Sample Rate | 16.42/sec |
| Health Score | 1026% |
| Threads | 11 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1789401518 94
1789401523 94
1789401528 92
1789401533 92
1789401538 92
1789401543 92
1789401548 90
1789401553 90
1789401559 90
1789401564 88
1789401569 88
1789401574 88
1789401579 88
1789401584 88
1789401589 92
1789401594 92
1789401599 94
1789401604 94
1789401609 94
1789401614 96
```
</details>

---

