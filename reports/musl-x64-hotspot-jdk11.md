---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795451688 83
1795451693 83
1795451698 83
1795451703 83
1795451708 83
1795451713 85
1795451718 85
1795451723 83
1795451728 83
1795451733 83
1795451738 83
1795451743 83
1795451748 83
1795451753 83
1795451758 83
1795451763 83
1795451768 83
1795451773 83
1795451778 83
1795451783 83
```
</details>

---

