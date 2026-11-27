---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:30:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795793088 47
1795793093 47
1795793098 47
1795793103 47
1795793108 47
1795793113 47
1795793118 47
1795793123 47
1795793128 47
1795793133 47
1795793138 47
1795793143 47
1795793148 47
1795793153 64
1795793158 64
1795793163 64
1795793168 64
1795793173 47
1795793178 47
1795793183 47
```
</details>

---

