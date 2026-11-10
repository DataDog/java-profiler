---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:31:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 12 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794324452 48
1794324457 48
1794324462 48
1794324467 48
1794324472 48
1794324477 48
1794324482 48
1794324487 48
1794324492 48
1794324497 48
1794324502 48
1794324507 48
1794324512 48
1794324517 48
1794324522 48
1794324527 48
1794324532 48
1794324537 48
1794324542 48
1794324547 48
```
</details>

---

