---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 15:17:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 12 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1790795554 90
1790795559 90
1790795564 90
1790795569 90
1790795574 90
1790795579 90
1790795584 90
1790795589 93
1790795594 93
1790795599 93
1790795604 93
1790795609 93
1790795614 93
1790795619 93
1790795624 93
1790795629 93
1790795634 93
1790795639 93
1790795644 93
1790795649 93
```
</details>

---

