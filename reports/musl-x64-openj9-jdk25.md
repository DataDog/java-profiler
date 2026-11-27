---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:39:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 54-58 cores)</summary>

```
1795793648 56
1795793653 56
1795793658 56
1795793663 56
1795793668 56
1795793673 56
1795793678 56
1795793683 56
1795793688 56
1795793693 56
1795793698 56
1795793703 54
1795793708 54
1795793713 54
1795793718 56
1795793723 56
1795793728 56
1795793733 56
1795793738 56
1795793743 56
```
</details>

---

