---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 04:21:12 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 12 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790669778 48
1790669783 48
1790669788 48
1790669793 48
1790669798 48
1790669803 48
1790669808 48
1790669813 48
1790669818 48
1790669823 48
1790669828 48
1790669833 48
1790669838 48
1790669843 48
1790669848 48
1790669853 48
1790669858 48
1790669863 48
1790669868 48
1790669873 48
```
</details>

---

