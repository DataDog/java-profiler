---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 33-64 cores)</summary>

```
1795424529 49
1795424534 49
1795424539 49
1795424544 49
1795424549 49
1795424554 49
1795424559 49
1795424564 49
1795424569 64
1795424574 64
1795424579 64
1795424584 33
1795424589 33
1795424594 33
1795424599 33
1795424604 33
1795424609 33
1795424614 33
1795424619 33
1795424624 33
```
</details>

---

