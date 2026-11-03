---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:05:38 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793739668 40
1793739673 40
1793739678 40
1793739683 40
1793739688 40
1793739693 40
1793739698 40
1793739703 40
1793739708 40
1793739713 40
1793739718 40
1793739723 40
1793739728 40
1793739733 40
1793739738 40
1793739743 40
1793739748 40
1793739753 40
1793739758 40
1793739763 40
```
</details>

---

