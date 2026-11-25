---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:05:25 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1795608030 30
1795608035 30
1795608040 30
1795608045 30
1795608050 30
1795608055 25
1795608060 25
1795608065 25
1795608070 25
1795608075 25
1795608080 25
1795608085 25
1795608090 25
1795608095 25
1795608100 25
1795608105 30
1795608110 30
1795608115 30
1795608120 30
1795608125 30
```
</details>

---

