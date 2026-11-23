---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 11 |
| Allocations | 117 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1795429047 44
1795429052 44
1795429057 39
1795429062 39
1795429067 39
1795429072 39
1795429077 39
1795429082 39
1795429087 39
1795429092 39
1795429097 39
1795429102 39
1795429107 39
1795429112 39
1795429117 39
1795429122 39
1795429127 39
1795429132 39
1795429137 39
1795429142 39
```
</details>

---

