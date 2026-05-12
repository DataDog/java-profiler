---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 20:50:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778546820 64
1778546825 64
1778546830 64
1778546835 64
1778546840 64
1778546845 64
1778546850 64
1778546855 64
1778546860 64
1778546865 64
1778546870 64
1778546875 64
1778546880 64
1778546885 64
1778546890 64
1778546895 64
1778546900 64
1778546905 64
1778546910 64
1778546915 64
```
</details>

---

