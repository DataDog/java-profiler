---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:59:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 13 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 36-45 cores)</summary>

```
1770828851 36
1770828856 36
1770828861 45
1770828866 45
1770828871 42
1770828876 42
1770828881 42
1770828886 42
1770828891 42
1770828896 42
1770828901 42
1770828906 42
1770828911 42
1770828916 43
1770828921 43
1770828926 43
1770828931 43
1770828936 45
1770828941 45
1770828946 45
```
</details>

---

