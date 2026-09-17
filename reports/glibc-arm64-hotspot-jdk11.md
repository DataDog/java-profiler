---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:03:54 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789682151 30
1789682156 30
1789682161 30
1789682166 30
1789682171 30
1789682176 30
1789682181 30
1789682186 30
1789682191 30
1789682196 30
1789682201 30
1789682206 30
1789682211 30
1789682216 30
1789682221 30
1789682226 30
1789682231 30
1789682236 30
1789682241 30
1789682246 30
```
</details>

---

