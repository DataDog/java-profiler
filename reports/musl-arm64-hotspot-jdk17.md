---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 14:20:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 7 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (1 unique values: 35-35 cores)</summary>

```
1792519986 35
1792519991 35
1792519996 35
1792520001 35
1792520006 35
1792520011 35
1792520016 35
1792520021 35
1792520026 35
1792520031 35
1792520036 35
1792520041 35
1792520047 35
1792520052 35
1792520057 35
1792520062 35
1792520067 35
1792520072 35
1792520077 35
1792520082 35
```
</details>

---

