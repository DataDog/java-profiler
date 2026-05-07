---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:54:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 78-86 cores)</summary>

```
1778165315 78
1778165320 78
1778165325 78
1778165330 78
1778165335 78
1778165340 78
1778165345 78
1778165350 78
1778165355 78
1778165360 81
1778165365 81
1778165371 81
1778165376 81
1778165381 85
1778165386 85
1778165391 85
1778165396 86
1778165401 86
1778165406 86
1778165411 86
```
</details>

---

