---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 10:50:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778078674 64
1778078679 64
1778078684 64
1778078689 64
1778078694 64
1778078699 64
1778078704 64
1778078709 64
1778078714 64
1778078719 64
1778078724 64
1778078729 64
1778078734 64
1778078739 64
1778078744 64
1778078749 64
1778078754 64
1778078759 64
1778078764 64
1778078769 64
```
</details>

---

