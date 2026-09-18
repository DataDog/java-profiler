---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:27:49 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (5 unique values: 27-44 cores)</summary>

```
1789737667 44
1789737672 44
1789737677 44
1789737682 44
1789737687 44
1789737692 44
1789737697 44
1789737702 44
1789737707 32
1789737712 32
1789737717 32
1789737722 32
1789737727 32
1789737732 32
1789737738 32
1789737743 32
1789737748 27
1789737753 27
1789737758 27
1789737763 27
```
</details>

---

