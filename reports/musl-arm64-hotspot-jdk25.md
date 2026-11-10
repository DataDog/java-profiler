---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:54:03 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1794340142 25
1794340147 25
1794340152 25
1794340157 25
1794340162 25
1794340167 30
1794340172 30
1794340177 30
1794340182 30
1794340187 30
1794340192 30
1794340197 30
1794340202 30
1794340207 30
1794340212 30
1794340217 30
1794340222 30
1794340227 30
1794340232 30
1794340237 30
```
</details>

---

