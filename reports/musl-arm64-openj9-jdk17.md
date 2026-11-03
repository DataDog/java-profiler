---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 59 |
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
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1793734721 46
1793734726 46
1793734731 41
1793734736 41
1793734742 41
1793734747 41
1793734752 41
1793734757 41
1793734762 41
1793734767 41
1793734772 54
1793734777 54
1793734782 54
1793734787 54
1793734792 54
1793734797 59
1793734802 59
1793734807 59
1793734812 59
1793734817 59
```
</details>

---

