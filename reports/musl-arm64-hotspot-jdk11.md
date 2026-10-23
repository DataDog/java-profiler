---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:47 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792767175 51
1792767180 51
1792767185 51
1792767191 51
1792767196 51
1792767201 51
1792767206 51
1792767211 51
1792767216 51
1792767221 51
1792767226 51
1792767231 51
1792767236 51
1792767241 51
1792767246 51
1792767251 51
1792767256 51
1792767261 51
1792767266 51
1792767271 51
```
</details>

---

