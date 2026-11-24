---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 12:21:54 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 9 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795540618 29
1795540623 29
1795540628 29
1795540633 29
1795540638 29
1795540643 34
1795540648 34
1795540653 34
1795540658 34
1795540663 34
1795540668 34
1795540673 34
1795540678 34
1795540683 34
1795540688 34
1795540693 34
1795540698 34
1795540703 34
1795540708 34
1795540713 34
```
</details>

---

