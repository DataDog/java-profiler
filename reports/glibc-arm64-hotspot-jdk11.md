---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:58:28 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (7 unique values: 20-32 cores)</summary>

```
1795085591 26
1795085596 26
1795085601 26
1795085606 26
1795085611 28
1795085616 28
1795085621 28
1795085626 28
1795085631 28
1795085636 28
1795085641 28
1795085646 28
1795085651 28
1795085656 28
1795085661 27
1795085666 27
1795085671 32
1795085676 32
1795085681 32
1795085686 32
```
</details>

---

