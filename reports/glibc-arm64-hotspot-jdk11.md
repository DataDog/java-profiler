---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 10:46:16 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1792161432 47
1792161437 47
1792161442 48
1792161447 48
1792161452 47
1792161457 47
1792161462 47
1792161467 47
1792161472 47
1792161477 47
1792161482 48
1792161487 48
1792161492 48
1792161497 48
1792161502 48
1792161507 48
1792161512 48
1792161517 48
1792161522 48
1792161527 48
```
</details>

---

