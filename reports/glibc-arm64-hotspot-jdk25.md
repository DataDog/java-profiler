---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (5 unique values: 29-37 cores)</summary>

```
1795429077 29
1795429082 29
1795429087 29
1795429092 29
1795429097 29
1795429102 29
1795429107 29
1795429112 29
1795429117 33
1795429122 33
1795429127 31
1795429132 31
1795429137 34
1795429142 34
1795429147 34
1795429152 34
1795429157 34
1795429162 34
1795429167 34
1795429172 34
```
</details>

---

