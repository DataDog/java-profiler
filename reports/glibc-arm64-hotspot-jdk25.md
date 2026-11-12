---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:27:11 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 180 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794504166 48
1794504171 48
1794504176 48
1794504181 48
1794504186 48
1794504191 48
1794504196 48
1794504201 48
1794504206 48
1794504211 48
1794504216 48
1794504221 48
1794504226 48
1794504231 48
1794504236 43
1794504241 43
1794504246 43
1794504251 43
1794504256 43
1794504261 43
```
</details>

---

