---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 17:27:03 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 37-47 cores)</summary>

```
1792704148 42
1792704153 42
1792704158 42
1792704163 42
1792704168 42
1792704173 42
1792704179 42
1792704184 37
1792704189 37
1792704194 37
1792704199 37
1792704204 37
1792704209 37
1792704214 37
1792704219 37
1792704224 37
1792704229 37
1792704234 47
1792704239 47
1792704244 47
```
</details>

---

