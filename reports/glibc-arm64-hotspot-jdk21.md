---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:29:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 51 |
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
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 15-51 cores)</summary>

```
1795001075 15
1795001080 15
1795001085 15
1795001090 15
1795001095 15
1795001100 15
1795001105 15
1795001110 15
1795001115 15
1795001120 15
1795001125 51
1795001130 51
1795001135 51
1795001140 51
1795001145 51
1795001150 51
1795001155 51
1795001160 51
1795001165 51
1795001170 51
```
</details>

---

