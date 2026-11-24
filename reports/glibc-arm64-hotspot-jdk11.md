---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 10:25:37 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 21-31 cores)</summary>

```
1795533703 21
1795533708 21
1795533713 21
1795533718 21
1795533723 21
1795533728 21
1795533733 21
1795533738 21
1795533743 21
1795533748 21
1795533753 21
1795533758 31
1795533763 31
1795533768 31
1795533773 31
1795533778 31
1795533783 31
1795533788 31
1795533793 31
1795533798 31
```
</details>

---

