---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-02 05:51:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 33-48 cores)</summary>

```
1790934408 47
1790934413 48
1790934418 48
1790934423 48
1790934428 48
1790934433 41
1790934438 41
1790934443 41
1790934448 41
1790934453 41
1790934458 41
1790934463 41
1790934468 41
1790934473 37
1790934478 37
1790934483 37
1790934488 37
1790934493 37
1790934498 37
1790934503 33
```
</details>

---

