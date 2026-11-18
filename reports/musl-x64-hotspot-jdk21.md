---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 00:06:55 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 33-66 cores)</summary>

```
1794978114 33
1794978119 33
1794978124 33
1794978129 33
1794978134 33
1794978139 33
1794978144 33
1794978149 33
1794978154 33
1794978159 33
1794978164 33
1794978169 33
1794978174 33
1794978179 66
1794978184 66
1794978189 66
1794978194 66
1794978199 66
1794978204 66
1794978209 66
```
</details>

---

