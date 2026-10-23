---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 05:55:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 14 |
| Allocations | 91 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1792749124 39
1792749129 39
1792749134 39
1792749139 39
1792749144 44
1792749149 44
1792749154 44
1792749159 44
1792749164 44
1792749169 44
1792749174 44
1792749179 44
1792749184 44
1792749189 44
1792749194 44
1792749199 44
1792749204 44
1792749209 44
1792749214 44
1792749219 44
```
</details>

---

