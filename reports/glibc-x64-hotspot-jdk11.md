---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 19:06:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792710083 30
1792710088 30
1792710093 30
1792710098 30
1792710103 30
1792710108 30
1792710113 30
1792710118 30
1792710123 30
1792710128 30
1792710133 30
1792710138 30
1792710143 30
1792710148 30
1792710153 30
1792710158 30
1792710163 30
1792710168 32
1792710173 32
1792710178 32
```
</details>

---

