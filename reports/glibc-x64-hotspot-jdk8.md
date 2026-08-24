---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-24 15:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1787600212 96
1787600217 96
1787600222 96
1787600227 96
1787600232 96
1787600237 96
1787600242 96
1787600247 96
1787600252 96
1787600257 96
1787600262 96
1787600267 96
1787600272 96
1787600277 96
1787600282 96
1787600287 96
1787600292 96
1787600297 96
1787600302 96
1787600307 92
```
</details>

---

