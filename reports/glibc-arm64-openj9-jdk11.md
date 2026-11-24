---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 08:09:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1795525426 49
1795525431 49
1795525436 49
1795525441 49
1795525446 49
1795525451 49
1795525456 49
1795525461 49
1795525466 54
1795525471 54
1795525476 54
1795525481 54
1795525486 54
1795525491 54
1795525496 54
1795525501 54
1795525506 54
1795525511 54
1795525516 54
1795525521 54
```
</details>

---

