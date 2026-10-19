---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 08:04:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1792411191 31
1792411196 51
1792411201 51
1792411206 51
1792411211 31
1792411216 31
1792411221 31
1792411226 31
1792411231 31
1792411236 31
1792411241 31
1792411246 31
1792411251 31
1792411256 31
1792411261 31
1792411266 31
1792411271 31
1792411276 31
1792411281 31
1792411286 31
```
</details>

---

