---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 09:47:48 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1794580916 27
1794580921 27
1794580926 27
1794580931 27
1794580936 27
1794580941 27
1794580946 27
1794580951 27
1794580956 27
1794580961 27
1794580966 27
1794580971 27
1794580976 25
1794580981 25
1794580986 25
1794580991 25
1794580996 25
1794581001 25
1794581006 30
1794581011 30
```
</details>

---

