---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:29:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795397152 59
1795397157 59
1795397162 59
1795397167 59
1795397172 59
1795397177 59
1795397182 59
1795397187 64
1795397192 64
1795397197 64
1795397202 64
1795397207 64
1795397212 64
1795397217 64
1795397222 64
1795397227 64
1795397232 64
1795397237 64
1795397242 64
1795397247 64
```
</details>

---

