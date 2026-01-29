---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 07:49:59 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 23.33/sec |
| Health Score | 1458% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 28.77/sec |
| Health Score | 1798% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1769690638 88
1769690643 88
1769690648 88
1769690653 88
1769690658 88
1769690663 88
1769690668 88
1769690673 88
1769690678 92
1769690683 92
1769690688 92
1769690693 92
1769690698 92
1769690703 94
1769690708 94
1769690713 94
1769690718 94
1769690723 94
1769690728 94
1769690733 96
```
</details>

---

