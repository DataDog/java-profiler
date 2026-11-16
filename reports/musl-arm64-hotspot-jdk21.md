---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:41:36 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 14 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1794793096 24
1794793101 24
1794793106 19
1794793111 19
1794793116 19
1794793121 19
1794793126 21
1794793131 21
1794793136 21
1794793141 21
1794793146 21
1794793151 21
1794793156 21
1794793161 21
1794793166 21
1794793171 21
1794793176 21
1794793182 21
1794793187 21
1794793192 21
```
</details>

---

