---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:21:38 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794824130 40
1794824135 40
1794824140 40
1794824145 40
1794824150 40
1794824155 40
1794824160 40
1794824165 40
1794824170 40
1794824175 35
1794824180 35
1794824185 35
1794824190 35
1794824195 35
1794824200 35
1794824205 35
1794824210 35
1794824215 35
1794824220 35
1794824225 35
```
</details>

---

