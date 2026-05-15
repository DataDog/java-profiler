---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-15 05:49:47 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778838162 64
1778838167 64
1778838172 64
1778838177 64
1778838182 64
1778838187 64
1778838192 64
1778838197 64
1778838202 64
1778838207 64
1778838212 64
1778838217 64
1778838222 64
1778838227 64
1778838232 64
1778838237 64
1778838242 64
1778838247 64
1778838252 64
1778838257 64
```
</details>

---

