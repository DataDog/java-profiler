---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 07:03:23 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790161167 43
1790161172 43
1790161177 43
1790161182 43
1790161187 43
1790161192 43
1790161197 43
1790161202 43
1790161207 43
1790161212 48
1790161217 48
1790161222 48
1790161227 43
1790161232 43
1790161237 38
1790161242 38
1790161247 38
1790161252 38
1790161257 38
1790161262 38
```
</details>

---

