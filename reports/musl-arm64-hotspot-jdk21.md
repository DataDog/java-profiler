---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:37:19 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 37-53 cores)</summary>

```
1793889089 37
1793889094 37
1793889099 41
1793889104 41
1793889109 41
1793889114 41
1793889119 41
1793889124 41
1793889129 41
1793889134 41
1793889139 41
1793889144 41
1793889149 41
1793889154 41
1793889159 41
1793889164 41
1793889169 41
1793889174 41
1793889179 41
1793889184 41
```
</details>

---

