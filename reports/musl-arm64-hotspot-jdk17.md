---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 07:24:19 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 13 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (3 unique values: 46-56 cores)</summary>

```
1776252037 56
1776252042 56
1776252047 56
1776252052 56
1776252057 56
1776252062 56
1776252067 56
1776252072 56
1776252077 56
1776252082 56
1776252087 56
1776252092 56
1776252098 56
1776252103 51
1776252108 51
1776252113 51
1776252118 51
1776252123 51
1776252128 51
1776252133 51
```
</details>

---

