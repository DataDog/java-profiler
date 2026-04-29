---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 51-63 cores)</summary>

```
1777475044 63
1777475049 63
1777475054 61
1777475059 61
1777475064 61
1777475069 61
1777475074 51
1777475079 51
1777475084 51
1777475089 53
1777475094 53
1777475099 53
1777475104 53
1777475109 53
1777475114 53
1777475119 53
1777475124 53
1777475129 53
1777475134 53
1777475139 53
```
</details>

---

