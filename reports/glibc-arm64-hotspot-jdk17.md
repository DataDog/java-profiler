---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:10:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792505114 46
1792505119 46
1792505124 46
1792505129 46
1792505134 51
1792505139 51
1792505144 51
1792505149 51
1792505154 51
1792505159 51
1792505164 51
1792505169 51
1792505174 51
1792505179 51
1792505184 51
1792505189 51
1792505194 51
1792505199 51
1792505205 51
1792505210 51
```
</details>

---

