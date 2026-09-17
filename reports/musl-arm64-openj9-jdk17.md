---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:48:49 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 10 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 32-35 cores)</summary>

```
1789677738 32
1789677743 32
1789677748 32
1789677753 32
1789677758 32
1789677763 32
1789677768 32
1789677773 32
1789677778 32
1789677783 32
1789677788 32
1789677793 32
1789677798 32
1789677803 32
1789677808 35
1789677813 35
1789677818 35
1789677823 35
1789677828 35
1789677833 35
```
</details>

---

