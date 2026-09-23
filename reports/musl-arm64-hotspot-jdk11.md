---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790172190 48
1790172195 48
1790172200 48
1790172205 48
1790172210 48
1790172215 48
1790172220 48
1790172225 48
1790172230 48
1790172235 48
1790172240 48
1790172245 48
1790172250 48
1790172255 48
1790172260 48
1790172265 48
1790172270 48
1790172275 48
1790172280 48
1790172285 43
```
</details>

---

