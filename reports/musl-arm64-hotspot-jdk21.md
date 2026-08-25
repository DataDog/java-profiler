---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 05:49:26 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1787650984 22
1787650989 17
1787650994 17
1787650999 17
1787651004 17
1787651009 17
1787651014 17
1787651019 17
1787651024 17
1787651029 17
1787651034 17
1787651039 17
1787651044 22
1787651049 22
1787651054 22
1787651059 22
1787651064 22
1787651069 22
1787651074 22
1787651079 22
```
</details>

---

