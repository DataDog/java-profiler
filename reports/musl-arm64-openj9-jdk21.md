---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:31:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 8 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795008251 51
1795008256 51
1795008261 51
1795008266 51
1795008271 51
1795008276 51
1795008281 51
1795008286 51
1795008291 51
1795008296 51
1795008301 51
1795008306 51
1795008311 51
1795008316 51
1795008321 51
1795008326 51
1795008331 51
1795008336 51
1795008341 51
1795008346 64
```
</details>

---

