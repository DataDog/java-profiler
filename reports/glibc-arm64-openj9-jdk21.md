---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 17:32:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 95 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777325191 64
1777325196 64
1777325201 64
1777325206 64
1777325211 64
1777325216 64
1777325221 64
1777325226 64
1777325231 64
1777325236 64
1777325241 64
1777325246 64
1777325251 64
1777325256 64
1777325262 64
1777325267 64
1777325272 64
1777325277 64
1777325282 64
1777325287 64
```
</details>

---

