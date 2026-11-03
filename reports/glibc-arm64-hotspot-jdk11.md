---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:50:59 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1793742154 48
1793742160 28
1793742165 28
1793742170 28
1793742175 28
1793742180 28
1793742185 28
1793742190 28
1793742195 28
1793742200 28
1793742205 28
1793742210 28
1793742215 28
1793742220 28
1793742225 28
1793742230 28
1793742235 28
1793742240 28
1793742245 28
1793742250 28
```
</details>

---

