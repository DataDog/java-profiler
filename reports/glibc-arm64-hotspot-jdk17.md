---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:12:23 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795194480 50
1795194485 50
1795194490 50
1795194495 50
1795194500 50
1795194505 50
1795194510 50
1795194515 50
1795194520 50
1795194525 50
1795194530 50
1795194535 50
1795194540 50
1795194545 50
1795194550 50
1795194555 50
1795194560 50
1795194565 50
1795194570 50
1795194575 50
```
</details>

---

