---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:07:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 65-72 cores)</summary>

```
1795014157 65
1795014162 65
1795014168 72
1795014173 72
1795014178 72
1795014183 72
1795014188 72
1795014193 72
1795014198 72
1795014203 72
1795014208 72
1795014213 72
1795014218 72
1795014223 72
1795014228 72
1795014233 72
1795014238 72
1795014243 72
1795014248 72
1795014253 72
```
</details>

---

