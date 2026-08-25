---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-25 16:41:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1787690229 42
1787690234 42
1787690239 42
1787690244 42
1787690249 42
1787690254 42
1787690259 42
1787690264 62
1787690269 62
1787690274 62
1787690279 62
1787690284 62
1787690289 62
1787690294 62
1787690299 62
1787690304 62
1787690309 62
1787690314 64
1787690319 64
1787690324 64
```
</details>

---

