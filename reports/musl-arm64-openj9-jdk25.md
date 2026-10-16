---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 06:16:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 12 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1792145508 42
1792145513 44
1792145518 44
1792145523 44
1792145528 44
1792145533 44
1792145538 44
1792145543 44
1792145548 44
1792145553 44
1792145558 44
1792145563 44
1792145568 44
1792145573 44
1792145578 44
1792145583 44
1792145588 44
1792145593 44
1792145599 44
1792145604 44
```
</details>

---

