---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 13:11:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786122403 32
1786122408 32
1786122413 32
1786122418 32
1786122423 32
1786122428 32
1786122433 32
1786122438 32
1786122443 32
1786122448 32
1786122453 32
1786122458 32
1786122463 32
1786122468 32
1786122473 32
1786122478 32
1786122483 32
1786122488 32
1786122493 32
1786122498 32
```
</details>

---

