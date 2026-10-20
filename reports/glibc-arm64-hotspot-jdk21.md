---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 10:10:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1792505048 64
1792505053 64
1792505058 64
1792505063 44
1792505068 44
1792505073 44
1792505078 44
1792505083 44
1792505088 44
1792505093 44
1792505098 44
1792505103 44
1792505108 44
1792505113 44
1792505118 44
1792505123 44
1792505128 49
1792505133 49
1792505138 49
1792505143 49
```
</details>

---

