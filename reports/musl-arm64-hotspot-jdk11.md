---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:46:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 983 |
| Sample Rate | 16.38/sec |
| Health Score | 1024% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794580926 51
1794580931 51
1794580936 51
1794580941 51
1794580946 51
1794580951 51
1794580956 46
1794580961 46
1794580966 46
1794580971 46
1794580976 46
1794580981 46
1794580986 46
1794580991 46
1794580996 46
1794581001 46
1794581006 46
1794581011 46
1794581016 46
1794581021 46
```
</details>

---

