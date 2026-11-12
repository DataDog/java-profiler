---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:35:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 588 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1794490171 29
1794490176 29
1794490181 29
1794490186 29
1794490191 29
1794490196 29
1794490202 29
1794490207 29
1794490212 29
1794490217 29
1794490222 29
1794490227 29
1794490232 29
1794490237 29
1794490242 29
1794490247 29
1794490252 29
1794490257 32
1794490262 32
1794490267 32
```
</details>

---

