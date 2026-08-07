---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-07 07:56:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1786103475 64
1786103480 64
1786103485 64
1786103490 64
1786103495 64
1786103500 64
1786103505 64
1786103510 64
1786103515 64
1786103520 64
1786103525 64
1786103530 64
1786103535 64
1786103540 64
1786103545 64
1786103550 67
1786103555 67
1786103560 67
1786103565 67
1786103570 67
```
</details>

---

