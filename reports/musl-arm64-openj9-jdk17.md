---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:39:04 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 116 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 42-50 cores)</summary>

```
1795170746 42
1795170752 42
1795170757 42
1795170762 42
1795170767 42
1795170772 42
1795170777 42
1795170782 42
1795170787 42
1795170792 42
1795170797 42
1795170802 42
1795170807 42
1795170812 42
1795170817 42
1795170822 42
1795170827 42
1795170832 42
1795170837 42
1795170842 42
```
</details>

---

