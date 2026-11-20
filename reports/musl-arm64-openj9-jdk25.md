---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:39:04 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 14 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (3 unique values: 39-64 cores)</summary>

```
1795170831 39
1795170836 39
1795170841 39
1795170846 39
1795170851 39
1795170856 39
1795170861 39
1795170866 39
1795170871 39
1795170876 44
1795170881 44
1795170886 44
1795170892 44
1795170897 44
1795170902 44
1795170907 44
1795170912 44
1795170917 44
1795170922 44
1795170927 44
```
</details>

---

