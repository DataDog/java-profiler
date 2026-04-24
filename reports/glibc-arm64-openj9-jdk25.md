---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-24 12:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777049457 64
1777049462 64
1777049467 64
1777049472 64
1777049477 64
1777049482 64
1777049487 64
1777049492 64
1777049497 64
1777049502 64
1777049508 64
1777049513 64
1777049518 64
1777049523 64
1777049528 64
1777049533 64
1777049538 64
1777049543 64
1777049548 64
1777049553 64
```
</details>

---

