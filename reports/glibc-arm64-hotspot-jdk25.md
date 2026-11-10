---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 14:54:00 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 15 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794340148 32
1794340153 32
1794340158 32
1794340163 32
1794340168 32
1794340173 32
1794340178 32
1794340183 32
1794340188 32
1794340193 32
1794340198 32
1794340203 32
1794340208 32
1794340213 32
1794340218 32
1794340223 32
1794340228 32
1794340233 32
1794340238 32
1794340243 32
```
</details>

---

