---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:38:24 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 61-64 cores)</summary>

```
1790238795 62
1790238800 62
1790238805 62
1790238810 62
1790238815 63
1790238820 63
1790238825 63
1790238830 63
1790238835 63
1790238840 63
1790238845 61
1790238850 61
1790238855 61
1790238860 61
1790238865 62
1790238870 62
1790238875 62
1790238880 62
1790238885 62
1790238890 64
```
</details>

---

