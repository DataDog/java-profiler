---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 05:26:35 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789723403 48
1789723408 48
1789723413 48
1789723418 48
1789723423 48
1789723428 48
1789723433 48
1789723438 48
1789723443 48
1789723448 48
1789723453 48
1789723458 48
1789723463 48
1789723468 46
1789723473 46
1789723478 46
1789723483 46
1789723488 46
1789723493 46
1789723498 46
```
</details>

---

