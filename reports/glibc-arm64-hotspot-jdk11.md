---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 00:59:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 10 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 8-13 cores)</summary>

```
1790139265 13
1790139270 13
1790139275 13
1790139280 13
1790139285 13
1790139290 8
1790139295 8
1790139300 13
1790139305 13
1790139310 13
1790139315 13
1790139320 13
1790139325 13
1790139330 13
1790139335 13
1790139340 13
1790139345 13
1790139350 13
1790139355 13
1790139360 13
```
</details>

---

