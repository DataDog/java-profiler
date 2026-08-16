---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-16 11:16:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786893104 64
1786893109 64
1786893114 64
1786893119 64
1786893124 64
1786893129 64
1786893134 64
1786893139 64
1786893144 64
1786893149 64
1786893154 64
1786893159 64
1786893164 64
1786893169 64
1786893174 64
1786893179 64
1786893184 64
1786893190 64
1786893195 64
1786893200 64
```
</details>

---

