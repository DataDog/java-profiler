---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 09:55:42 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 15-20 cores)</summary>

```
1787147515 20
1787147520 20
1787147525 20
1787147530 20
1787147535 20
1787147540 20
1787147545 20
1787147550 20
1787147555 15
1787147560 15
1787147565 15
1787147570 15
1787147575 15
1787147580 15
1787147585 15
1787147590 15
1787147595 15
1787147600 15
1787147605 15
1787147610 15
```
</details>

---

