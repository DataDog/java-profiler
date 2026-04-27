---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 05:15:06 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777281088 64
1777281093 64
1777281098 64
1777281103 64
1777281108 64
1777281113 64
1777281118 64
1777281123 64
1777281128 64
1777281133 64
1777281138 64
1777281143 64
1777281148 64
1777281153 59
1777281158 59
1777281163 59
1777281168 59
1777281173 59
1777281178 59
1777281184 59
```
</details>

---

