---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:25:37 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790173219 50
1790173224 50
1790173229 50
1790173234 50
1790173239 50
1790173244 50
1790173249 50
1790173254 50
1790173259 50
1790173264 50
1790173269 50
1790173274 50
1790173279 50
1790173284 50
1790173289 50
1790173294 50
1790173299 50
1790173304 50
1790173309 50
1790173314 50
```
</details>

---

