---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:30:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 21-21 cores)</summary>

```
1795793093 21
1795793098 21
1795793103 21
1795793108 21
1795793113 21
1795793118 21
1795793123 21
1795793128 21
1795793133 21
1795793138 21
1795793143 21
1795793148 21
1795793153 21
1795793158 21
1795793163 21
1795793168 21
1795793173 21
1795793178 21
1795793183 21
1795793188 21
```
</details>

---

