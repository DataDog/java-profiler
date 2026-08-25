---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 16:41:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 80-88 cores)</summary>

```
1787690214 86
1787690219 86
1787690224 86
1787690229 86
1787690234 86
1787690239 88
1787690244 88
1787690249 88
1787690254 88
1787690259 88
1787690264 88
1787690269 80
1787690274 80
1787690279 80
1787690284 80
1787690289 80
1787690294 80
1787690299 80
1787690304 80
1787690309 80
```
</details>

---

