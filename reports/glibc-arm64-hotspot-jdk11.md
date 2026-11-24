---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 08:09:17 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 12 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
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
1795525526 54
1795525531 54
1795525536 54
1795525541 59
1795525546 59
1795525551 59
1795525556 59
1795525561 59
```
</details>

---

