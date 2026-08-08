---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-08 05:50:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 21-48 cores)</summary>

```
1786182252 21
1786182257 21
1786182262 48
1786182267 48
1786182272 48
1786182277 48
1786182282 48
1786182287 48
1786182292 48
1786182297 48
1786182302 48
1786182307 48
1786182312 48
1786182317 48
1786182322 48
1786182327 48
1786182332 48
1786182337 48
1786182342 48
1786182347 48
```
</details>

---

