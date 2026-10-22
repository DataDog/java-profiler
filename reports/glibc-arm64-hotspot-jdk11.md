---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:38:38 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (6 unique values: 32-48 cores)</summary>

```
1792672417 34
1792672422 34
1792672427 32
1792672432 32
1792672437 32
1792672442 33
1792672447 33
1792672452 33
1792672457 33
1792672462 33
1792672467 33
1792672472 35
1792672477 35
1792672482 35
1792672487 35
1792672492 35
1792672497 45
1792672502 45
1792672507 45
1792672512 45
```
</details>

---

