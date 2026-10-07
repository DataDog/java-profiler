---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 14:24:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (5 unique values: 65-76 cores)</summary>

```
1791397151 74
1791397156 74
1791397161 74
1791397166 74
1791397171 74
1791397176 74
1791397181 74
1791397186 74
1791397191 74
1791397196 74
1791397201 74
1791397206 72
1791397211 72
1791397216 72
1791397221 76
1791397226 76
1791397231 65
1791397236 65
1791397241 65
1791397246 65
```
</details>

---

