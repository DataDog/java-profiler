---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 16:13:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 10 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 14-18 cores)</summary>

```
1794776905 14
1794776910 14
1794776915 14
1794776920 14
1794776925 14
1794776930 14
1794776935 14
1794776940 14
1794776945 14
1794776950 14
1794776955 14
1794776960 14
1794776965 16
1794776970 16
1794776975 16
1794776980 18
1794776985 18
1794776991 18
1794776996 18
1794777001 18
```
</details>

---

