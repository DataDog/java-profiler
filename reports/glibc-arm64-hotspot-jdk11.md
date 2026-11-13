---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:24:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 11 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794594076 51
1794594081 51
1794594086 51
1794594091 51
1794594096 51
1794594101 51
1794594106 46
1794594111 46
1794594116 46
1794594121 46
1794594126 46
1794594131 46
1794594136 46
1794594141 46
1794594146 46
1794594151 46
1794594156 46
1794594161 46
1794594166 51
1794594171 51
```
</details>

---

