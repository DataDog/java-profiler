---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:30:24 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795793156 64
1795793161 64
1795793166 64
1795793171 64
1795793176 64
1795793181 64
1795793186 64
1795793191 64
1795793196 64
1795793201 64
1795793206 64
1795793211 64
1795793216 64
1795793221 64
1795793226 64
1795793231 64
1795793236 64
1795793241 64
1795793246 64
1795793251 64
```
</details>

---

