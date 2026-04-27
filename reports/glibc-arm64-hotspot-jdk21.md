---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-27 05:15:06 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777281068 64
1777281073 64
1777281078 64
1777281083 64
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
```
</details>

---

