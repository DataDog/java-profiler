---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:39:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 32-60 cores)</summary>

```
1795170806 32
1795170811 32
1795170816 60
1795170821 60
1795170826 32
1795170831 32
1795170836 32
1795170841 32
1795170846 32
1795170851 32
1795170856 32
1795170861 32
1795170866 32
1795170871 32
1795170876 32
1795170881 32
1795170886 42
1795170891 42
1795170896 42
1795170901 42
```
</details>

---

