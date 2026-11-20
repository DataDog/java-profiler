---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:39:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 16 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1795170786 29
1795170791 30
1795170796 30
1795170801 30
1795170806 30
1795170811 30
1795170816 30
1795170821 30
1795170826 30
1795170831 30
1795170836 30
1795170841 30
1795170846 30
1795170851 30
1795170856 30
1795170861 30
1795170866 30
1795170871 30
1795170876 30
1795170881 30
```
</details>

---

