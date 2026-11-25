---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (3 unique values: 27-44 cores)</summary>

```
1795618562 27
1795618567 27
1795618572 27
1795618577 27
1795618582 27
1795618587 27
1795618592 27
1795618597 44
1795618602 44
1795618607 28
1795618612 28
1795618617 28
1795618622 28
1795618627 28
1795618632 28
1795618637 28
1795618642 28
1795618647 28
1795618652 28
1795618657 28
```
</details>

---

