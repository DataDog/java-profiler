---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:45:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 45-64 cores)</summary>

```
1794840080 64
1794840085 64
1794840090 64
1794840095 64
1794840100 64
1794840105 45
1794840110 45
1794840115 45
1794840120 45
1794840125 45
1794840130 45
1794840135 45
1794840140 45
1794840145 45
1794840150 45
1794840155 45
1794840160 45
1794840165 49
1794840170 49
1794840175 49
```
</details>

---

