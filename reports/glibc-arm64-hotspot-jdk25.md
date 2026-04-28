---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 09:37:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 10 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1777383175 60
1777383180 60
1777383185 60
1777383190 60
1777383195 60
1777383200 60
1777383205 60
1777383210 60
1777383215 60
1777383220 60
1777383225 60
1777383230 60
1777383235 60
1777383240 60
1777383245 60
1777383250 60
1777383255 60
1777383260 60
1777383265 60
1777383270 60
```
</details>

---

