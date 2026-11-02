---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 11:02:22 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793635074 48
1793635079 48
1793635084 48
1793635089 48
1793635094 48
1793635099 48
1793635104 48
1793635109 48
1793635114 48
1793635119 48
1793635124 48
1793635129 48
1793635134 48
1793635139 48
1793635144 48
1793635149 48
1793635154 48
1793635159 48
1793635164 48
1793635169 48
```
</details>

---

